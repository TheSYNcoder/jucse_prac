package Server;

import Channel.Channel;
import Node.Sender;
import Packet.Packet;

import java.util.concurrent.CountDownLatch;

public class Server {

    private final ReceiverWindow window;
    private String srcAddress;
    private String destAddress;
    private int windowLength;
    private int seqLength;
    private Channel ch;
    private Sender sender;
    private boolean gobackn;

    private CountDownLatch latch;
    Listener listener;


    public static double drop_rate = 0.15;


    public Server(String srcAddress, String destAddress, int windowLength, int seqLength, Channel ch, boolean gobackn) {

        latch = new CountDownLatch(1);
        listener = new Listener();
        listener.setDaemon(true);
        listener.start();


        this.srcAddress = srcAddress;
        this.destAddress = destAddress;
        this.windowLength = windowLength;
        this.seqLength = seqLength;
        this.gobackn = gobackn;
        this.ch = ch;
        sender = new Sender(ch, true);
        window = new ReceiverWindow(windowLength, seqLength, srcAddress, destAddress, gobackn) {
            @Override
            public void sendPacket(Packet p) {
                sender.add(p);
            }
        };

        listener.go();

    }

    public void onReceive(Packet p) {
        window.receive(p);
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
                    String content = ch.getPacketSender(destAddress);
                    if (content == null) continue;
                    Packet p = Packet.toPacket(content);
                    onReceive(p);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }


}
