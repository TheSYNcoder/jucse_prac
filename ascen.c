#include <stdio.h>
//sorting the array

void sortarray(int *arr)
{
				int i, j;
				for ( i=0; i < 10; i++)
					for ( j=1; j < 10; j++)
						if ( arr[j]  < arr[j-1])
						{
								int temp = arr[j];
								arr[j] = arr[j-1];
								arr[j-1] = temp;
						} 
}

int main()
{
			int arr[10];
			int i;
			// inputting the array
			for ( i=0; i < 10; i++)
			{
									scanf("%d", &arr[i]);
			}
			
			sortarray(arr);
			//printing the array
			for ( i=0; i < 10; i++)
					printf("%d" , arr[i]);
			return 0;		
			
}
