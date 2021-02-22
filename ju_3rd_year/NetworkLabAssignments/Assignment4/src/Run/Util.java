package Run;

public class Util {


    public static int[][] buildTable(int[][] walsh_table, int len, int i1, int i2, int j1, int j2, boolean comp) {

        // unit square
        if (len == 2) {
            if (!comp) {
                walsh_table[i1][j1] = -1;
                walsh_table[i1][j2] = -1;
                walsh_table[i2][j1] = -1;
                walsh_table[i2][j2] = 1;
            } else {
                walsh_table[i1][j1] = 1;
                walsh_table[i1][j2] = 1;
                walsh_table[i2][j1] = 1;
                walsh_table[i2][j2] = -1;
            }
            return walsh_table;
        }
        // recurse
        int midi = (i1 + i2) / 2;
        int midj = (j1 + j2) / 2;
        walsh_table = buildTable(walsh_table, len / 2, i1, midi, j1, midj, comp);
        walsh_table = buildTable(walsh_table, len / 2, midi + 1, i2, j1, midj, comp);
        walsh_table = buildTable(walsh_table, len / 2, i1, midi, midj + 1, j2, comp);
        walsh_table = buildTable(walsh_table, len / 2, midi + 1, i2, midj + 1, j2, !comp);
        return walsh_table;
    }

    public static void showWalshTable(int num_stations, int[][] walsh_table) {
        for (int i = 0; i < num_stations; i++) {
            for (int j = 0; j < num_stations; j++) {
                System.out.print(walsh_table[i][j]);
                System.out.print("\t");
            }
            System.out.println();
        }
    }
}
