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


        int src1 = 10;
        int des1 = 11;

        int src2 = 12;
        int des2 = 13;
        boolean gobackn = false;
        String src1Add = padAddress(Integer.toBinaryString(src1));
        String des1Add = padAddress(Integer.toBinaryString(des1));

        String src2Add = padAddress(Integer.toBinaryString(src2));
        String des2Add = padAddress(Integer.toBinaryString(des2));


        Channel ch = new Channel();
        // window size half of sequence size
        // selective repeat
        new Client(src1Add, des1Add, 2, 5, ch, gobackn);
        new Server(src1Add, des1Add, 2, 5, ch, gobackn);

        new Client(src2Add, des2Add, 2, 5, ch, gobackn);
        new Server(src2Add, des2Add, 2, 5, ch, gobackn);


    }


}
