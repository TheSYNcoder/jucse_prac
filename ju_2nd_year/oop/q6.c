#include <stdio.h>

struct student{
	const name[1000];
	int age;

};
typedef struct student data;
void sort( data nw)
{
	for ( int i =0; i < n; i++)
	{
		for ( int j =0; j < i; j++)
		{
			if ( nw.age[i]< nw.e[j])
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

int main()
{

	printf("Enter the number of students\n");
	int n;
	scanf("%d" ,&n);
	data *array = malloc(n *sizeof(student));
	
	printf("ENTER THE NAME OF THE PERSON separated by , ALONG WITH AGE\n");
	for ( int i =0; i < n; i++)
	{
		getchar();
		scanf("%[^,]%*c%d" ,data[i].name , data[i].age);
	}
	
	 
	

}
