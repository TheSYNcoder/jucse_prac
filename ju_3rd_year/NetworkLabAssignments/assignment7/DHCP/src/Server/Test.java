package Server;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;

public class Test {

    public static void main(String[] args) throws UnknownHostException, SocketException {
        InetAddress lanip = InetAddress.getByName("192.168.0.138");
        NetworkInterface network = NetworkInterface.getByInetAddress(lanip);
        byte[] mac = network.getHardwareAddress();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < mac.length; i++) {
            sb.append(String.format("%02X%s", mac[i], (i < mac.length - 1) ? "-" : ""));
        }
        String address = sb.toString();

        System.out.println(lanip.toString());
        System.out.println(address);
        System.out.println(network.toString());
    }
}
