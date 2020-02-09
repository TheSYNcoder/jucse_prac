package Member;
import java.util.*;
import Member.Member;




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
		System.out.println("Enter year: "); 
		this.year = sc.nextInt();
		System.out.println("Enter month "); 
		this.month = sc.nextInt();
		System.out.println("Enter day: " ); 
		this.day =sc.nextInt(); 
	}
	
	void show(){
		System.out.println("Year : " + year + " Month :" + month + " Day :" + day  ); 
	} 


}



public class MemberList{
	public Member arr[];
	static int no =0 ;
	
	public MemberList(){
		arr = new Member[1000];
	}
	public static int getNo(){
		return  no;
	}
	
	public void addMember(){
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
		System.out.println("------------------------");
		for ( int i =0 ; i < no ; i++ ){
			arr[i].show();
			System.out.println(); 
		}
	
	}
	

	public int canIssue( String mid){
		int i = 0;
		for ( i = 0 ; i < arr.length ; i++){
			if ( arr[i].getId().equals(mid)){
				break;
			}
		}
		if  (arr[i].copies <= Member.limit){
			return 1;
		}
		else{
			return 0;
		}
	}

	public void issue( String mid){
		int i = 0;
		for (  i = 0 ; i < arr.length ; i++){
			if ( arr[i].getId().equals(mid)){
				break;
			}
		}
		arr[i].issue();
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
	
	
	
}


