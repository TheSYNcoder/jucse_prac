package Run;

import Channel.Channel;
import Receiver.Receiver;
import Sender.Sender;

public class Worker {
    public int[][] walsh_table;
    private int num_stations;
    private Channel channel;

    public Worker(int num_stations, int[][] walsh_table) {
        this.walsh_table = walsh_table;
        this.num_stations = num_stations;
        channel = new Channel();
        start();
    }

    public void start() {
        for (int i = 0; i < num_stations; i++) {
            new Sender(i, walsh_table, channel, num_stations);
        }
        new Receiver(num_stations, channel, walsh_table);
    }
}
