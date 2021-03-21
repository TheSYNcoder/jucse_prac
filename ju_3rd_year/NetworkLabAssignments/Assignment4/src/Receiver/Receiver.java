package Receiver;

import Channel.Channel;
import Packet.Packet;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Receiver {

    private int num_stations;
    private ExecutorService executor;
    private Channel channel;
    private int[][] walsh_table;
    private int bits_transferred;
    private long time;

    public Receiver(int num_stations, Channel channel, int[][] walsh_table) {
        this.num_stations = num_stations;
        this.channel = channel;
        this.walsh_table = walsh_table;
        bits_transferred = 0;
        time = System.nanoTime();
        executor = Executors.newSingleThreadExecutor();
        executor.execute(() -> onReceive());


    }


    public void onReceive() {
        while (true) {

            String data = channel.removeData();
            if (data == null) continue;
            ArrayList<Integer> decoded = Packet.decodePacket(data);


            for (int i = 0; i < num_stations; i++) {
                int tmp = 0;
                for (int j = 0; j < num_stations; j++) {
                    tmp += walsh_table[i][j] * decoded.get(j);
                }
                tmp /= num_stations;

                if (tmp != 0)
                    System.out.println("data received :  " + String.valueOf(tmp));
                if (tmp == 1) {
                    System.out.println("[RECEIVER] SENDER : " + String.valueOf(i + 1) + " DATA : 1");
                    bits_transferred += 1;
                } else if (tmp == -1) {
                    System.out.println("[RECEIVER] SENDER : " + String.valueOf(i + 1) + " DATA : 0");
                    bits_transferred += 1;
                }


            }

            double time_taken = (System.nanoTime() - time) / 1000.0;

            System.out.println("[INFO] bits transferred : " + bits_transferred + " Time taken : " + time_taken);
            if (time_taken > 0)
                System.out.println(" Throughput : " + (double) (bits_transferred / time_taken));


        }
    }


}
