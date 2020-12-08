package Channel;

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

    public String getPacketSender() throws InterruptedException {
        messageSenderQueue.awaitNotEmpty();
        return messageSenderQueue.take();
    }

    public String getPacketReceiver() throws InterruptedException {
        messageReceiverQueue.awaitNotEmpty();
        return messageReceiverQueue.take();
    }


}
