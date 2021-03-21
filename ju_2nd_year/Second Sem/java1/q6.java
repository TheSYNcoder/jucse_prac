import java.util.*;


class Test{


    void show(int data){
        System.out.println(data);
    }
    
    void show( double data ){
        System.out.println(data);
    }
    
    
    public static void main(String args[]){
        Test t = new Test();
        short a = 4;
        double  b = 9.5;
        t.show(a);
        t.show(b);       
    }

}
