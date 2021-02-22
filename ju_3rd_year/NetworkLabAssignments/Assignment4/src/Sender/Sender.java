package Sender;

import Channel.Channel;
import Packet.Packet;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Sender extends SendBuffer {

    private int sender_index; // determines the chip sequence position in the walsh table
    private int[][] walsh_table; // walsh table for sender chip sequence
    private ArrayBlockingQueue<Integer> buffer;
    private Channel channel;
    private ExecutorService executor;
    private int num_stations;


    public Sender(int sender_index, int[][] walsh_table, Channel channel, int num_stations) {
        this.sender_index = sender_index;
        this.walsh_table = walsh_table;
        this.channel = channel;
        this.num_stations = num_stations;
        buffer = new ArrayBlockingQueue<>(100);
        executor = Executors.newFixedThreadPool(3);
        executor.execute(() -> fillBuffer());
//        fillBuffer();
        executor.execute(() -> sendDataInBuffer());
        executor.execute(() -> sendData());
    }

    private void fillBuffer() {
        // generating a random number of frames
        int random_frames = 1000;
        for (int i = 0; i < random_frames; i++) {
            try {
                int randomBit = getRandomBit();
                buffer.put(randomBit);
            } catch (InterruptedException e) {

            }
        }
    }

    private void sendDataInBuffer() {
        while (true) {

            try {
                Integer data = buffer.take();
                addData(data, sender_index);
            } catch (InterruptedException e) {
                System.out.println("[WARN] Interrupted in Sender");
            }

        }
    }

    private int getRandomBit() {
        int x = (int) (Math.random() * 2);
        if (x == 0) x = -1;
        return x;
    }


    public void sendData() {

        while (true) {

//            if (!condition) continue;
//            condition = false;
//            senderNodes.clear();
            if (senderData.size() < num_stations) continue;


            ArrayList<Integer> encoded = new ArrayList<>();
            for (int i = 0; i < num_stations; i++)
                encoded.add(0);
            ArrayList<Integer> zeros = (ArrayList<Integer>) encoded.clone();
            int sz = num_stations;
            Set<Integer> ss = new HashSet<>();
            while (senderData.size() > 0) {
                try {
                    Pair pair = senderData.take();
                    Integer data = pair.getData();
                    Integer node_index = pair.getNode();
                    if (ss.contains(node_index)) break;
                    ss.add(node_index);
                    int tmp = 0;
                    for (int j = 0; j < num_stations; j++) {
                        tmp = walsh_table[node_index][j] * data;
                        int x = encoded.get(j);
                        encoded.set(j, tmp + x);
                    }
//                    encoded.set(node_index, tmp);
                    sz--;
                } catch (InterruptedException e) {
                }
            }

            if (encoded.equals(zeros)) continue;
//            System.out.println(encoded);
            String codeword = Packet.encodePacket(encoded);
            channel.addData(codeword);
        }

    }


}
