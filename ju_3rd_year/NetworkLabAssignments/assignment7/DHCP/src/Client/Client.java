package Client;

import Packet.DHCPAckPacket;
import Packet.DHCPDiscoverPacket;
import Packet.DHCPOfferPacket;
import Packet.DHCPRequestPacket;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Client {

    private DatagramSocket socket;
    private InetAddress address;
    ExecutorService executor;
    String macAddress;
    String[] arguments;

    public Client(String[] arguments) throws IOException {
        int port = Integer.valueOf(arguments[0]);
        String macAdd = arguments[1];
        macAddress = macAdd;
        socket = new DatagramSocket(port, InetAddress.getLocalHost());
        socket.setBroadcast(true);
        address = InetAddress.getByName("255.255.255.255");
        executor = Executors.newSingleThreadExecutor();
        executor.execute(() -> listen());


    }

    public void listen() {

        try {
            // Broadcast a DHCP Discover message
            DHCPDiscoverPacket packet = DHCPDiscoverPacket.getDHCPDiscoverPacket(macAddress);
            packet.setMacaddr(macAddress);
            byte[] buffer = packet.toString().getBytes();
            DatagramPacket sendPacket = new DatagramPacket(buffer, buffer.length, address, 8067);
            socket.send(sendPacket);
            System.out.println("[INFO] DHCPDiscoverPacket broadcasted");

            // Receive a DHCP Offer message
            buffer = new byte[4096];
            sendPacket = new DatagramPacket(buffer, buffer.length);
            socket.receive(sendPacket);
            String received = new String(buffer).substring(0, sendPacket.getLength());
            DHCPOfferPacket packet1 = DHCPOfferPacket.decode(received);
            System.out.println("[INFO] DHCPOffer Packet received from : " + packet1.getSiaddr() + " offering : " + packet1.getYiaddr());


            // Broadcast the DHCP Request message for the IP given
            DHCPRequestPacket packet2 = DHCPRequestPacket.getDHCPRequestPacket(macAddress);
            packet2.setSiaddr(packet1.getSiaddr());
            packet2.setCiaddr(packet1.getYiaddr());
            buffer = packet2.toString().getBytes();
            sendPacket = new DatagramPacket(buffer, buffer.length, address, 8067);
            socket.send(sendPacket);
            System.out.println("[INFO] DHCPRequestPacket broadcasted");

            // Receive the DHCP ACK regarding the following IP is active.
            buffer = new byte[4096];
            sendPacket = new DatagramPacket(buffer, buffer.length);
            socket.receive(sendPacket);
            received = new String(buffer).substring(0, sendPacket.getLength());
            DHCPAckPacket packet3 = DHCPAckPacket.decode(received);
            System.out.println("[INFO] DHCPAckPacket received from : " + packet3.getSiaddr() + " and confirmed IP :" + packet3.getYiaddr());

            System.out.println("\nIP confirmed by DHCP server : " + packet3.getYiaddr());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        try {
            if (args.length < 2) {
                System.out.println("Please give port and mac address as arguments");
                System.out.println("Shutting down ....");
                System.exit(0);
            }
            new Client(args);
        } catch (IOException e) {

        }
    }
}
