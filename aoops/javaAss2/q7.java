import java.util.*;


class Test{

	public static void main(String args[]){
		Scanner in  = new Scanner(System.in);
		String ii = in.nextLine();
		// find 'a'
		int c=0;
		for ( int  i =0 ; i < ii.length() ; i++){
			if ( ii.charAt(i) == 'a'){
				c++;
			}
		}
		System.out.println("count of a :" + c);
		int an =0;
		for ( int i =0 ; i + 2 < ii.length() ; i++){
			String ss = ii.substring( i , i +3);
			if ( ss.equals("and")){
				an++;
			}
		}
		System.out.println("count of and : " + an); 
		
		System.out.println("starts with The : " + ii.startsWith("The"));  
		
		char[] arr = ii.toCharArray();
		
		System.out.println(arr);
		
		
		
	}
}
