import java.util.*;

class Instructor{
    String name;
    String phone;
    
    Instructor( String name , String phone ){
        this.name = name;
        this.phone = phone;
    }
    
    void set( String name , String phone ){
        this.name = name;
        this.phone = phone;
    }
    
    void show( ){
        System.out.println(name);
        System.out.println(phone);
    } 

}

class Book{
    String title ;
    String author;
    String publisher;
    
    Book( String title ,String author , String p ){
        this.title = title;
        this.author = author;
        this.publisher = p;
    }
    
    void set( String title , String author , String p ){
        this.title = title;
        this.author = author;
        this.publisher = p;
    }
    
    void show( ){
        System.out.println(title);
        System.out.println(author);
        System.out.println(publisher);
    } 

}

class Course {
    String name;
    Book b;
    Instructor i;
    Course ( String name){
        b = new Book("tit" , "auth" , "publ");
        i = new Instructor("name" , "phobne = 8793");
        this.name = name; 
    }
    
    void show(){
        System.out.println(name);
        b.show();
        i.show(); 
    }
}




class Test{
     
    public static void main(String args[]){
        Course c= new Course("data");
        c.show();
        
        
           
    }
    
    
    
   
   

}
