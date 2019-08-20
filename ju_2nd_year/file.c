#include<stdio.h>
#include <stdlib.h>
struct student{
	int roll;
	char name[100];
	int scores[5];
};
typedef struct student data;
void getdata( data *s)
{
	printf("ENTER ROLL :");
	scanf("%d" , &(s -> roll));
	printf("ENTER NAME : ");
	scanf("%[^\n]%*c" , s -> name);
	
	for ( int i =0; i < 5; i++)
	{
		printf("SCORE IN SUB %d :",i+1 );
	scanf("%d" ,&(s -> scores[i]));
	}
}


void append()
{
	FILE *fp = fopen("student.dat" , "a");
	data s;
	getdata(&s);
	fseek( fp , 0 , 2);
	fwrite(&s , sizeof(data) ,1, fp);
	fclose(fp);
}
void search()
{
	FILE *fp = fopen("student.dat" , "r");
	data s;
	printf("ENTER ROLL TO BE SEARCHED :");
	int roll;
	scanf("%d" , &roll);
	while ( fread( &s , sizeof(data) , 1, fp)!=0)
	{
		if ( s.roll == roll)
		{
			printf("Record found\n");
			printf("NAME : %s\n" , s.name);
			printf("ROLL : %d\n" , s.roll);
			for ( int i =0; i < 5; i++)
			printf("SCORE %d = %d\n" ,i+1, s.scores[i]);
			return ;
		}
	}
	printf("Record not found :(\n");
	fclose(fp);

}
void edit()
{
	FILE *fp= fopen("student.dat" , "r+");
	printf("ENTER ROLL TO BE SEARCHED :");
	data s;
	int roll;
	scanf("%d" , &roll);
	int offset =0;
	int found =0;
	fseek( fp , 0 , 0);
	while ( fread( &(s.roll) , sizeof(int) , 1, fp)!=0)
	{

		if ( s.roll == roll)
		{
			printf("Record found\n");
			printf("NAME : %s\n" , s.name);
			printf("ROLL : %d\n" , s.roll);
			
			found =1;
			
			// fseek(fp , -1 , 1);
			printf("ENTER NEW MODIFIED DATA :\n");
			getchar();
			data ss;
			getdata(&ss);
			fwrite(ss.name ,sizeof(char[100]) , 1, fp );
			for (int i =0; i < 5; i++)
			fwrite(&(ss.scores[i]) , sizeof(int) , 1 , fp);
			printf("Written successfully\n");
			return;
		}
		offset++;
	}
	if (!found)
	{
		printf("Record not found :(\n");
		return;
	}
	
	

}

int main()
{
	while ( 1)
	{
		for ( int i =0 ; i < 25; i++)
		printf("-");
		printf("MENU");
		for ( int i =0; i <25; i++)
			printf("-");
		printf("\n");
		printf("1. TO APPEND RECORD TO FILE\n");
		printf("2. TO DELETE RECORD FROM FILE\n");
		printf("3. TO SEARCH RECORD TO FILE\n");
		printf("4. TO EDIT RECORD TO FILE\n");
		printf("5. TO APPEND RECORD TO FILE\n");
		printf("ENTER VALUE :");
		int n;
		scanf("%d" , &n);
		getchar();
		switch(n)
		{
			case 1:
			append();
			break;
			case 2:

			break;
			case 3:
			search();
			break;
			case 4:
			edit();
			break;
			default:
			printf("Wrong choice man :(\n");
			break;
		}
		getchar();
		char ch;
		printf("ENTER y/n to continue or exit the program :");
		scanf("%c" , &ch);

		
		if ( ch == 'Y' || ch == 'y')
			continue;
		else 
			break;
	}
printf("BYE :(\n");
	
}
