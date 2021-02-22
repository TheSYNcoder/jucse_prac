package Packet;

public class DHCPDiscoverPacket extends BasePacket {


    public static DHCPDiscoverPacket decode(String s) {
        String[] tokens = s.split("[;]+");
        DHCPDiscoverPacket packet = new DHCPDiscoverPacket();
        packet.setCiaddr(tokens[0]);
        packet.setYiaddr(tokens[1]);
        packet.setSiaddr(tokens[2]);
        packet.setGiaddr(tokens[3]);
        packet.setMacaddr(tokens[4]);
        packet.setOption(tokens[5]);
        return packet;
    }

    public static DHCPDiscoverPacket getDHCPDiscoverPacket(String macAddress) {
        DHCPDiscoverPacket packet = new DHCPDiscoverPacket();
        packet.setCiaddr("00");
        packet.setYiaddr("00");
        packet.setGiaddr("00");
        packet.setSiaddr("00");
        packet.setMacaddr(macAddress);
        packet.setOption(Integer.toHexString(1));
        return packet;

    }


    @Override
    public String toString() {
        String s = ciaddr + ";" + yiaddr + ";" + siaddr + ";" + giaddr + ";" + macaddr + ";" + option;
        return s;
    }
}
