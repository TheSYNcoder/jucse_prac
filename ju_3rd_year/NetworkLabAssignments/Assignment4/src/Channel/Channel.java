package Channel;

import java.util.concurrent.LinkedBlockingQueue;

public class Channel {
    private LinkedBlockingQueue<String> messageSenderQueue;

    public Channel() {
        messageSenderQueue = new LinkedBlockingQueue<>();
    }

    public void addData(String data) {
        try {
            messageSenderQueue.put(data);
        } catch (InterruptedException e) {
        }

    }


    public String removeData() {

        try {
            String x = messageSenderQueue.take();
            return x;
        } catch (InterruptedException e) {
        }

        return null;
    }
}
