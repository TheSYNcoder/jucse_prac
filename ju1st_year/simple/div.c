//program to print the no divisible nby n

#include <stdio.h>


int main()
{
		printf("Enter the number");
		int n;
		scanf("%d", &n);
		int i;
		for( i=1; i <= 100; i++)
			if( i % n == 0)
				printf("%d ",i);
				
				
		return 0;
		

}
