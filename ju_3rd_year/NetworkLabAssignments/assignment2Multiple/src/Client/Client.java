package Client;

import Channel.Channel;
import Node.Sender;
import Packet.Packet;

import java.util.concurrent.CountDownLatch;

public class Client {

    private final SenderWindow window;
    private String srcAddress;
    private String destAddress;
    private int windowLength;
    private int seqLength;
    private Channel ch;
    private Sender sender;
    private boolean gobackn;

    private CountDownLatch latch;
    Listener listener;

    public Client(String srcAddress, String destAddress, int windowLength, int seqLength, Channel ch, boolean gobackn) {
        latch = new CountDownLatch(1);
        listener = new Listener();
        listener.setDaemon(true);
        listener.start();


        this.srcAddress = srcAddress;
        this.destAddress = destAddress;
        this.windowLength = windowLength;
        this.seqLength = seqLength;
        this.ch = ch;
        this.gobackn = gobackn;

        sender = new Sender(ch, false);
        window = new SenderWindow(windowLength, seqLength, srcAddress, destAddress) {
            @Override
            public void sendPacket(Packet p) {
                sender.add(p);
            }
        };
        listener.go();
    }

    public void onReceive(Packet packet) {
        System.out.println("[INFO] onReceive   : " + packet);
        switch (packet.type) {
            case "ACK": {
                window.ack(packet.getSeqNumber()); // implement number
                System.out.println("[INFO] ACK REMOVED : " + String.valueOf(packet.getSeqNumber()));
                break;
            }
            case "NAK": {
                window.nak(packet.getSeqNumber());
                break;
            }

        }
    }


    class Listener extends Thread {


        public void go() {
            latch.countDown();
        }

        /*
         * Listen for incoming packets and inform receivers
         */
        @Override
        public void run() {
            try {
                latch.await();
                // Endless loop: attempt to receive packet, notify receivers, etc
                while (true) {
                    String content = ch.getPacketReceiver(srcAddress);
                    if (content == null) continue;

                    Packet p = Packet.toPacket(content);
                    System.out.println("[PACKET RECEIVED]" + p);
                    onReceive(p);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
