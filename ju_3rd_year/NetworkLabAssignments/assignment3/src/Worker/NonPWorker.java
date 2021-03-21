package Worker;

import Node.Node;
import Packet.Packet;

import java.util.ArrayList;
import java.util.concurrent.CountDownLatch;

public class NonPWorker {
    private int num_nodes;
    private int avg_transmission_time;
    private int channel_speed;
    private int distance_between_nodes;
    private int propagation_speed;

    CountDownLatch latch;
    private double probability;

    ArrayList<Node> nodes;

    public NonPWorker(int num_nodes, int avg_transmission_time, int channel_speed, int distance_between_nodes, int propagation_speed, double probability) {
        latch = new CountDownLatch(1);
        this.num_nodes = num_nodes;
        this.avg_transmission_time = avg_transmission_time;
        this.channel_speed = channel_speed;
        this.distance_between_nodes = distance_between_nodes;
        this.propagation_speed = propagation_speed;
        this.probability = probability;
        nodes = new ArrayList<Node>();

        buildNodes();
        latch.countDown();
        startAlgo();

    }

    private void buildNodes() {
        for (int i = 0; i < num_nodes; i++) {
            nodes.add(new Node(i * distance_between_nodes, avg_transmission_time, i));
        }
    }

    public void startAlgo() {


        double curr_time = 0;
        int transmitted_packets = 0;
        int successfully_transmitted_packets = 0;
//        latch2 = new CountDownLatch(1);
        Node currentfirst = new Node(-1, avg_transmission_time, 0);
//        latch2.countDown();

        int packetLengthSum = 0;
        long start_time = System.currentTimeMillis();


        // continue the process until no frames are left to be sent
        while (true) {
            Node current = currentfirst;
            // clears buffer and adds a single element
            current.addNew(1e9);

            for (Node node : nodes) {
                if (node.len() > 0) {
                    if (current.compareTo(node) < 0) {
                        current = node;
                    }
                }
            }

            if (current.getLocation() == -1)
                break;


            // wait for a slot increase current time
            if (current.buffer.size() > 0) {
                Packet p = current.buffer.get(0);
                double time = p.getTime() + 0.5;
                p.setTime(time);
                current.buffer.set(0, p);
            }
//            current.waitNode();


            // Check if collision will occur when the first frame is being sent
            // Collision occurs when any other node has
            // sending time < curr_time + propagation time of first frame
            // and the channel remains busy for the above + transmission time
            curr_time = current.getTime();
            transmitted_packets += 1;

            boolean collision_occured_once = false;

            //


            // Check if channel is busy : SENSE THE CHANNEL

            for (Node node : nodes) {
                if (node.getLocation() != current.getLocation() && node.len() > 0) {
                    int distance = Math.abs(node.getLocation() - current.getLocation());


                    // Propagation speed = Distance / propagation_speed
                    double propagation_time = distance / (double) propagation_speed;

                    // Time when the first bit until the last bit has left the transmitting node
                    // Packet transmission time = Packet size ( in bits ) / Bit rate

                    double transmission_time = 8 * current.getFirst().toCodeWord().length() / (double) (channel_speed);

                    // The time when the first bit leaves the transmitter until the last is received.
                    // Packet delivery time = Transmission time +

                    boolean collision_occured = false;

                    // collision occured
                    if (node.getTime() <= curr_time + propagation_time)
                        collision_occured = true;


                    // condition for busy channel
                    if (node.getTime() > curr_time + propagation_time && node.getTime() < curr_time + propagation_time + transmission_time) {
                        node.nonPersistentOnBusBusy(channel_speed);
//                        node.waitNode();
                    }

                    if (collision_occured) {
                        collision_occured_once = true;
                        transmitted_packets += 1;
                        node.onCollisionWait(channel_speed);
                    }
                }
            }


            /**
             *
             *  Send frame if no collision has occured
             *
             */

//            current.waitNode();
//            double time = current.getTime() + 1;
//            for (Node nn : nodes) {
//                if (nn.buffer.size() > 0) {
//                    if (nn.getTime() < time) {
//                        Packet p = nn.buffer.get(0);
//                        p.setTime(time);
//                        nn.buffer.set(0, p);
//                    }
//                }
//            }

            if (collision_occured_once == false) {

                System.out.print("[RECEIVER] " + current);
                System.out.println(" " + current.buffer.get(0));
                packetLengthSum += current.buffer.get(0).toCodeWord().length();
                successfully_transmitted_packets += 1;
                current.pop_packet();


            } else
                current.onCollisionWait(channel_speed);


        }


        System.out.println("EFFICIENCY : " + String.valueOf((double) (successfully_transmitted_packets) / (double) (transmitted_packets)));
        double avgPacketLength = (double) packetLengthSum / successfully_transmitted_packets;
        long time_end = System.currentTimeMillis();
        double time_taken = (time_end - start_time) / (double) (1000);
        double th = (avgPacketLength * successfully_transmitted_packets) / (double) (time_taken);

        System.out.println("Throughput : " + String.valueOf(th * Math.pow(10, -6)) + " Mbps");
        System.out.println("Collisions  : " + String.valueOf(transmitted_packets - successfully_transmitted_packets));

        System.out.println("Time Taken : " + String.valueOf((time_end - start_time) / 1000) + " seconds");
        System.exit(0);


    }
}
