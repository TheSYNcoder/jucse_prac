package Packet;

import ErrorDetection.CRC;

public class Packet implements Comparable<Packet> {


    /*
     * Stores a single packet
     * in the IEEE 802.3 ethernet
     * frame format

     */
    private String preamble;
    private String SFD;

    private String source;
    private String destination;

    private double time;


    int length;
    private String payload;

    private int frameNo;


    public Packet() {

    }

    public void setTime(double time) {
        this.time = time;
    }

    public double getTime() {
        return time;
    }

    public Packet(String source, String destination, String payload, int frame_number) {
        this.source = source;
        this.destination = destination;
        this.payload = payload;

        length = payload.length();
        String alt01 = "01";
        preamble = "";
        for (int i = 0; i < 4 * 7; i++) { // 7 bytes of preamble
            preamble += alt01;
        }
        SFD = "";
        for (int i = 0; i < 3; i++) {
            SFD += alt01;
        }
        SFD += "11";

        this.frameNo = frame_number;

    }

    @Override
    public int compareTo(Packet o) {
        if (time < o.getTime())
            return 1;
        else if (time > o.getTime())
            return -1;
        return 0;
    }


    public String toCodeWord() {

        // 7 + 1 + 6 + 6
        String codeword = preamble + SFD + source + destination;

        String len = Integer.toBinaryString(length);

        // 2 bytes of length
        int l = len.length();
        for (int i = 0; i < 16 - l; i++) {
            len = '0' + len;
        }


        codeword += len;

        codeword += payload;


        ErrorDetection.CRC obj = new CRC();
        codeword = obj.prepare_codeword(codeword);
        return codeword;
    }


    public static Packet toPacket(String content) {


        String source = content.substring(56 + 8, 56 + 8 + 48);

        String destination = content.substring(56 + 8 + 48, 56 + 8 + 48 + 48);


        String length = content.substring(56 + 8 + 48 + 48, 56 + 8 + 48 + 48 + 16);
        int len = convert_into_number(length);


        String payload = content.substring(56 + 8 + 48 + 48 + 16, 56 + 8 + 48 + 48 + 16 + len);

        Packet converted = new Packet(source, destination, payload, 0);
        return converted;
    }


    private static int convert_into_number(String binary_segment) {
        int number = 0;
        int len = binary_segment.length();
        for (int i = 0; i < len; i++) {
            number = number * 2 + (binary_segment.charAt(i) - '0');
        }
        return number;
    }


    public void setPayload(String payload) {
        this.payload = payload;
    }

    @Override
    public String toString() {
        return "Packet Frame : " + String.valueOf(frameNo);
    }
}
