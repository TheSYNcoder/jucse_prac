package Packet;

import ErrorDetection.CRC;

public class Packet {
    /*
     * Stores a single packet
     * in the IEEE 802.3 ethernet
     * frame format

     */
    private String preamble;
    private String SFD;

    private String source;
    private String destination;


    int length;
    private String payload;

    private int seqNumber;

    private String CRC;

    public String type;


    public Packet() {

    }


    public Packet(String source, String destination, String payload) {
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
        type = "PACKET";


    }

    public int getSeqNumber() {
        return seqNumber;
    }


    int getCodeType(String typePacket) {
        switch (typePacket) {
            case "PACKET":
                return 0;

            case "ACK":
                return 1;

            case "NAK":
                return 2;

            case "NAKN":
                return 3;

        }
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


        // 2 bytes of sequence number

        int code = getCodeType(type);
        String codet = Integer.toBinaryString(code);
        l = codet.length();
        for (int i = 0; i < 8 - l; i++) {
            codet = '0' + codet;
        }

        String seqLen = Integer.toBinaryString(seqNumber);
        l = seqLen.length();
        for (int i = 0; i < 16 - l; i++) {
            seqLen = '0' + seqLen;
        }


        // 1 byte of type


        codeword += seqLen;

        codeword += len;
        codeword += codet;
        codeword += payload;


        CRC obj = new CRC();
        codeword = obj.prepare_codeword(codeword);
        return codeword;
    }


    static String getTypeFromCode(String con) {
        int code = convert_into_number(con);
        switch (code) {
            case 0:
                return "PACKET";

            case 1:
                return "ACK";
            case 2:
                return "NAK";

            case 3:
                return "NAKN";

        }
        return "PACKET";
    }


    public static Packet toPacket(String content) {


        String source = content.substring(56 + 8, 56 + 8 + 48);

        String destination = content.substring(56 + 8 + 48, 56 + 8 + 48 + 48);

        String seqlen = content.substring(56 + 8 + 48 + 48, 56 + 8 + 48 + 48 + 16);
        int seq = convert_into_number(seqlen);


        String length = content.substring(56 + 8 + 48 + 48 + 16, 56 + 8 + 48 + 48 + 16 + 16);
        int len = convert_into_number(length);

        String typeCode = content.substring(56 + 8 + 48 + 48 + 16 + 16, 56 + 8 + 48 + 48 + 16 + 16 + 8);
        String Type = getTypeFromCode(typeCode);


        String payload = content.substring(56 + 8 + 48 + 48 + 16 + 16 + 8, 56 + 8 + 48 + 48 + 16 + 16 + 8 + len);

        Packet converted = new Packet(source, destination, payload);
        converted.setSeqNumber(seq);
        converted.setType(Type);
        return converted;
    }

    public void setSeqNumber(int number) {
        seqNumber = number;
    }


    private static int convert_into_number(String binary_segment) {
        int number = 0;
        int len = binary_segment.length();
        for (int i = 0; i < len; i++) {
            number = number * 2 + (binary_segment.charAt(i) - '0');
        }
        return number;
    }


    public static Packet makeAck(int seqNumber, String srcAdd, String desAdd) {

        String payload = "";
        for (int i = 0; i < 50; i++) {
            payload += '0';
        }
        Packet p = new Packet(srcAdd, desAdd, payload);
        p.setSeqNumber(seqNumber);
        p.setType("ACK");
        return p;

    }


    public static Packet makeNak(int seqNumber, String srcAdd, String desAdd) {
        String payload = "";
        for (int i = 0; i < 50; i++) {
            payload += '0';
        }
        Packet p = new Packet(srcAdd, desAdd, payload);
        p.setSeqNumber(seqNumber);
        p.setType("NAK");
        return p;
    }

    public static Packet makeNakN(int seqNumber, String srcAdd, String desAdd) {
        String payload = "";
        for (int i = 0; i < 50; i++) {
            payload += '0';
        }
        Packet p = new Packet(srcAdd, desAdd, payload);
        p.setSeqNumber(seqNumber);
        p.setType("NAKN");
        return p;
    }


    public void setPayload(String payload) {
        this.payload = payload;
    }

    public void setType(String type) {
        this.type = type;
    }

    @Override
    public String toString() {
        return "TYPE : " + type + " SEQ. NO. : " + String.valueOf(seqNumber);
    }
}
