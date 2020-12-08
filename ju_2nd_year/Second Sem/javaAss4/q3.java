import java.util.*;


class Permission{
    private int cntr = 0;
    private int cntw = 0;
    private int cntq = 0;

    synchronized public void  seekReadPerm(){
        if ( cntw  > 0 || cntq > 0){
            try{
                wait();
            }
            catch( InterruptedException e){
                System.out.println(e);
            }
            cntr++; 
        }
    }

    synchronized public void readOverNotify(){
        cntr--;
        notifyAll();
    }

    synchronized public void seekWritePerm(){
        cntq++;
        if ( cntr > 0  || cntw > 0){
            try{
                wait();
            }
            catch( InterruptedException e){
                System.out.println(e);
            }
            cntq--;
            cntw++;
        }
    }

    synchronized public void writeOverNotify(){
        cntq--;
        cntw--;
        notifyAll();

    }
}

class Data
{
    int x;
    Data( int p){
        x = p;
    }
    int read(){
        System.out.println("Thread " + Thread.currentThread().getName() + " reading");
        return x;
    }

    void write(){
        System.out.println("Wow i just wrote "+ x + " by Thread = " + Thread.currentThread().getName());
    }
}



class Reader implements Runnable{
    Data d; Permission p;
    Thread t;
    Reader(Data d , Permission p){
         this.d =d;
         this.p = p;
         t = new Thread(this);
         t.start();
         
    }

    public void run() {
        int a;
        p.seekReadPerm();
        a = d.read();
        p.readOverNotify();
    }
    

    
}

class Writer implements Runnable{
    Data d; Permission p;
    Thread t;
    Writer( Data  d , Permission p){
        this.d = d;
        this.p = p;
        t = new Thread(this);
        t.start();
    }

    public void run(){
        p.seekWritePerm();
        d.write();
        p.writeOverNotify();
    }
}


class Test{ 
    public static void main( String args[]){
        Permission p = new Permission();
        Data d = new Data(5);
        Reader r = new Reader( d , p);
        Writer w = new Writer( d , p);
       for ( int i =0 ; i < 50 ; i++){
           int x = (int) (Math.random()*2) ;
           if ( x == 0){
                new Thread( new  Reader( d , p) ,  String.valueOf(i));
           }
           else{
                new Thread( new  Writer( d , p),  String.valueOf(i));
           }
           
       }



    }
}