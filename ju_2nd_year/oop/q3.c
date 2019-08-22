#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("Enter The number of rows\n");
	int rows;
	scanf("%d" , &rows);
	int **p = ( int **) malloc( rows * sizeof (int *));
	printf("ENTER THE NUMBER OF COLUMNS\n");
	int cols;
	scanf("%d" , &cols);
	for ( int i =0; i < rows; i++)
	{
		*(p + i) = ( int *) malloc(cols * sizeof(int));
	}
	printf("ENTER THE 2D ARRAY ELEMENTS\n");
	for( int i =0; i < rows; i++)
	{
		for ( int j =0; j < cols; j++)
		{
			scanf("%d", (*(p + i) + j)); 
		}
	}
	printf("The array elements\n");
	for( int i =0; i < rows; i++)
	{
		for ( int j =0; j < cols; j++)
		{
			printf("%d ", *(*(p + i) + j)); 
		}
		printf("\n");
	}
	
}
