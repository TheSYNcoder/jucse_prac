package Run;

public class Run {

    public static int convert(int number) {
        int power = 1;
        while (power < number)
            power *= 2;
        return power;
    }


    public static void main(String[] args) {

        int num_nodes = 7;
        int num_stations = convert(num_nodes);

        int[][] walsh_table = new int[num_stations][num_stations];
        walsh_table = Util.buildTable(walsh_table, num_stations, 0, num_stations - 1, 0, num_stations - 1, false);
        Util.showWalshTable(num_stations, walsh_table);
        new Worker(num_nodes, walsh_table);


    }
}
