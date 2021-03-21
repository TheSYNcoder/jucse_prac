package Server;

import Packet.Packet;
import Utils.ArrayBlockingList;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public abstract class ReceiverWindow {

    private final ArrayBlockingList<Packet> window;

    private final ExecutorService executor;

    private int windowLength;
    private int sequenceLength;
    private int windowStart;
    private int expectedNumber;
    private String srcAdd;
    private String destAdd;
    private boolean goback;

    public ReceiverWindow(int windowLength, int sequenceLength, String srcAdd, String destAdd, boolean goback) {
        this.windowLength = windowLength;
        this.sequenceLength = sequenceLength;
        this.srcAdd = srcAdd;
        this.destAdd = destAdd;
        window = new ArrayBlockingList<Packet>(windowLength);
        windowStart = 0;
        expectedNumber = 0;
        this.goback = goback;

        executor = Executors.newSingleThreadExecutor();
        executor.execute(() -> windowToOutput());

    }

    /*
     * Thread wise
     * continuous movement of
     * data packets.
     *
     */


    public abstract void sendPacket(Packet p);


    private void windowToOutput() {
        while (true) {
            try {

                window.awaitNotEmpty();
                int size = window.size();

                for (int i = 0; i < size; i++) {
                    Packet p = window.remove();
                    windowStart = nextNumber(windowStart);


                    // output the packet : can implement showing in console
                    System.out.println("[INFO] Receiver : " + p);
                }

                // Send ACK
                Packet ack = Packet.makeAck(windowStart, srcAdd, destAdd);
                sendPacket(ack);

            } catch (InterruptedException e) {

            }
        }
    }


    public void receive(Packet p) {
        if (goback)
            gobackN(p);
        else
            selectiveRepeat(p);
    }


    public void gobackN(Packet packet) {
        int seqNumber = packet.getSeqNumber();

        if (seqNumber == expectedNumber) {
            // append to window for outputing
            window.set(0, packet);
            expectedNumber = nextNumber(expectedNumber);
        } else {
            Packet nakn = Packet.makeNakN(expectedNumber, srcAdd, destAdd);
            sendPacket(nakn);
        }

        // else silently discard
    }


    public void selectiveRepeat(Packet packet) {
        int packetNum = packet.getSeqNumber();
        int numberPos = posInWindow(packetNum);
        int expectedPos = posInWindow(expectedNumber);

        if (numberPos < expectedPos) {
            window.set(numberPos, packet);
        } else if (numberPos == expectedPos) {
            window.set(numberPos, packet);
            expectedNumber = nextNumber(expectedNumber);
        } else if (numberPos < windowLength) {
            while (expectedNumber != packetNum) {
                Packet nak = Packet.makeNak(expectedNumber, srcAdd, destAdd);
                sendPacket(nak);
                expectedNumber = nextNumber(expectedNumber);
            }
            window.set(numberPos, packet);
            expectedNumber = nextNumber(expectedNumber);
        } else {
            Packet ack = Packet.makeAck(windowStart, srcAdd, destAdd);
            sendPacket(ack);
        }


    }


    private int cyclicShift(int number, int shift, int modulo) {
        int n = (number + shift) % modulo;
        return n < 0 ? n + modulo : n;
    }

    private int posInWindow(int number) {
        return cyclicShift(number, -windowStart, sequenceLength);
    }


    private int nextNumber(int windowStart) {
        return (windowStart + 1) % sequenceLength;
    }
}
