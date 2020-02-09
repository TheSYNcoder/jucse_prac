package Member;
import java.util.*;
import Member.*;


public class Member{
	String id;
	String name;
	DOB db;
	int copies;
	static int limit = 100;
	
	Member(){
		this.id = "";
		this.name = "";
		this.copies = 0;
		this.db  =new DOB();
	}
	
	Member( String id , String name   , DOB d){
		this.id = id;
		this.name = name;
		this.copies = 0;
		this.db  =d;
	}
	
	
	void setId( String id ){
		this.id = id;
	}
	void setName( String title ){
		this.name = title;
	}
	void setCopies( int copies ){
		this.copies = copies;
	}
	
	public String getId(){
		return id;
	}
	String getName(){
		return name;
	}
	int getCopies(){
		return copies;
	}
	
	void show(){
		System.out.println("Member id: " + id ); 
		System.out.println("Member name: " + name );
		System.out.println("Member copies: " + copies ); 
		db.show(); 
	}
	
	void issue(){
		this.copies++;
	}
	
	void getData(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter Member id: "  ); 
		this.id = sc.nextLine();
		System.out.println("Enter Member name " ); 
		this.name= sc.nextLine();
		System.out.println("Enter Member copies: " ); 
		this.copies =sc.nextInt();
		System.out.println("Enter Member DOB: " ); 
		DOB dd = new DOB();
		dd.getData();
		this.db = dd;
		
	
	}
	
}