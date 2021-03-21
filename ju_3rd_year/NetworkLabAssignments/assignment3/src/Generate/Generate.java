package Generate;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Random;

public class Generate {

    public static void main(String[] args) {
        ArrayList<String> filenames = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            String filename = "files/input" + String.valueOf(i + 1) + ".txt";
            filenames.add(filename);
        }

        for (String filename : filenames) {
            try {
                Files.write(Paths.get(filename), "".getBytes(), StandardOpenOption.CREATE);
            } catch (IOException e) {
                System.out.println(e);
            }

            int numberLines = 200;
            for (int i = 0; i < numberLines; i++) {
                int size = (int) (64 + Math.random() * 100);
                String bits = new Random().ints(0, 2).parallel().limit(size).collect(StringBuilder::new, StringBuilder::append, StringBuilder::append).toString();
                bits += '\n';
                try {
                    Files.write(Paths.get(filename), bits.getBytes(), StandardOpenOption.APPEND);
                } catch (IOException e) {
                    System.out.println(e);
                }
            }
        }
    }
}
