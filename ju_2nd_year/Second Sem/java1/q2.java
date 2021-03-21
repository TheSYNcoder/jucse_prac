import java.util.*;


class Test{
    public static void main(String args[]){
     
        if (args.length <=  0 ){
            System.out.println("No arguments");
        }
        else{
            System.out.println( "No of arguments : "+ args.length);
            for ( int i =0 ; i < args.length ; i++ ){
                System.out.print( args[i] + " " );
            }
        }
    }

}
