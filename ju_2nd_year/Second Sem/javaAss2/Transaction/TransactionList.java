package Transaction;
import java.util.*;
import Member.*;
import Booklist.*;


class Transaction{
	String mid;
	String bid;
	
	Transaction(String mid,  String bid){
		this.mid = mid;
		this.bid = bid;
	}
	void setBid( String Bid ){
		this.bid = Bid;
	}
	void setMid( String Mid ){
		this.mid = Mid;
	}
	
	String getMid(){
		return mid;
	}
	String getBid(){
		return bid;
	}
	
	void show(){
		System.out.println("Member id: " + mid ); 
		System.out.println("Book id: " + bid );
		
	}
	
	
	void getData(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter Member id: "  ); 
		this.mid = sc.nextLine();
		System.out.println("Enter Book id " ); 
		this.bid = sc.nextLine();
	}
	
	
	
	
}


public class TransactionList{
	public Transaction arr[];
	static int no=0;
	
	public TransactionList(){
		arr = new Transaction[1000];
	}

	int issue(BookList bl , MemberList ml , String bid , String mid){
		int ok  =0;
		for ( int i =0 ; i < ml.getNo() ; i++ ){
			if ( ml.arr[i].getId().equals(mid)){
				ok =1;
			} 
		}
		if ( ok == 0){
			System.out.println("Member with id  " + mid + "not found");
			return 0;
		}
		ok = 0;
		for ( int i =0 ; i < bl.getNo() ; i++ ){
			if ( bl.arr[i].getId().equals(bid)){
				ok =1;
			} 
		}
		if ( ok == 0 ){
			System.out.println("Book id : " + bid + "not found");
			return 0;
		}
		if ( ml.canIssue(mid)==1 && bl.canIssue(bid)==1){
			ml.issue(mid);
			bl.issue(bid);
			System.out.println("Book successfully issued");
			return 1;
		}

		return 0;
		
		
	
	}

	public void addIssueTransaction( BookList bl ,MemberList ml , String bid , String mid){
		
		if (issue(bl , ml , bid , mid) == 1){
			Transaction t = new Transaction( bid ,mid);
			arr[no] = t;
			System.out.println("Book " + bid+" successfully issued to member" + mid) ;
		}
	}
	
	
	
	void displayAll(){
		for ( int i =0 ; i < no ; i++ ){
			arr[i].show();
			System.out.println(); 
		}
	
	}
	
	// void display( String id ){
	    
	// 	for ( int i = 0 ;i < no ; i++ ){
	// 		if ( arr[i].getId().equals(id)){
	// 			arr[i].show(); 
	// 			System.out.println(); 
	// 			return;
	// 		}
	// 	}
	// 	System.out.println("Member id not found " ); 
	
	// }
	
	
	
}


