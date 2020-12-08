package Packet;


import java.util.concurrent.Delayed;
import java.util.concurrent.TimeUnit;

public class TimedPacket implements Delayed {

    public static final long REPEAT_TIME = TimeUnit.SECONDS.toNanos(2);

    private long delay;
    private Packet packet;
    public String type;

    public TimedPacket(Packet packet) {
        this.packet = packet;
        delay = System.nanoTime();
        type = "TIMED_PACKET";
    }

    @Override
    public int compareTo(Delayed o) {
        if (this.delay < ((TimedPacket) o).delay)
            return -1;
        else if (this.delay > ((TimedPacket) o).delay)
            return 1;
        return 0;
    }

    @Override
    public long getDelay(TimeUnit unit) {
        return unit.convert(delay - System.nanoTime(), TimeUnit.NANOSECONDS);
    }

    public Packet getPacket() {
        return packet;
    }

    public synchronized TimedPacket repeat() {
        delay += REPEAT_TIME;
        return this;
    }

    public synchronized TimedPacket reset() {
        delay = System.nanoTime();
        return this;
    }

    public static TimedPacket toPacket(String source) {
        return new TimedPacket(Packet.toPacket(source));
    }
}
