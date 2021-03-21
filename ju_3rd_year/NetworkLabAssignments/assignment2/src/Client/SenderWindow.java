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
    private boolean gobackn;
    private boolean flag;


    private long startTime;

    public SenderWindow(int windowLength, int sequenceLength, String srcAdd, String destAdd, boolean gobackn) {
        this.windowLength = windowLength;
        this.sequenceLength = sequenceLength;
        this.srcAdd = srcAdd;
        this.destAdd = destAdd;
        this.gobackn = gobackn;

        bufferNumber = 0;
        windowStart = 0;
        totalCount = 0;
        flag = false;

        windowPackets = new ArrayBlockingList<>(windowLength);
        windowTimers = new DelayQueue<>();
        packets = new LinkedBlockingQueue<>();
        getPacket();
        pool = Executors.newFixedThreadPool(2);
        pool.execute(() -> inputToWindow());
        pool.execute(() -> windowWorker());
//        pool.execute(() -> getPacket());

        startTime = System.currentTimeMillis();

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

//                if (timedPacket.getPacket().getSeqNumber() == windowStart && gobackn && flag) {
////                    windowStart = nextNumber(windowStart);
//                    for (int i = windowStart; i < windowPackets.size(); i++) {
//                        TimedPacket tp = windowPackets.get(windowStart);
//                        windowTimers.remove(tp);
//                        windowTimers.add(tp.reset());
//                    }
//                    flag = false;
//                }
//                if (timedPacket.getPacket().getSeqNumber() == windowStart && !flag) {
//                    flag = true;
//                }
                sendPacket(timedPacket.getPacket());
                System.out.println("[INFO] Packet Sending " + timedPacket.getPacket());


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
            for (String line : lines.subList(0, 1000)) {
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
            System.out.println("[INFO] PACKETS SUCCESSFULLY SENT AND ACK RECEIVED COUNT :" + String.valueOf(totalCount));
            if (totalCount > 10) {
                long end = System.currentTimeMillis();
                System.out.println("Time taken in seconds :" + String.valueOf((end - startTime)));


            }
            result = true;

        } else {
            result = false;
        }
        return result;
    }


    public void nak(int number, boolean goback) {
        int relative = relativeNumber(number);

        if (relative < windowLength) {
            if (goback) {
                for (int i = relative; i < windowPackets.size(); i++) {
                    TimedPacket tp = windowPackets.get(i);
                    windowTimers.remove(tp);
                    windowTimers.add(tp.reset());
                }
            } else {
                TimedPacket timedPacket = windowPackets.get(relative);
                windowTimers.remove(timedPacket);

                // expire the timer for the packet and send it immediately
                windowTimers.add(timedPacket.reset());
            }
        }
    }


    public int nextNumber(int number) {
        return (number + 1) % sequenceLength;
    }

    public int relativeNumber(int number) {
        return (number - windowStart + sequenceLength) % sequenceLength;
    }

}
