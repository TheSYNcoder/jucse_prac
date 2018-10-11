#include <stdio.h>


int main(){
	printf( "the sum of the given series");
	printf("\n input the number n");
	printf("\n");
	int n;
	scanf("%d", &n);int i,sum;
	sum=0;
	for ( i =1; i <=n ; i++){
		sum+= i*(i+1);
	
	}
	printf ("sum = %d", sum);
	return 0;


}
