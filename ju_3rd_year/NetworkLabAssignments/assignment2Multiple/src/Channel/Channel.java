package Channel;

import Packet.Packet;
import Utils.ArrayBlockingList;

public class Channel {

    private ArrayBlockingList<String> messageSenderQueue;
    private ArrayBlockingList<String> messageReceiverQueue;

    public Channel() {

        // unbounded queue
        this.messageSenderQueue = new ArrayBlockingList<>(10);
        this.messageReceiverQueue = new ArrayBlockingList<>(10);
    }

    public void addSender(String content) throws InterruptedException {

        messageSenderQueue.awaitNotFull();
        messageSenderQueue.put(content);
    }

    public void addReceiver(String content) throws InterruptedException {

        messageReceiverQueue.awaitNotFull();
        messageReceiverQueue.put(content);
    }


    // for receiver or server
    public String getPacketSender(String desAdd) throws InterruptedException {
        messageSenderQueue.awaitNotEmpty();
        String content = messageSenderQueue.peek(); // blocking
        if (Packet.getDesAdd(content).equals(desAdd))
            return messageSenderQueue.take();
        else return null;
    }

    public String getPacketReceiver(String srcAdd) throws InterruptedException {
        messageReceiverQueue.awaitNotEmpty();
        String content = messageSenderQueue.peek(); //blocking
        if (Packet.getSrcAdd(content).equals(srcAdd))
            return messageReceiverQueue.take();
        return null;
    }


}
