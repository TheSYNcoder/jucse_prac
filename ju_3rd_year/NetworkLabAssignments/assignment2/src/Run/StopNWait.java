package Run;

import Channel.Channel;
import Client.Client;
import Server.Server;

public class StopNWait {

    private static String padAddress(String address) {
        int l = address.length();
        for (int i = 0; i < 6 * 8 - l; i++)
            address = '0' + address;
        return address;
    }

    public static void main(String[] args) {
        int src = 10;
        int des = 11;
        boolean gobackn = true;
        String srcAdd = padAddress(Integer.toBinaryString(src));
        String desAdd = padAddress(Integer.toBinaryString(des));

        Channel ch = new Channel();
        new Client(srcAdd, desAdd, 1, 2, ch, gobackn);
        new Server(srcAdd, desAdd, 1, 2, ch, gobackn);

    }


}
