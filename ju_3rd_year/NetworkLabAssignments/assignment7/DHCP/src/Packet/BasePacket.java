package Packet;

public class BasePacket {

    String ciaddr; // IP Address of this machine ( if already there )
    String yiaddr; // IP Address of this machine ( provided by the DHCP server )
    String siaddr; // IP Address of the DHCP server
    String giaddr; // IP Address of the DHCP relay

    String macaddr; // The mac address of this machine
    String option;

    public BasePacket() {
    }

    public String getCiaddr() {
        return ciaddr;
    }

    public void setCiaddr(String ciaddr) {
        this.ciaddr = ciaddr;
    }

    public String getYiaddr() {
        return yiaddr;
    }

    public void setYiaddr(String yiaddr) {
        this.yiaddr = yiaddr;
    }

    public String getSiaddr() {
        return siaddr;
    }

    public void setSiaddr(String siaddr) {
        this.siaddr = siaddr;
    }

    public String getGiaddr() {
        return giaddr;
    }

    public void setGiaddr(String giaddr) {
        this.giaddr = giaddr;
    }

    public String getMacaddr() {
        return macaddr;
    }

    public void setMacaddr(String macaddr) {
        this.macaddr = macaddr;
    }

    public String getOption() {
        return option;
    }

    public void setOption(String option) {
        this.option = option;
    }

    public static String getPacketType(String buffer) {
        String[] tokens = buffer.split("[;]+");

        if (tokens[5].equals(Integer.toHexString(1)))
            return "DHCPDiscover";
        else if (tokens[5].equals(Integer.toHexString(2)))
            return "DHCPOffer";
        else if (tokens[5].equals(Integer.toHexString(3)))
            return "DHCPRequest";
        else if (tokens[5].equals(Integer.toHexString(4)))
            return "DHCPAck";
        return null;
    }


}
