#include <stdio.h>
#include <stdlib.h>

void getdims(int *rows, int *cols)
{
	printf("Enter The number of rows\n");
	scanf("%d" , rows);
	printf("ENTER THE NUMBER OF COLUMNS\n");
	scanf("%d" , cols);
}
void dyn_allocate(int ***pp, int rows, int cols)
{
	int **p;
	p = (int**)malloc( rows * sizeof(int*));
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
	*pp =p;
	
}
void display(int **p, int rows , int cols)
{
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
int main()
{
	int rows ;int  cols;
	getdims(&rows , &cols);
	int **p;
	dyn_allocate(&p, rows , cols);
	display(p, rows, cols);
}
