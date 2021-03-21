import java.util.*;


class Address{
	int no;
	String street;
	String city;
	String pin;
	String state;
	
	Address( int no , String street , String city , String pin , String state){
		this.no = no;
		this.street = street;
		this.city = city;
		this.pin = pin;
		this.state=  state;
	}
	
	public String toString(){
		String ret =  "Address" + "no :" + no + "\nstreet : " + street+"\ncity : " + city+"\npin :" + pin+"\nstate :" + state ;
		return ret;
	
	}
	
	void set_no( int data){
		no  = data;
	}
	
	void set_street( String data ){
		street = data;
	}
	
	void set_city( String data ){
		city = data;
	}
	void set_pin( String data ){
		pin = data;
	}
	void set_state( String data ){
		state = data;
	}
	

}

class Person{
	String name;
	String email;
	String phone;
	Address ad;

	Person(String name , String email , String phone , int no , String street  , String city , String pin , String state){
		this.name = name;
		this.email = email;
		this.phone= phone;
		ad = new Address(no,  street , city , pin , state);
		
	}
	
	
	void show(){
		System.out.println();
		System.out.println("name :" + name);
		System.out.println("email :" + email);
		System.out.println("phone :" + phone);
		System.out.println(ad);
	}
	
	


}


class Student extends Person{
	String roll;
	String course;
	
	Student(String roll , String course ,String name , String email , String phone , int no , String street  , String city , String pin , String state){
		super(name , email ,phone,  no , street , city ,pin , state );
		this.roll = roll;
		this.course = course;
		
	
	}
	void show(){
	    System.out.println(“————Student DETAILS————-”);
		System.out.println("roll :" + roll);
		System.out.println("course :" + course);
		super.show();
	
	}
	

}


class Faculty extends Person{
	String id;
	String department;
	String spz;
	
	Faculty(String id , String department ,String spz ,String name , String email , String phone , int no , String street  , String city , String pin , String state){
		super(name , email ,phone,  no , street , city ,pin , state );
		this.id = id;
		this.department = department;
		this.spz = spz;
		
	
	}
	
	void show(){
	    System.out.println(“————FACULTY DETAILS————-”);
		System.out.println("id :" + id);
		System.out.println("department :" + department);
		System.out.println("specialization :" + spz);
		super.show();
	}
	

}



class Test{
	
	public static void main(String args[]){
	
	Student s = new Student("43" , "course"  , "s_name" , "s_email" , "s_phone" , 104, "strret" , "cityy" , "pin" , "state");
	s.show();
	Faculty f = new Faculty("43" , "department"  ,"spz", "f_name" , "f_email" , "f_phone" , 43 ,"trret" , "ityy" , "in" , "sate");
	f.show();
	}


}
