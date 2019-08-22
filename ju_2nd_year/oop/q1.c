#include <stdio.h>


int main()
{
	int a;
	int *p = &a;
	int **pp = &p;
	printf("ENTER A NUMBER\n");
	scanf("%d" , &a);
	printf("The value of *p = %d\n" , *p);
	printf("The value of **p = %d\n" , **pp);
	
	
	
}
