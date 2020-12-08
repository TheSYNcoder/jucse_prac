#include <stdio.h>

int prime[100005];
int main(){
	for (int k=0; k < 100005;k++)
	printf ("enter the number less than which primes are to be found\n"); 
	int n;
	scanf ("%d" , &n);int flag;int i,j;
	
	for ( i=n-1; i >= 2; i--){
	flag =1;
		for ( j =2; j < i; j++){
			if ( i % j==0){
				dp
				flag = 0;
				break;
				}
			}
			if (flag)
			printf("%d --", i);	
	
	}
	
	
	return 0;
	}


