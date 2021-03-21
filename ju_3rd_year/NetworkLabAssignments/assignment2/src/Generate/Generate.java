package Generate;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Random;

public class Generate {
    public static void main(String[] args) {
        String filename = "input.txt";
        try {
            Files.write(Paths.get(filename), "".getBytes(), StandardOpenOption.CREATE);
        } catch (IOException e) {
            System.out.println(e);
        }


        int number_of_data = 10000;
        for (int i = 0; i < number_of_data; i++) {
            int size = (int) (64 + Math.random() * 1000);
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
