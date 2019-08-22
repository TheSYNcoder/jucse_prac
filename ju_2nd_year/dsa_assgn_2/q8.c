#include <stdio.h>
#include <assert.h>
const int MAX =1e5 +5;
int arr[MAX];
#define max( x , y) ((x) > (y) ? (x) : (y))
#define min( x , y) ((x) < (y) ? (x) : (y))

int help (int a , int b)
{
	return ( a >= b ? 1 : 0);
}
int check( int arr[MAX] , int n)
{
	if ( n <= 2)
		return 1;
	int ans =0;
	ans = help(arr[0] , arr[1]);
	for ( int i =1; i < n-1; i++)
		if ( ans != help(arr[i]  , arr[i+1]))
			return 0;
	return 1;
}
int main()
{
	printf("Enter the number of elements of the array\n");
	int n;
	scanf("%d" ,&n);
	assert( ("Array should have atleast one element and not negative elements\n" &&  n > 0));
	for ( int i =0; i < n; i++)
		scanf("%d" , &arr[i]);
	int ans = check( arr , n);
	if ( !ans)
		printf("The array is not sorted\n");
	else
	{
		printf("The array is sorted\n");
		printf("The sorting order : ");

		if ( n == 1)
			printf("Ascending\n");
		else 
		{
			int c = help( arr[0] , arr[1]);
			if ( c)
				printf("Descending\n");
			else 
				printf("Ascending\n");
		}
	}



}