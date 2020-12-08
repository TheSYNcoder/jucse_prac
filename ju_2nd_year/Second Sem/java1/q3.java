import java.util.*;


class Test{
    public static void main(String args[]){
     
        System.out.println("Enter the height in cm : ");
        Scanner in = new Scanner(System.in);
        
        int height  = in.nextInt();
        double feet = 0;
        System.out.println("The height in feet :" + height/30.5);
        System.out.println("and inches :" +(height - (int)(height/30.5 )*(30.5))/2.54);
        
    }

}
