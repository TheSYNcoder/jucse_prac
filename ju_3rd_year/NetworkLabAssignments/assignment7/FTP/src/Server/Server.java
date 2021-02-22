package Server;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Base64;
import java.util.Iterator;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server {

    private final int port;
    private ServerSocketChannel serverSocket;
    private Selector selector;
    private ByteBuffer buffer = ByteBuffer.allocate(1024);
    private ExecutorService executor;


    public Server(int port) throws IOException {
        this.port = port;
        this.serverSocket = ServerSocketChannel.open();
        this.serverSocket.socket().bind(new InetSocketAddress("localhost", port));
        this.serverSocket.configureBlocking(false);
        this.selector = Selector.open();


        this.serverSocket.register(selector, SelectionKey.OP_ACCEPT);
        executor = Executors.newSingleThreadExecutor();
        executor.execute(() -> listen());
    }


    private void listen() {
        try {
            System.out.println("[INFO] Server starting on port " + this.port + " ....");
            Iterator<SelectionKey> iterator;
            SelectionKey key;
            while (this.serverSocket.isOpen()) {
                selector.select();
                iterator = this.selector.selectedKeys().iterator();
                while (iterator.hasNext()) {
                    key = iterator.next();
                    iterator.remove();
                    if (key.isAcceptable()) {
                        handleAccept(key);
                    } else if (key.isReadable()) {
                        handleRead(key);
                    }

                }
            }
        } catch (IOException e) {
            System.out.println("IOException, server of port " + this.port + " terminating. Stack trace:");
            e.printStackTrace();
        }
    }


    private final ByteBuffer welcomeMessage = ByteBuffer.wrap("Welcome to the FTP server\n".getBytes());

    private void handleAccept(SelectionKey key) throws IOException {
        SocketChannel socketChannel = ((ServerSocketChannel) key.channel()).accept();
        String address = (new StringBuilder(socketChannel.socket().getInetAddress().toString())).append(":").append(socketChannel.socket().getPort()).toString();
        socketChannel.configureBlocking(false);
        socketChannel.register(selector, SelectionKey.OP_READ, address);
        socketChannel.write(welcomeMessage);
        welcomeMessage.rewind();
        System.out.println("[INFO] Accepted connection from :" + address);
    }

    /**
     * Commands supported
     * FTP LIST
     * FTP DSIZ
     * FTP RECV <FILE>
     * FTP DELE <FILE>
     * FTP SEND <FILE>
     *
     * @param client_message
     * @return bytes array of file or array message
     */
    private byte[] analyze(String client_message) {
        String delims = "[ ]+";
        String[] tokens = client_message.split(delims);
        byte[] bytes;
        ArrayList<String> valid2Tokens = new ArrayList<>(Arrays.asList("DSIZ", "LIST", "EXIT", "HELP"));
        ArrayList<String> valid3Tokens = new ArrayList<>(Arrays.asList("RECV", "DELE"));
        if (tokens.length == 0 || tokens.length == 1) {
            bytes = "ERROR 501 - SYNTAX ERROR".getBytes();
            return bytes;
        }
        if (!tokens[0].equals("FTP")) {
            bytes = "ERROR 501 - SYNTAX ERROR".getBytes();
            return bytes;
        }
        if (tokens.length == 2) {
            if (!valid2Tokens.contains(tokens[1])) {
                bytes = "ERROR 504 - COMMAND NOT IMPLEMENTED".getBytes();
                return bytes;
            }
            if (tokens[1].equals("LIST")) {
                File[] files = new File("src/Server/Data").listFiles();
                String res = "\tLISTING --\n\n";
                for (File file : files) {
                    res += file.getName() + "\n";
                }
                res += "\n200 OK .\n";
                bytes = res.getBytes();
                return bytes;
            }

            if (tokens[1].equals("DSIZ")) {
                File[] files = new File("src/Server/Data").listFiles();
                double sum = 0;
                for (File file : files) {
                    sum += (double) file.length() / (1024 * 1024);
                }
                String res = "\nDirectory size : " + String.valueOf(sum) + "MB .\n";
                res += "\n200 OK .\n";
                bytes = res.getBytes();
                return bytes;
            }

            if (tokens[1].equals("HELP")) {
                String ret = "***********************\n";
                ret += "Commands supported -----\n\n";
                ret += "FTP LIST          - lists all files in server memory\n";
                ret += "FTP DSIZ          - gets the total directory size in server memory\n";
                ret += "FTP RECV <file>   - gets the required file from server and stores it in client\n";
                ret += "FTP SEND <file>   - sends the asked file from the client memory to the server\n";
                ret += "FTP DELE <file>   - deletes the asked file in the server\n";
                ret += "\n\n*******************************\n";
                bytes = ret.getBytes();
                return bytes;
            }

            if (tokens[1].equals("EXIT")) {
                return null;
            }
        }
        if (tokens.length == 3) {

//            if (!valid3Tokens.contains(tokens[1])) {
//                bytes = "ERROR 504 - COMMAND NOT IMPLEMENTED".getBytes();
//                return bytes;
//            }

            if (tokens[1].equals("DELE")) {
                String filename = tokens[2];
                ArrayList<String> files = new ArrayList<>(Arrays.asList(new File("src/Server/Data").list()));
                if (!files.contains(filename)) {
                    bytes = "ERROR 400 - FILE NOT FOUND".getBytes();
                    return bytes;
                }
                for (File file : new File("src/Server/Data").listFiles()) {
                    if (file.getName().equals(filename)) {
                        file.delete();
                        bytes = "200 OK - FILE DELETED".getBytes();
                        return bytes;
                    }
                }
            }
            if (tokens[1].equals("RECV")) {
                String filename = tokens[2];
                bytes = "ERROR".getBytes();

                ArrayList<String> files = new ArrayList<>(Arrays.asList(new File("src/Server/Data").list()));
                if (!files.contains(filename)) {
                    bytes = "ERROR 400 - FILE NOT FOUND".getBytes();
                    byte[] base64 = Base64.getEncoder().encode(bytes);
                    return base64;
                }
                for (File file : new File("src/Server/Data").listFiles()) {
                    if (file.getName().equals(filename)) {
                        try {
                            bytes = Files.readAllBytes(Paths.get(new File(file.getPath()).toURI()));
                            break;

                        } catch (IOException e) {
                            bytes = "ERROR 500 - IO Exception".getBytes();
                            System.out.println("ERROR IO Exception in reading file : " + file.getName());
                            e.printStackTrace();
                        }

                    }
                }

                byte[] base64 = Base64.getEncoder().encode(bytes);
                return base64;

            }

        }

//        if (tokens[0].equals("FTP") && tokens[1].equals("SEND")) {
//            String res = "";
//            String filename = tokens[2];
//            for (int i = 3; i < tokens.length; i++)
//                res += tokens[i];
//            try {
//                File file = new File("src/Server/Data/" + filename);
//                file.createNewFile();
//                FileWriter writer = new FileWriter("src/Server/Data/" + filename);
//                writer.write(res);
//                writer.close();
//                bytes = "200 OK .".getBytes();
//                return bytes;
//
//            } catch (IOException e) {
//                System.out.println("File cannot be created");
//                bytes = "ERROR 500 - SENDING FAILED".getBytes();
//                return bytes;
//            }
//
//
//        }


        bytes = "ERROR 501 - SYNTAX ERROR".getBytes();

        return bytes;


    }

    private byte[] makeFileandWrite(String filename, byte[] content) {
        byte[] bytes;
        try {
            File file = new File("src/Server/Data/" + filename);
            file.createNewFile();
            FileOutputStream os = new FileOutputStream(file.getPath());
            os.write(content);
            bytes = "200 OK- FILE WRITTEN".getBytes();
            return bytes;
        } catch (IOException e) {
            System.out.println("File cannot be created");
            bytes = "ERROR 500 - SENDING FAILED".getBytes();
            return bytes;
        }

    }

    private void handleRead(SelectionKey key) throws IOException {
        SocketChannel socketChannel = ((SocketChannel) key.channel());
        StringBuilder stringBuilder = new StringBuilder();

        buffer.clear();
        int read = 0;
        try {
            socketChannel.read(buffer);
            // for reading
            buffer.flip();
            byte[] bytes = new byte[buffer.limit()];
            buffer.get(bytes);
            stringBuilder.append(new String(bytes));
            buffer.clear();

        } catch (Exception e) {
            key.cancel();
            read = -1;
        }
        String client_message = stringBuilder.toString();
        System.out.println(client_message);
        String[] tokens = client_message.split("[ ]+");


        if (tokens[0].equals("FTP") && tokens[1].equals("SEND")) {
            String filename = tokens[2];
            int index = client_message.indexOf(filename);

            index += filename.length();
            index++;
            String content = client_message.substring(index);
            byte[] res = Base64.getDecoder().decode(content.getBytes());
            byte[] status = makeFileandWrite(filename, res);
            System.out.println("[INFO] SERVER GOT MESSAGE " + key.attachment());
            socketChannel.write(ByteBuffer.wrap(status));
            return;


        }


        byte[] bytes = analyze(stringBuilder.toString());

        if (bytes == null) {
            socketChannel.write(ByteBuffer.wrap("EXITING SOCKET BYE".getBytes()));
            socketChannel.close();
        }


        socketChannel.write(ByteBuffer.wrap(bytes));
        System.out.println("[INFO] SERVER GOT MESSAGE " + key.attachment());


    }

    public static void main(String[] args) {
        try {
            new Server(9090);
        } catch (IOException e) {

        }
    }
}
