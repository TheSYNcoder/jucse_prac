package Server;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class Test {
    public static void main(String[] args) throws IOException {
//        File[] files = new File("src/Server/Data").listFiles();
//        for (File file : files) {
//            System.out.println(file.getName());
//        }

        byte[] lines = Files.readAllBytes(Paths.get(new File("src/Server/Data/download.jpeg").toURI()));
        System.out.println(lines.length);
//        FileOutputStream os = new FileOutputStream(new File("src/Server/Data/file.txt").getPath());
        byte[] base64 = Base64.getEncoder().encode(lines);
//        os.write(lines);
        byte[] mess = "content".getBytes();
        byte[] all = new byte[mess.length + base64.length];
        ByteBuffer buff = ByteBuffer.wrap(all);

        buff.put(mess);
        buff.put(base64);
        buff.flip();

        buff.get(all);
        String big = new String(all);
        String small = new String(mess);
        System.out.println(small);
        System.out.println(big.indexOf(small));


        int index = big.indexOf(small);
//        for (int i = 0; i < small.length(); i++) {
//            if (big.charAt(index + i) == small.charAt(i)) {
//
//            }
//        }
        System.out.println(big.length());
        System.out.println(index);

        String content = big.substring(small.length());
        byte[] con = Base64.getDecoder().decode(content.getBytes());

        FileOutputStream os = new FileOutputStream(new File("src/Server/Data/nn.jpeg").getPath());
        os.write(con);

    }
}
