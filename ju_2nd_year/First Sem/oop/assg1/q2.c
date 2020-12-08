#include <stdio.h>
#include <stdlib.h>

int main()
{	
	printf("ENTER THE SIZE OF THE ARRAY\n");
	int size;
	scanf("%d" ,&size);
	int *array = (int *)malloc(size * sizeof(int));
	printf("ENTER THE VALUES: ");
	for ( int i =0; i < size ; i++)
	{
		scanf("%d" , array+i);
	}
	
	printf("Printing the values\n");
	for ( int i =0; i < size; i++)
	{
		printf("%d " , *(array+i));
	}
	
}
