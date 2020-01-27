import java.util.*;





class Test{

	public static void main(String args[]){
		int i ;
		Scanner in  = new Scanner(System.in);
		i = in.nextInt();
		Integer ii = new Integer(i);
		System.out.println("basic : " + i); 
		System.out.println("object : " + ii);
		int x = ii;
		System.out.println("object to basic : " + x);
		String basic = String.valueOf(i);
		System.out.println("basic to string : " + basic );
		int bs = Integer.parseInt(basic);
		System.out.println("string to basic : " + bs);  
		Integer ni = new Integer(basic);
		System.out.println("string to numeric : " + ni); 
		String ss = ni.toString();
		System.out.println("numeric object to String : " +ss); 
	
	}
}


