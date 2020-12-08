import java.io.File;
import java.util.*;


class Test{

    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the filename");
        String filename = sc.nextLine();
        File tmp = new File(filename);
        if ( tmp.exists()){
            boolean f = tmp.isDirectory();
            if ( f){
                System.out.println("File is  a directory");
                for ( File ff : tmp.listFiles()){
                    System.out.println(ff);
                }
                
            }
            else{
                System.out.println("Not a directory");
            }
        }   
        else{
            System.out.println("Wrong path");
        }

    }
}