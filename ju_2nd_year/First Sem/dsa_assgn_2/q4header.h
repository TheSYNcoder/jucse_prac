#include <stdio.h>

#define max( x , y) ((x) > (y) ? (x) : (y))

const int MAX = 1e5 +5;
const int ROWS = 30;
const int COLS =30;


// set has or not
// size of set
// insert
// search 
// delete
// 
int SET[MAX];
static int count =0;
int getdata()
{
	int val;
	if (!scanf("%d" ,  &val))
	{
		printf("The entered val must be an integer , taking 0 as default input\n");
		return 0;
	}
	return val;
}
void insert()
{
	printf("Enter the value to insert :");
	int val;
	val =getdata();
	if ( SET[val] )
		printf("Element exists\n");
	else
	{
		SET[val]+=1;
		count+=1;
	}
}

void has(int n =-1)
{
	if ( n == -1)
	{
		printf("Enter value to be searched\n");
		n = getdata();
	}
	if ( SET[n])
		printf("Element exists :)\n");
	else
		printf("Element does not exist :(\n");

}

void delet(int n =-1)
{
	if ( n == -1)
	{
		printf("Enter value to be searched\n");
		n = getdata();
	}
	if( !SET[n])
		printf("Element does not exist :(\n");
	else
	{
		SET[n]=0;
		printf("Element deleted successfully :)\n");
	}

}
void size()
{
	printf("The size of set is : %d\n" , count);
}