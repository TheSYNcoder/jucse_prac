import java.util.*;


abstract class Dataset{
    static double arr[][];
    Dataset(){
        arr = new double[100][5];
    }
    void read(){
        for ( int i =0 ;i < 100 ;i++ ) {
            for ( int j =0; j < 5; j ++){
                arr[i][j] = Math.random() * 50;
            }
        }
    }

    void cal_average(){}
    void cal_std(){}
}

class Average extends Dataset{

    Average(){
        super();
        super.read();
    }
    void cal_average(){
        for ( int i =0; i < 100; i++){
           for ( int j =0; j < 5; j++){
               System.out.println(arr[i][j]);
           }
           System.out.println('\n');
        }
    }

    void cal_std(){
         System.out.println("Not implemented");
    }
}

class Test {

    

    public static void main(String args[]) {

        Average a = new Average();
        a.cal_std();
        a.cal_average();
    }


}
