package Sender;

import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.LinkedBlockingQueue;


public class SendBuffer {

    class Pair {
        Integer k;
        Integer v;

        public Pair(Integer k, Integer v) {
            this.k = k;
            this.v = v;
        }

        public Integer getData() {
            return k;
        }

        public Integer getNode() {
            return v;
        }
    }

    protected Set<Integer> senderNodes;
    public LinkedBlockingQueue<Pair> senderData;
    protected Boolean condition;
//    private ExecutorService executor;


    public SendBuffer() {
        condition = false;
        senderNodes = new HashSet<Integer>();
        senderData = new LinkedBlockingQueue<>();
//        executor = Executors.newSingleThreadExecutor();
//        executor.execute(() -> sendOnFull());
    }

    public void addData(Integer data, Integer node_index) {


        try {
            if (senderNodes.contains(node_index)) {
                condition = true;
            }
            senderNodes.add(node_index);
            Pair p = new Pair(data, node_index);
            senderData.put(p);
        } catch (InterruptedException e) {
            System.out.println("[WARN] SendBuffer Interrupted");
        }

    }

//    public abstract void sendData();

//    private synchronized void sendOnFull() {
//        while (true) {
//
//            condition = false;
////            senderNodes.clear();
//            sendData();
//
//        }
//    }
}
