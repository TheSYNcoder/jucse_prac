#include <stdio.h>

/*void swap( char *p, char *s){
	char *temp;
	temp = p;
	p = s;
	s = temp;

}*/

int main(){
		int n;
		printf ("enter te number:\n");
		scanf ("%d", &n);
		char num[4];int i=3;int j;char key;
		while (i >= 0){
			num[i--] =(char)((n %10)+48);
			n/=10;
		}
		
		for ( i =1;i < 4; i++){
			key = num[i];
			for ( j=i-1; j >=0 ;j--){
				if ( num[j] > key)
					num[j+1] = num[j];
					}
					num[j+1] =key;   
		
		} 
		printf ("%s", num);
		
		
		




}
