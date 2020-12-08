import java.util.*;


class SharedData{
    int data;
    int check = 0;

    SharedData(){
        data = 0;
    }
    void  consume(int value){
        data-= value;
        System.out.println("Consumed" + data);
        
    }

   void produce( int value){
        data += value;
        System.out.println("produced data = " + data);
    }
}


class NewThread implements Runnable{
    Thread t;
    SharedData d;
    int action;
    int x;
    

    NewThread(SharedData a , int action , int x){
        d =a;
        this.action = action;
        t = new Thread(this);
        this.x = x;
    }

    public void run(){
        
        
        if ( action == 0){
            
            d.produce(x);
        }
        else{
            d.consume(50);
        }
        try{
        Thread.sleep(0);
        }
        catch( InterruptedException e){
            System.out.println("Interrupted" + e.getMessage());
        }
    }
}


class Test{

    public static void main( String args[]) throws Exception{
        try{
        SharedData d = new SharedData();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter");
        int x = sc.nextInt();
        
        for ( int i = 0 ; i < 100000 ; i++){
            Thread t1 = new Thread(new NewThread(d, 0, x));
            Thread t2 = new Thread(new NewThread(d, 1, x));
            t1.start();
            t2.start();
        }
        
        
        System.out.println(d.data);
        System.out.println("Stop");
        }
        catch(Exception e){
              System.out.println(e);
        }

    }
}