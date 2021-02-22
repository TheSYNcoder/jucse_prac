package Client;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Base64;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Client {

    public static void main(String[] args) {
        try {
            SocketChannel client = SocketChannel.open(new InetSocketAddress("localhost", 9090));

            ExecutorService service = Executors.newSingleThreadExecutor();
//            service.execute(() -> listen(client));
            listen(client);
            service.execute(() -> send(client));


        } catch (IOException e) {
            System.out.println("IO Exception");
        }
    }

    private static void send(SocketChannel socketChannel) {
        Scanner sc = new Scanner(System.in);

        try {

            while (true) {
                System.out.print("$ ");
                String in = sc.nextLine();
                if (in.isEmpty()) {
                    System.out.println();
                    continue;
                }

                if (in.equals("FTP SEND")) {
                    String in2 = sc.nextLine();
                    ArrayList<String> files = new ArrayList<>(Arrays.asList(new File("src/Client/Data").list()));
                    if (!files.contains(in2)) {
                        System.out.println("File does not exist");
                        continue;
                    }
//                    in += " " + in2;
//                    ByteBuffer buffer = ByteBuffer.allocate(1024);
//                    buffer.put(in.getBytes());
//                    buffer.flip();
//                    socketChannel.write(buffer);
//                    buffer.clear();
                    for (File file : new File("src/Client/Data").listFiles()) {
                        if (file.getName().equals(in2)) {
                            in += " " + file.getName() + " ";
                            byte[] lines = Files.readAllBytes(Paths.get(new File(file.getPath()).toURI()));
                            byte[] base64 = Base64.getEncoder().encode(lines);
                            byte[] all = new byte[base64.length + in.getBytes().length];
                            ByteBuffer buffer = ByteBuffer.wrap(all);

                            buffer.put(in.getBytes());
                            buffer.put(base64);
                            buffer.flip();
                            socketChannel.write(buffer);

                            buffer.clear();
                            socketChannel.read(buffer);
                            StringBuilder stringBuilder = new StringBuilder();
                            buffer.flip();
                            byte[] bytes = new byte[buffer.limit()];
                            buffer.get(bytes);
                            stringBuilder.append(new String(bytes));
                            if (stringBuilder.toString().length() > 0) {
                                System.out.print(stringBuilder.toString());
                            }
                            System.out.println();
                            break;
                        }
                    }
                    continue;
                }


                String delims = "[ ]+";
                String[] tokens = in.split(delims);
                if (tokens[0].equals("FTP") && tokens[1].equals("RECV")) {
                    if (tokens.length != 3) {
                        System.out.println("SYNTAX : FTP RECV <file>");
                        continue;
                    }

                    ByteBuffer buffer = ByteBuffer.allocate(1024);
                    buffer.put(in.getBytes());
                    buffer.flip();
                    socketChannel.write(buffer);

                    buffer.clear();
                    buffer = ByteBuffer.allocate(65536);
                    socketChannel.read(buffer);
                    buffer.flip();
                    byte[] bytes = new byte[buffer.limit()];
                    buffer.get(bytes);
                    StringBuilder stringBuilder = new StringBuilder();
                    stringBuilder.append(new String(bytes));
                    String file_content = stringBuilder.toString();
                    byte[] res = Base64.getDecoder().decode(file_content.getBytes());
                    String x = new String(res);
                    if (x.startsWith("ERROR")) {
                        System.out.println(x);
                        continue;
                    }
                    try {
                        File file = new File("src/Client/Data/" + tokens[2]);
                        file.createNewFile();
                        FileOutputStream os = new FileOutputStream(file.getPath());
                        os.write(res);
                        System.out.println("FILE " + tokens[2] + " RECEIVED");

                    } catch (IOException e) {
                        System.out.println("File cannot be created");
                        continue;

                    }
                    System.out.println();

                    continue;

                }


                ByteBuffer buffer = ByteBuffer.allocate(1024);
                buffer.put(in.getBytes());
                buffer.flip();
                socketChannel.write(buffer);

                buffer.clear();
                socketChannel.read(buffer);
                StringBuilder stringBuilder = new StringBuilder();
                buffer.flip();
                byte[] bytes = new byte[buffer.limit()];
                buffer.get(bytes);
                stringBuilder.append(new String(bytes));


                if (stringBuilder.toString().length() > 0) {
                    System.out.print(stringBuilder.toString());
                }
                System.out.println();


            }
        } catch (IOException e) {

        }
    }

    private static void listen(SocketChannel socketChannel) {
        try {
            ByteBuffer buffer = ByteBuffer.allocate(1024);


            StringBuilder stringBuilder = new StringBuilder();
            buffer.clear();
            int read = 0;

            read = socketChannel.read(buffer);
            // for reading
            buffer.flip();
            byte[] bytes = new byte[buffer.limit()];
            buffer.get(bytes);
            stringBuilder.append(new String(bytes));

            if (stringBuilder.toString().length() > 0) {
                System.out.print(stringBuilder.toString());
//                    System.out.println();

            }


        } catch (IOException e) {

        }
    }
}
