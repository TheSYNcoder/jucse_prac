import java.util.*;


class Metric{
    
    double data;
    Metric( double d){
        data = d;
       }
    void convertToKilo(){
        double kilos = 1.5 * data;
        
        System.out.println("Data = " + data + " in kilos :" + kilos );
        data = kilos;
    }
    void convertToMiles(){
        double miles =  data / 1.5;
        
        System.out.println("Data = " + data + " in kilos :" + miles );
        data = miles;
    } 
    public static void main(String args[]){
        Metric m = new Metric(1);
        m.convertToKilo();
        System.out.println(m.data);
        
           
    }
    
    
    
   
   

}
