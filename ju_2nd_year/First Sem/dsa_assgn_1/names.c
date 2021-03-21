#include <stdio.h>
#include <string.h>

void sort( char roll[80][60] ,char name[80][60] , int no_of_students )
{
	for ( int i =0 ; i < no_of_students; i++)
	{
		for ( int j =0; j < i; j++ )
		{
			if ( strcmp(name[i] , name[j]) < 0)
			{
				char temp[45];
				strcpy(temp , name[i]);
				strcpy(name[i] , name[j]);
				strcpy(name[j] , temp);
				strcpy(temp , roll[i]);
				strcpy(roll[i] , roll[j]);
				strcpy(roll[j] , temp);
			}

		}
	}
	
}
int main()
{
	FILE *fp ;
	fp = fopen("roll-numbers-names.txt" , "r");
	char roll[80][60];
	char name[80][60];
	int no_of_students=0;
	int highest =0, lowest =1000;
	char high[100] , low[100];
	while ( fscanf( fp , "%[^,]%*c%*c%[^\n]%*c", roll[no_of_students] , name[no_of_students])!= EOF)
	{

		printf("%s %s\n" , roll[no_of_students] , name[no_of_students]);
		if ( strlen(name[no_of_students]) < lowest)
		{
			strcpy(low, name[no_of_students]);
			lowest = strlen(name[no_of_students]);
		}
		if ( strlen(name[no_of_students]) > highest)
		{
			strcpy(high, name[no_of_students]);
			highest = strlen(name[no_of_students]);

		}
		no_of_students++;

	}

	fclose(fp);
	printf("%d\n" , no_of_students);
	printf("The person %s has the highest no of characters = %lu \n",high, strlen(high) );
	printf("The person %s has the lowest no of characters = %lu \n",low, strlen(low) );
	sort(roll , name , no_of_students);
	fp = fopen("alphabetically-names.txt" , "w");
	fprintf(fp, "%s   %s\n","ROLL-NUMBER" , "NAME" );
	for ( int i =0; i < no_of_students; i++)
	{
		fprintf(fp, "%s %s\n",roll[i] , name[i] );
	}
	printf("Files written\n");
	fclose(fp);

}