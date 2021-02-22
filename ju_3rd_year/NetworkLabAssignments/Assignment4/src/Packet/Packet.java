package Packet;

import java.util.ArrayList;

public class Packet {


    public static String encodePacket(ArrayList<Integer> encoded) {

        // 10 bits per number
        String codeword = "00";

        for (int x : encoded) {
            boolean flag = false;
            if (x < 0) {
                flag = true;
                x = -x;
            }
            String bin = Integer.toBinaryString(x);
            int len = bin.length();
            if (flag) {

                for (int i = 0; i < 10 - len - 1; i++) {
                    bin = "0" + bin;
                }
                bin = "1" + bin;
            } else {
                for (int i = 0; i < 10 - len; i++) {
                    bin = "0" + bin;
                }
            }

            codeword += bin;
        }
        return codeword;
    }

    public static ArrayList<Integer> decodePacket(String codeword) {
        ArrayList<Integer> encoded = new ArrayList<>();
        int start = 2;
        while (start < codeword.length()) {
            String num = codeword.substring(start + 1, start + 10);
            int number = convert_into_number(num);
            if (codeword.charAt(start) == '1') {
                number = -number;
            }
            encoded.add(number);
            start += 10;
        }
        return encoded;

    }

    private static int convert_into_number(String binary_segment) {
        int number = 0;
        int len = binary_segment.length();
        for (int i = 0; i < len; i++) {
            number = number * 2 + (binary_segment.charAt(i) - '0');
        }
        return number;
    }
}
