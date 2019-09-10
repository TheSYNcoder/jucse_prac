#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void sort( char **str ,int *age ,int n)
{
	for ( int i =0; i < n; i++)
	{
		for ( int j =0; j < i; j++)
		{
			if ( age[i] < age[j])
			{
				char temp[1000];
				strcpy(temp , str[i]);
				strcpy(str[i] , str[j]);
				strcpy(str[j] , temp);
				int te =age[i];
				age[i] =age[j];
				age[j] = te;
			}
		
		}
	
	} 
} 

void allocate( char ***strt,int **ages , int n)
{

	char **str = (char **) malloc(n * sizeof(char *));
	for ( int i =0; i < n; i++)
		str[i] = ( char *) malloc(1000 * sizeof(char));
	int *age = ( int *) malloc( n* sizeof(int));
	*strt = str;
	*ages =age;
}
void display( char **str , int *age , int n)
{
	printf("The details of the studenets are :\n");
	for ( int i =0; i < n; i++)
	{
		printf("name =%s \t age =%d\n" , str[i] , age[i]);
	
	}

}

int main()
{

	printf("ENTER THE NUMBER OF PERSONS\n");
	int n;
	scanf("%d" , &n);
	char **person;
	
	int *age;
	
	allocate(&person , &age , n);
	
	
	
	
	printf("ENTER THE NAME OF THE PERSON separated by , ALONG WITH AGE\n");
	for ( int i =0; i < n; i++)
	{
		getchar();
		scanf("%[^,]%*c%d" , *(person + i), age+i );
	}
	
	 sort( person , age , n);
	 display(person , age , n);
	
	
}
