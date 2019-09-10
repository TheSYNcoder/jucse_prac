#include <stdio.h>
#include <stdlib.h>
int cols =50;
int main()
{
	// pointer to array
	//int  cols;
	//scanf("%d" , &cols);
	//int *(*p) = (int *(int *)) malloc(cols* sizeof ( int ));
	printf("ENTER THE NUMBER OF ROWS\n");
	int rows;
	scanf("%d" , &rows);
	int (*p)[cols];
	printf("ENTER THE NUMBER OF COLUMNS\n");
	int col;
	scanf("%d" , &col);
	//for ( int i =0; i < rows; i++)
	//{
		//*(p+ i) = ( int *) malloc(cols * sizeof(int));
	//
	p = ( int ** ) malloc( rows * cols * sizeof(int));
	printf("ENTER THE 2D ARRAY ELEMENTS\n");
	for( int i =0; i < rows; i++)
	{
		for ( int j =0; j < col; j++)
		{
			scanf("%d", (*(p + i) + j)); 
		}
	}
	printf("The array elements\n");
	for( int i =0; i < rows; i++)
	{
		for ( int j =0; j < col; j++)
		{
			printf("%d ", *(*(p + i) + j)); 
		}
		printf("\n");
	}
	
}
