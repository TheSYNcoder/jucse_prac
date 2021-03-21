package Run;

import Worker.Worker;

public class RunPPersistent {

    public static void main(String[] args) {

        final int channel_speed = (int) Math.pow(10, 6);
        final int propagation_speed = (int) (2 * Math.pow(10, 8));

        double probability = 0.95;
        new Worker(4, 7, channel_speed, 10, propagation_speed, "P-PERSISTENT", probability);

    }
}
