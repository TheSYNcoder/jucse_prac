package Transaction;
import java.util.*;
import Member.*;
import Booklist.*;


class Transaction{
	String mid;
	String bid;
	Book(){
		this.mid = "";
		this.bid = "";
	}
	
	Book( String mid , String bid){
		this.bid = bid;
		this.mid = mid;
	}
	
	
	void setBid( String Bid ){
		this.Bid = Bid;
	}
	void setMid( String Mid ){
		this.Mid = Mid;
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
	
	void issue(BookList bl , MemberList ml){
		int ok  =0;
		for ( int i =0 ; i < ml.getNo() ; i++ ){
			if ( ml.arr[i].getId().equals(mid)){
				ok =1;
			} 
		}
		if ( ok == 0){
			System.out.println("Member not found");
		}
		ok = 0;
		for ( int i =0 ; i < bl.getNo() ; i++ ){
			if ( bl.arr[i].getId().equals(bid)){
				ok =1;
			} 
		}
		
		
		
	
	}
	
	
}


public class MemberList{
	Member arr[];
	static int no;
	
	MemberList(){
		no = 0;
		arr = new Member[1000];
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


