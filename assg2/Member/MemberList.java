package Member;
import java.util.*;




class DOB{
	int year;
	int day;
	int month;
	
	DOB(){
		this.year = 0;
		this.day = 0;
		this.month = 0;
	}
	
	DOB( int year , int day , int month ){
		this.year = year;
		this.day = day ;
		this.month = month;
	}
	
	void set_day( int day ){
		this.day = day;
	}
	void set_month( int month ){
		this.month = month;
	}
	void set_year( int year ){
		this.year = year;
	}
	
	void getData(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter year: "  ); 
		this.year = sc.nextInt();
		System.out.println("Enter month " ); 
		this.month = sc.nextInt();
		System.out.println("Enter day: " ); 
		this.day =sc.nextInt(); 
	}
	
	void show(){
		System.out.println("Year : " + year + " Month :" + month + " Day :" + day  ); 
	} 


}
class Member{
	String id;
	String name;
	DOB db;
	int copies;
	static int limit = 100;
	
	Book(){
		this.id = "";
		this.name = "";
		this.copies = 0;
		this.db  =new DOB();
	}
	
	Book( String id , String name , int copies  , DOb d){
		this.id = id;
		this.name = name;
		this.copies = copies;
		this.db  =d;
	}
	
	
	void setId( String id ){
		this.id = id;
	}
	void setName( String title ){
		this.title = title;
	}
	void setCopies( int copies ){
		this.copies = copies;
	}
	
	String getId(){
		return id;
	}
	String getName(){
		return title;
	}
	int getCopies(){
		return copies;
	}
	
	void show(){
		System.out.println("Member id: " + id ); 
		System.out.println("Member name: " + title );
		System.out.println("Member copies: " + copies ); 
		db.show(); 
	}
	
	void issue(){
		
	}
	
	void getData(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter Member id: "  ); 
		this.id = sc.nextLine();
		System.out.println("Enter Member name " ); 
		this.title = sc.nextLine();
		System.out.println("Enter Member copies: " ); 
		this.copies =sc.nextInt();
		System.out.println("Enter Member DOB: " ); 
		DOB dd;
		dd.getData();
		this.db = dd;
		
	
	}
	
}


public class MemberList{
	Member arr[];
	static int no =0 ;
	
	MemberList(){
		arr = new Member[1000];
	}
	
	
	static int getNo(){
		return  no;
	}
	
	void addMember(){
		Member b = new Member();
		b.getData();
		for ( int i = 0 ; i < no ; i++ ){
			if ( arr[i].getId().equals(b.id)){
				System.out.println("Id with book found");
				return;
			}
		}	
		arr[no++] = b;
	}
	
	void displayAll(){
		for ( int i =0 ; i < no ; i++ ){
			arr[i].show();
			System.out.println(); 
		}
	
	}
	
	void display( String id ){
	    
		for ( int i = 0 ;i < no ; i++ ){
			if ( arr[i].getId().equals(id)){
				arr[i].show(); 
				System.out.println(); 
				return;
			}
		}
		System.out.println("Member id not found " ); 
	
	}
	
	public static void main(String args[]){
		
	}
	
}


