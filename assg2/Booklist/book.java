package Booklist;
import java.util.*;
class Book{
	String id;
	String title;
	int copies;
	
	Book(){
		this.id ="";
		this.title= "";
		this.copies = 0;
	
	}
	
	Book( String id , String title , int copies ){
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
	
	String getId(){
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
	
}


public class BookList{
	Book arr[];
	int no;
	
	BookList(){
		no = 0;
		arr = new Book[1000];
	}
	
	void addBook(){
		Book b = new Book();
		b.getData();
		for ( int i = 0 ; i < no ; i++ ){
			if ( arr[i].id.equals(b.id)){
				System.out.println("Id with book found");
				return;
			}
		}	
		arr[no++] = b;
	}
	
	void display( String id ){
		for ( int i = 0 ;i < no ; i++ ){
			if ( arr[i].id.equals(id)){
				arr[i].show(); 
			}
		}
		System.out.println("Book id not found " ); 
	
	}
	
}


