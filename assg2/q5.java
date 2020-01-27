import java.util.*;



class Exception extends Throwable{

	

}
class Student{
	String name;
	String roll;
	int score;
	
	Student(String name, String roll , int score){
		this.name=  name;
		this.roll = roll;
		this.score= score;
	}
	
	void set_score(int score) throws Exception{
		if ( score < 0  || score  > 100 ){
			Exception e = new Exception();
			throw e;
		}
	}
	
	

}

class Test{

	public static void main(String args[]){
		Student s = new Student("name" ,"54" , 32);
		try{
			s.set_score(200);
		
		}
		catch(Exception e){
			System.out.println("Wriong input");
		}
	
	
	}
	
	


}
