import java.util.*;

class Customer{
	String id;
	String name;
	String phone;
	
	
	double loan;
	static double credit_limit_n  = 1000;
	static double credit_limit = 2000;
	
	
	void set_name( String name ){
		this.name = name;
	}
	void set_phone(String phone){
		this.phone = phone;	
	}
	
	Customer(String id , String name,  String phone){
		this.id = id;
		this.name = name;
		this.phone = phone;
		this.loan =0 ;
	}
	
	void show(){
		System.out.println(loan);
	}
	
	void show_details(){
		System.out.println("name :" + name);
		System.out.println("phone :" + phone );
		System.out.println("current loan :" + loan );
	
	}
	
	
}



class Priv extends Customer{
	
	Priv(String id , String name , String phone){
		super(id , name  , phone);
	}
	
	void sanction(double amount){
		if ( amount + loan <= credit_limit ){
			loan = amount + loan;
		}
	}
	
}



class Norm extends Customer{
	
	Norm(String id, String name , String phone ){
		super(id , name, phone);
	}
	void sanction(double amount){
		if ( amount + loan <= credit_limit_n ){
			loan = amount + loan;
		}
	}
	

}

class Test{

	
	public static void main(String args[]){
		
		Priv c1 =new Priv("1" , "hjdsh" , "687362");
		Norm c2 = new Norm("2"  , "normie" , "87763984");
		c1.sanction(400);
		c2.sanction(1000);
		c1.show();
		c2.show();
		c1.show_details();
		c2.show_detils();
	}



}



