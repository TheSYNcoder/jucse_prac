package Node;

import Packet.Packet;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Node implements Comparable<Node> {
    public static final double MAX_SIMULATION_TIME = 1000;
    public static final int MAX_COLLISIONS = 15;
    public static final int MAX_PACKETS = 1000;
    public static final double SLOT_TIME = 0.9;
    public ArrayList<Packet> buffer;

    private int location;

    private int wait_collisions;
    private int collisions;
    private int number;
    ExecutorService executor;

    public Node(int location, int avgPacketArrivalTime, int node_number) {
        this.number = node_number;
        this.location = location;
        buffer = new ArrayList<Packet>();
        executor = Executors.newSingleThreadExecutor();

        executor.execute(() -> fillBuffer(avgPacketArrivalTime));
//        fillBuffer(avgPacketArrivalTime);

    }

    /**
     * generates a random number of packets to be sent with
     * random arrival times sampled on avgRandomArrivalTime
     *
     * @param avgPacketArrivalTime
     */
    private void fillBuffer(int avgPacketArrivalTime) {
        double arrival_time = 0;
        int cnt = 1;
        while (arrival_time < MAX_SIMULATION_TIME) {
//            double val = get_exponential_random_variable(avgPacketArrivalTime);
//            System.out.println(val);
            arrival_time += get_exponential_random_variable(avgPacketArrivalTime);

            Packet p = makePacket(cnt);
            cnt += 1;
            p.setTime(arrival_time);
            buffer.add(p);
        }

//        Collections.sort(buffer);

    }

    private Packet makePacket(int cnt) {
        int dataSize = (int) (500 + Math.random() * 2000);
        String payload = new Random().ints(0, 2).limit(dataSize).collect(StringBuilder::new, StringBuilder::append, StringBuilder::append).toString();
        String locationS = Integer.toBinaryString(location);
        for (int i = 0; i < 48 - locationS.length(); i++) {
            locationS = '0' + locationS;
        }
        String dest = new Random().ints(0, 1).limit(48).collect(StringBuilder::new, StringBuilder::append, StringBuilder::append).toString();
        Packet p = new Packet(locationS, dest, payload, cnt);

        return p;
    }

    public int getLocation() {
        return location;
    }

    public double getTime() {
        if (buffer.size() > 0)
            return buffer.get(0).getTime();
        else
            return 1e9;
    }


    public Packet getFirst() {
        if (buffer.size() > 0)
            return buffer.get(0);
        else return null;
    }

    @Override
    public int compareTo(Node o) {
        if (o.buffer.isEmpty() && !buffer.isEmpty()) return 1;
        else if (buffer.isEmpty()) return -1;
//        else if (o.buffer.isEmpty()) return 1;
        else return buffer.get(0).compareTo(o.buffer.get(0));
    }


    public void addNew(double time) {
        Packet p = makePacket(0);
        p.setTime(time);
        buffer.clear();
        buffer.add(p);
    }

    /**
     * generates a random arrival time based on avgPacketArrivalTime
     *
     * @param avgPacketArrivalTime
     * @return random arrival time : double
     */
    private double get_exponential_random_variable(int avgPacketArrivalTime) {
        double uniform_random_variable = 1 - Math.random();
        return (-Math.log(1 - uniform_random_variable) / (float) (avgPacketArrivalTime));
    }

    public void pop_packet() {
        if (buffer.size() > 0)
            buffer.remove(0);
        collisions = 0;
        wait_collisions = 0;
    }


    public void onCollision(int R, int mode) {
        collisions += 1;
        if (collisions > MAX_COLLISIONS) {
            Packet p = buffer.get(0);
            System.out.println("[INFO] " + p + "Discarded");
            pop_packet();
            return;
        }
        double backoff_time;
        if (mode == 2)
            backoff_time = buffer.get(0).getTime() + exponential_backoff_time(R, collisions) + SLOT_TIME;
        else
            backoff_time = buffer.get(0).getTime() + exponential_backoff_time(R, collisions);


        for (int i = 0; i < buffer.size(); i++) {
            if (backoff_time >= buffer.get(i).getTime()) {
                Packet p = buffer.get(i);
                p.setTime(backoff_time);
                buffer.set(i, p);
//                buffer.get(i).setTime(backoff_time);
            }

        }

    }

    public void onCollisionWait(int R) {
        collisions += 1;
        if (collisions > MAX_COLLISIONS) {
            Packet p = buffer.get(0);
            System.out.println("[INFO] " + p + "Discarded");
            pop_packet();
            return;
        }


        double backoff_time = buffer.get(0).getTime() + exponential_backoff_time(R, collisions) + SLOT_TIME;

        for (int i = 0; i < buffer.size(); i++) {
            if (backoff_time >= buffer.get(i).getTime()) {
                Packet p = buffer.get(i);
                p.setTime(backoff_time);
                buffer.set(i, p);
            }

        }

    }

    public void nonPersistentOnBusBusy(int channel_speed) {
//        wait_collisions += 1;
//        if (wait_collisions >= MAX_COLLISIONS) {
//            pop_packet();
//            return;
//        }

        double backoff = buffer.get(0).getTime() + SLOT_TIME + exponential_backoff_time(channel_speed, wait_collisions);

        for (int i = 0; i < buffer.size(); i++) {
            if (backoff >= buffer.get(i).getTime()) {
                Packet p = buffer.get(i);
                p.setTime(backoff);
                buffer.set(i, p);
            }


        }

    }


    public void waitNode() {
//        wait_collisions += 1;
//        if (wait_collisions >= MAX_COLLISIONS) {
//            pop_packet();
//            return;
//        }
        if (buffer.size() > 0) {
            Packet first = buffer.get(0);
            double extended_time = first.getTime() + SLOT_TIME + Math.random() * 2;
            for (int i = 0; i < buffer.size(); i++) {
                if (buffer.get(i).getTime() < extended_time) {
                    Packet p = buffer.get(i);
                    p.setTime(extended_time);
                    buffer.set(i, p);
                }
            }
        }

//        p.setTime(extended_time);
//        buffer.set(0, p);
    }

    public void waitNode(double time) {
        double t = time + Math.random() * 2;
        for (int i = 0; i < buffer.size(); i++) {
            if (buffer.get(i).getTime() < t) {
                Packet p = buffer.get(i);
                p.setTime(t);
                buffer.set(i, p);
            }

        }
    }

    private double exponential_backoff_time(int R, int general_collisions) {
        double rand_time = Math.random() * (Math.pow(2, general_collisions) - 1);
        return rand_time * 512 / (double) (R);
    }


    public int len() {
        return buffer.size();
    }


    @Override
    public String toString() {
        return "Node number : " + String.valueOf(number) + " Location : " + String.valueOf(location);
    }
}
