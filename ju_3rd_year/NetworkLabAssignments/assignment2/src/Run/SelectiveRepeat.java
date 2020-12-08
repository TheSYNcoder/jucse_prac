package Run;

import Channel.Channel;
import Client.Client;
import Server.Server;

public class SelectiveRepeat {

    private static String padAddress(String address) {
        int l = address.length();
        for (int i = 0; i < 6 * 8 - l; i++)
            address = '0' + address;
        return address;
    }


    public static void main(String[] args) {


        /**
         *
         * Noise  8291, 100 ,  4222, 50  2
         * Noise  4123 ,100    4074,50         4
         * NOise  255,100
         *
         *
         */


        int src = 10;
        int des = 11;
        boolean gobackn = false;
        String srcAdd = padAddress(Integer.toBinaryString(src));
        String desAdd = padAddress(Integer.toBinaryString(des));


        Channel ch = new Channel();
        // window size half of sequence size
        // selective repeat
        new Client(srcAdd, desAdd, 8, 17, ch, gobackn);
        new Server(srcAdd, desAdd, 8, 17, ch, gobackn);

//        new Client(srcAdd, desAdd, 2, 5, ch, gobackn);
//        new Server(srcAdd, desAdd, 2, 5, ch, gobackn);
    }


}
