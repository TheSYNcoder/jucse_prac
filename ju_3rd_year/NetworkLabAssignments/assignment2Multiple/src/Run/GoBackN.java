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


        int src1 = 10;
        int des1 = 11;

        int src2 = 12;
        int des2 = 13;

        String src1Add = padAddress(Integer.toBinaryString(src1));
        String des1Add = padAddress(Integer.toBinaryString(des1));

        String src2Add = padAddress(Integer.toBinaryString(src2));
        String des2Add = padAddress(Integer.toBinaryString(des2));
        boolean gobackn = true;


        Channel ch = new Channel();
        new Client(src1Add, des1Add, 4, 5, ch, gobackn);
        new Server(src1Add, des1Add, 1, 5, ch, gobackn);

        new Client(src2Add, des2Add, 4, 5, ch, gobackn);
        new Server(src2Add, des2Add, 1, 5, ch, gobackn);
    }
}
