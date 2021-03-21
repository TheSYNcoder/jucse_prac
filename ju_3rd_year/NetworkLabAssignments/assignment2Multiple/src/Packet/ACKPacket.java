package Packet;

public class ACKPacket {


    Packet p;

    ACKPacket(int seqNumber) {
        p = new Packet();
        p.setSeqNumber(seqNumber);
        String payload = "";
        for (int i = 0; i < 50; i++) {
            payload += '0';
        }
        p.setPayload(payload);
        
    }


}
