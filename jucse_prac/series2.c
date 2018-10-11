#include <stdio.h>

int dp[100];

/*int fact(int n){
	if(dp[n]!=0)
		return dp[n];
	else{
		dp[n] = n * fact(n-1);
		return dp[n];
	} 
}*/
int fact(int n){
	if ( n==1)
		return 1;
	else 
		return (n * fact(n-1));

	} 
	
int main(){
	int sum, i, n;
	for( i=0; i < 100; i++)
		dp[i]=0;
	dp[0]=1;
	dp[1]=1;
	
	sum=0;
	printf ("enter the number n upto which the series is to be calculated\n");
	scanf ("%d", &n);
	for (i =1; i <= n; i++){
		sum += fact(i);
	}
	printf ("the sum of the series =%d\n" , sum);
	return 0;
}

