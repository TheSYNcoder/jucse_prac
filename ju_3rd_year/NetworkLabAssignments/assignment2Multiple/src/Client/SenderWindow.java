package Client;

import Packet.Packet;
import Packet.TimedPacket;
import Utils.ArrayBlockingList;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;
import java.util.concurrent.DelayQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public abstract class SenderWindow {

    private final ArrayBlockingList<TimedPacket> windowPackets;
    private final DelayQueue<TimedPacket> windowTimers;
    private final LinkedBlockingQueue<Packet> packets;


    private final ExecutorService pool;

    private int sequenceLength;
    private int windowLength;
    private int bufferNumber;
    private int windowStart;
    private String srcAdd;
    private String destAdd;
    private int totalCount;

    public SenderWindow(int windowLength, int sequenceLength, String srcAdd, String destAdd) {
        this.windowLength = windowLength;
        this.sequenceLength = sequenceLength;
        this.srcAdd = srcAdd;
        this.destAdd = destAdd;

        bufferNumber = 0;
        windowStart = 0;
        totalCount = 0;

        windowPackets = new ArrayBlockingList<>(windowLength);
        windowTimers = new DelayQueue<>();
        packets = new LinkedBlockingQueue<>();
        getPacket();
        pool = Executors.newFixedThreadPool(2);
        pool.execute(() -> inputToWindow());
        pool.execute(() -> windowWorker());
//        pool.execute(() -> getPacket());

    }

    private void inputToWindow() {
        while (true) {
            try {
                windowPackets.awaitNotFull();
//                packets.awaitNotEmpty();  // Blocking

                Packet packet = packets.take();
                packet.setSeqNumber(bufferNumber);
                bufferNumber = nextNumber(bufferNumber);

                // Blocking
                TimedPacket timedPacket = new TimedPacket(packet);
                //Add packet to both of the window components:
                windowPackets.add(timedPacket);
                windowTimers.add(timedPacket);
            } catch (InterruptedException e) {
                System.out.println("Terminating feeder"); //--> DEBUG
                return;
            }
        }
    }

    public abstract void sendPacket(Packet p);


    private void windowWorker() {
        while (true) {
            try {
                // Wait for next packet to expire

                TimedPacket timedPacket = windowTimers.take(); // Blocking

                sendPacket(timedPacket.getPacket());


                // renew the delay on the packet and feed back into schedule
                windowTimers.put(timedPacket.repeat());
            } catch (InterruptedException e) {
                System.out.println("Terminating scheduleHandler"); //DEBUG
                return;
            }
        }
    }


    private void getPacket() {
        try {
            String filename = "input.txt";
            List<String> lines = Files.readAllLines(new File(filename).toPath());
            for (String line : lines.subList(0, 100)) {
                try {
//                    packets.awaitNotFull(); // Blocking

//                    System.out.println("[DEBUG] ADDING : " + line);

                    Packet p = new Packet(srcAdd, destAdd, line);
                    packets.put(p);
                } catch (InterruptedException e) {

                }

            }
        } catch (IOException e) {
            System.out.println("Cannot read input file");
        }
    }


    public boolean ack(int number) {
        boolean result;
        int relative = relativeNumber(number);
        System.out.println("[ACK] :" + String.valueOf(number) + "   " + String.valueOf(relative));
        if (0 < relative && relative < windowLength + 1) {
            for (int i = 0; i < relative; i++) {
                TimedPacket timedPacket = windowPackets.remove();
                windowStart = nextNumber(windowStart);
                windowTimers.remove(timedPacket);
            }
            totalCount += relative;
            System.out.println("[INFO] PACKETS SUCCESSFULLY SENT AND ACK RECEIVED COUNT :" + String.valueOf(totalCount) + " SRC : " + String.valueOf(convert_into_number(srcAdd))
                    + " DES : " + String.valueOf(convert_into_number(destAdd)));
            result = true;
        } else {
            result = false;
        }
        return result;
    }


    private int convert_into_number(String binary_segment) {
        int number = 0;
        int len = binary_segment.length();
        for (int i = 0; i < len; i++) {
            number = number * 2 + (binary_segment.charAt(i) - '0');
        }
        return number;
    }


    public void nak(int number) {
        int relative = relativeNumber(number);
        if (relative < windowLength) {
            TimedPacket timedPacket = windowPackets.get(relative);
            windowTimers.remove(timedPacket);

            // expire the timer for the packet and send it immediately
            windowTimers.add(timedPacket.reset());
        }
    }


    public int nextNumber(int number) {
        return (number + 1) % sequenceLength;
    }

    public int relativeNumber(int number) {
        return (number - windowStart + sequenceLength) % sequenceLength;
    }

}
