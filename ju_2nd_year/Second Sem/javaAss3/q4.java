import java.io.*;
import java.util.*;

class Test{

    final static String lexicon = "ABCDEFGHIJKLMNOPQRSTUVWXYZ12345674890";

    final static java.util.Random rand = new java.util.Random();

    // consider using a Map<String,Boolean> to say whether the identifier is being
    // used or not
    final static Set<String> identifiers = new HashSet<String>();

    public static String randomIdentifier() {
        StringBuilder builder = new StringBuilder();
        while (builder.toString().length() == 0) {
            int length = rand.nextInt(5) + 5;
            for (int i = 0; i < length; i++) {
                builder.append(lexicon.charAt(rand.nextInt(lexicon.length())));
            }
            if (identifiers.contains(builder.toString())) {
                builder = new StringBuilder();
            }
        }
        return builder.toString();
    }

    public static void main(String args[]){
        String[] arr = new String[100];
        for ( int i =0  ; i < 100 ; i++){
            arr[i] = Test.randomIdentifier();
        }
        File f =  new File("names.txt");
        if ( f.exists()){
            f.delete();
        }
        try{
        if (f.createNewFile()){
            PrintWriter out= new PrintWriter(new FileWriter(f.getName()));
                for (String ss : arr){
                    // System.out.println(ss);
                    out.println(ss);
                }
            
            out.close();
        }
    }
    catch (IOException e){
        System.out.println(e.getMessage());
    }

    System.out.println("Content written");
    try{
    Scanner sc  = new Scanner(f);
    while ( sc.hasNextLine()){
        System.out.println(sc.nextLine());
    }
}
catch(FileNotFoundException e){
    System.out.println(e.getMessage());
}
    }
}