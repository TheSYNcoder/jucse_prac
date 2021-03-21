package Booklist;
import java.util.*;

import Booklist.book;


public class BookList{
	public book arr[];
	static int no;
	
	public BookList(){
		no = 0;
		arr = new book[1000];
	}

	public static int getNo(){
		return  no;
	}
	
	
	public void addBook(){
		book b = new book();
		b.getData();
		for ( int i = 0 ; i < no ; i++ ){
			if ( arr[i].getId().equals(b.id)){
				System.out.println("Id with book found , cannot add");
				return;
			}
		}	
		arr[no++] = b;
	}

	
	void displayAll(){
		System.out.println("-----------------------");
		for ( int i =0 ; i < no ; i++ ){
			arr[i].show();
			System.out.println(); 
		}
		System.out.println("-----------------------");
	}

	public int canIssue( String bid){
		int i = 0;
		for (  i = 0 ; i < arr.length ; i++){
			if ( arr[i].getId().equals(bid)){
				break;
			}
		}
		if( arr[i].copies > 0){
			return 1;
		}
		else{
			return 0;
		}
	}

	public void issue( String bid){
		int i = 0;
		for (  i = 0 ; i < arr.length ; i++){
			if ( arr[i].getId().equals(bid)){
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
		System.out.println("Book id not found " ); 
	
	}
	
	public static void main(String args[] ){
		BookList bl = new BookList();
		bl.addBook();
		bl.addBook();
		bl.addBook();
		String s = new String("1");
		String ss = new String("2");
		bl.display(s);
		bl.display(ss);
		bl.displayAll();
	
	}
	
}


