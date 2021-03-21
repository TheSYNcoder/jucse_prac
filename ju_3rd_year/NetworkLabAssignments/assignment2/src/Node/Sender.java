package Node;


import Channel.Channel;
import Packet.Packet;

import java.util.Date;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;

/*
 *
 *  A class for sending packets
 *  with buffer
 */
public class Sender {

    private Channel ch;
    private Boolean server;
    private LinkedBlockingQueue<String> bh;

    private final ExecutorService executor;

    public Sender(Channel ch, Boolean server) {
        this.server = server;
        this.ch = ch;
        bh = new LinkedBlockingQueue<>();
        executor = Executors.newSingleThreadExecutor();
        executor.execute(() -> sender());

    }


    public void add(Packet packet) {

        String content = packet.toCodeWord();
        bh.add(content);

    }


    private void sender() {
        ReentrantLock lock = new ReentrantLock();
//        Condition sendTime = lock.newCondition();

        while (true) {
            lock.lock();
            try {
//                bh.awaitNotEmpty();
                String content = bh.take();
//                sendTime.awaitUntil(nextSendTime());


                /**
                 *  Inject Random Error
                 *
                 */

//                if (new Random().nextDouble() < 0.08) { //drop rate
//                    content = CRC.addError(content);
//                }


                /**
                 *  Drop packet by a random probability
                 */
                if (new Random().nextDouble() < 0.10) { //drop rate
                    System.out.println("[INFO] Packet " + Packet.toPacket(content) + "Lost");
                    continue;
                }


                if (server) {
                    ch.addReceiver(content);
                } else {
                    ch.addSender(content);
                }
            } catch (InterruptedException e) {
                System.out.println("Sender failed");
            } finally {
                lock.unlock();
            }
        }
    }

    /*
     *   Used for sending packets with random delay
     *   ranging from 0 seconds to 3 seconds.
     *
     */

    private Date nextSendTime() {
        int delaySeconds = (int) (Math.random() * 4);
        return new Date(System.currentTimeMillis() + TimeUnit.SECONDS.toMillis(delaySeconds));
    }
}
