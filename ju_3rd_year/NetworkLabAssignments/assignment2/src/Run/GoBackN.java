package Run;

import Channel.Channel;
import Client.Client;
import Server.Server;

public class GoBackN {


    private static String padAddress(String address) {
        int l = address.length();
        for (int i = 0; i < 6 * 8 - l; i++)
            address = '0' + address;
        return address;
    }

    public static void main(String[] args) {

        // 2172 ms  + 6016 +  - SR
        // 24487 ms + 48276ms  - GOBACKN ( with loss )
        // 12145

        /**
         *
         * GOBACKN 16 window size 20 packets : 109s, 15 packets : 80
         * GOBACKN 8 window size 20 packets : 41s, 15 packets : 41
         *
         * 100 : 43108 4
         *
         */
        int src = 10;
        int des = 11;
        boolean gobackn = true;
        String srcAdd = padAddress(Integer.toBinaryString(src));
        String desAdd = padAddress(Integer.toBinaryString(des));


        Channel ch = new Channel();
        new Client(srcAdd, desAdd, 4, 5, ch, gobackn);
        new Server(srcAdd, desAdd, 1, 5, ch, gobackn);

    }
}
