//program to print the sum of sum of factors upto n

#include <stdio.h>
int factsum(int n)
{
		int i;int sum=0;
		for( i=1;i <= n;i++)
		{
				if ( n % i ==0)
					sum+=i;
		}
		return sum;
}
int main()
{
		printf ("Enter number");
		int n,i;int sum=0;
		scanf("%d" ,&n);
		for (i =1; i <=n; i++)
		{
				sum+=factsum(i);
				printf("%d@ + ",i);
		}
		printf("= %d", sum);
		return 0;
}


