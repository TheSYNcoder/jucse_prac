package Booklist;
import java.util.*;
public class book{
	String id;
	String title;
	int copies;
	
	book(){
		this.id = "";
		this.title = "";
		this.copies = 0;
	}
	
	book( String id , String title , int copies ){
		this.id = id;
		this.title = title;
		this.copies = copies;
	}
	
	
	void setId( String id ){
		this.id = id;
	}
	void setTitle( String title ){
		this.title = title;
	}
	void setCopies( int copies ){
		this.copies = copies;
	}
	
	public String getId(){
		return id;
	}
	String getTitle(){
		return title;
	}
	int getCopies(){
		return copies;
	}
	
	void show(){
		System.out.println("Book id: " + id ); 
		System.out.println("Book title: " + title );
		System.out.println("Book copies: " + copies );  
	}
	
	void getData(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter Book id: "  ); 
		this.id = sc.nextLine();
		System.out.println("Enter Book title " ); 
		this.title = sc.nextLine();
		System.out.println("Enter Book copies: " ); 
		this.copies =sc.nextInt();
	
	}

	void issue(){
		this.copies--;
	}
	
}