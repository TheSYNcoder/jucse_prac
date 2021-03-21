package Generate;


import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;


public class Gen {


    private static BlockingQueue<String> bq;

    public static synchronized void getLines() {
        try {
            String filename = "input.txt";
            List<String> lines = Files.readAllLines(new File(filename).toPath());


            int i = 0;
            for (String line : lines.subList(0, 100)) {
                try {
//                    bq.awaitNotFull();
                    bq.put(String.valueOf(i + 1) + line.substring(0, 5));
                    System.out.println(String.valueOf(i + 1) + line.substring(0, 5) + " inserted");
                    i += 1;
                } catch (InterruptedException e) {

                }
            }

        } catch (IOException e) {

        }


    }

    public static synchronized void takeLines() {
        try {
            while (true) {
//                bq.awaitNotEmpty();
                String line = bq.take();
                System.out.println(line + '\n');
            }
        } catch (InterruptedException e) {

        }

    }


    public static void main(String[] args) {
//        bq = new ArrayBlockingList<String>(10000);
        bq = new LinkedBlockingQueue<>(5);
        ExecutorService service = Executors.newFixedThreadPool(2);
        service.execute(() -> getLines());
        service.execute(() -> takeLines());


    }
}
