package Server;

import Packet.*;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class DHCPServer {

    String address;
    int port;
    DatagramSocket socket;
    ArrayList<String> ips;
    byte[] buffer;

    ExecutorService executor;
    HashMap<String, String> macToIps;
    String serverAddress;


    public DHCPServer() throws IOException {

        serverAddress = "192.168.34.23";
        socket = new DatagramSocket(8067, InetAddress.getByName("0.0.0.0"));
        socket.setBroadcast(true);

        buffer = new byte[4096];
        macToIps = new HashMap<>();
        ips = new ArrayList<>();
        macToIps.put("01-23-45-67-89-AB-CD-EF", "192.0.4.5");
        macToIps.put("01-23-45-67-90-BC-DE-FG", "192.0.4.6");
        ips.add("192.0.4.5");
        ips.add("192.0.4.6");


        executor = Executors.newSingleThreadExecutor();
        executor.execute(() -> listen());

    }


    public String generateIp() {
        String Ip = "";
        for (int i = 0; i < 4; i++) {
            int sub = (int) (Math.random() * 255);
            Ip += String.valueOf(sub);
            if (i != 3) Ip += ":";
        }
        if (ips.contains(Ip)) {
            Ip = generateIp();
        } else {
            ips.add(Ip);
        }
        return Ip;
    }


    public void listen() {
        while (true) {
            try {
                System.out.println("DHCP Server " + serverAddress + " listening ...");
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                InetAddress address = packet.getAddress();
                int port = packet.getPort();

                // deduce the packet - can be either discover or request
                String received = new String(buffer).substring(0, packet.getLength());
                String type = BasePacket.getPacketType(received);

                if (type.equals("DHCPDiscover")) {

                    // create a DHCP Offer Packet
                    DHCPDiscoverPacket packet1 = DHCPDiscoverPacket.decode(received);

                    System.out.println("[INFO] Got DHCP discover packet from  port : " + packet.getPort() + " : " + packet.getSocketAddress() + " with mac address  : " + packet1.getMacaddr());

                    DHCPOfferPacket packet2 = DHCPOfferPacket.getDHCPOfferPacket(packet1.getMacaddr());
                    if (macToIps.containsKey(packet1.getMacaddr())) {
                        packet2.setSiaddr(serverAddress);
                        packet2.setYiaddr(macToIps.get(packet1.getMacaddr()));
                    } else {
                        String ip = generateIp();
                        macToIps.put(packet1.getMacaddr(), ip);
                        packet2.setSiaddr(serverAddress);
                        packet2.setYiaddr(ip);
                    }
                    buffer = packet2.toString().getBytes();
                    packet = new DatagramPacket(buffer, packet2.toString().length(), address, port);
                    socket.send(packet);
                    System.out.println("[INFO] Sent DHCP Offer Packet to address : " + address + " port: " + port);

                } else if (type.equals("DHCPRequest")) {

                    // Create a DHCP Ack packet
                    DHCPRequestPacket packet1 = DHCPRequestPacket.decode(received);

                    System.out.println("[INFO] Got DHCP Request packet from  port : " + packet.getPort() + " : " + packet.getSocketAddress() + " with mac address  : " + packet1.getMacaddr());

                    DHCPAckPacket packet2 = DHCPAckPacket.getDHCPAckPacket(packet1.getMacaddr());
                    if (macToIps.containsKey(packet1.getMacaddr())) {
                        packet2.setSiaddr(serverAddress);
                        packet2.setYiaddr(macToIps.get(packet1.getMacaddr()));
                    } else {
                        System.out.println("[INFO] Invalid DHCP Request");
                        packet2.setSiaddr(serverAddress);
                        packet2.setYiaddr("00");
                    }
                    buffer = packet2.toString().getBytes();
                    packet = new DatagramPacket(buffer, packet2.toString().length(), address, port);
                    socket.send(packet);
                    System.out.println("[INFO] Sent DHCP ACK Packet to address : " + address + " port: " + port);
                }

            } catch (IOException e) {
                e.printStackTrace();
            }


        }

    }


    public static void main(String[] args) {
        try {
            new DHCPServer();
        } catch (IOException e) {

        }
    }


}
