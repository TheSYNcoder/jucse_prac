#include<stdio.h>
#include <stdlib.h>
struct student{
	int roll;
	char name[100];
	int scores[5];
};
const int MAX =10000;
int delarr[MAX];
int count =0;
typedef struct student data;
void getdata( data *s)
{
	printf("ENTER ROLL :");
	scanf("%d" , &(s -> roll));
	getchar();
	printf("ENTER NAME : ");
	scanf("%[^\n]%*c" , s -> name);
	
	for ( int i =0; i < 5; i++)
	{
		printf("SCORE IN SUB %d :",i+1 );
	scanf("%d" ,&(s -> scores[i]));
	}
}
void write()
{
	FILE *fp = fopen("student.dat" , "w");
	data s;
	getdata(&s);
	count++;
	fseek( fp , 0 , 2);
	fwrite(&s , sizeof(data) ,1, fp);
	fclose(fp);
}

void append()
{
	FILE *fp = fopen("student.dat" , "a");
	data s;
	getdata(&s);
	count++;
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
		if ( s.roll == roll && !delarr[roll])
		{
			printf("Record found\n");
			printf("NAME : %s\n" , s.name);
			printf("ROLL : %d\n" , s.roll);
			for ( int i =0; i < 5; i++)
			printf("SCORE %d = %d\n" ,i+1, s.scores[i]);
			fclose(fp);
			return;
			
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


		if ( s.roll == roll && !delarr[roll])
		{
			printf("Record found\n");
			printf("ROLL : %d\n" , s.roll);
			
			found =1;
			
			// fseek(fp , -1 , 1);
			// fseek(fp ,-1*(sizeof(data) ) , 1);
			printf("ENTER NEW MODIFIED DATA :\n");
			fseek(fp , 0 , 1);
			getchar();
			data ss;
			getdata(&ss);
			int c , d;
			c =fwrite(ss.name ,sizeof(char[100]) , 1, fp );
			for (int i =0; i < 5; i++)
			d |=fwrite(&(ss.scores[i]) , sizeof(int) , 1 , fp);
			if (c & d)
			printf("Written successfully\n");
			fclose(fp);
			return;
		}
		
		fread(s.name, sizeof(char[100]) ,1 , fp);
		for (int i =0; i < 5; i++)
		fread(&(s.scores[i]) , sizeof(int ) , 1, fp);
		offset++;

	}
	if (!found)
	{
		printf("Record not found :(\n");
		
	}
	fclose(fp);
	return;
	
	

}
void display()
{
	FILE *fp= fopen("student.dat" , "r");
	data s;
	int rec =0;
	printf("The details are of %d students are :\n" , count);
	while (!feof(fp))
	{
		// getchar();
		int c =fread(&s , sizeof(data) , 1, fp);
		if ( delarr[s.roll])
			continue;
		printf("ROLL :%d\n" , s.roll);
		printf("NAME : %s\n" , s.name);
		
		for ( int i =0; i < 5; i++)
		printf("SCORE IN SUB %d = %d\n" , i+1 , s.scores[i]);
		printf("\n"); 
		rec++;
		if ( rec == count)
			return;
		if ( !c)
			break;
	}

	printf("\n");
	fclose(fp);
}

void delet()
{
	printf("ENTER THE ROLL TO DELTE\n");
	FILE *fp = fopen("student.dat" , "r+");
	int roll;
	scanf("%d" , &roll);
	data s;
	while ( fread(&s , sizeof(data) , 1, fp)!=0)
	{
		if ( s.roll == roll)
		{
			printf("Record. found\n");
			delarr[roll]++;
			printf("Record deleted !!\n");
			fclose(fp);
			return;
		}
	}
	printf("Record not found :(\n");
	fclose(fp);
	return;

}
void phy_delete()
{
	printf("ENTER THE ROLL TO DELETE\n");
	int roll;
	scanf("%d" , &roll);
	FILE *fp = fopen("student.dat" ,"r+");
	FILE *ff = fopen("temp.dat" ,"w");
	data s;
	while ( fread(&s , sizeof(data) , 1, fp)!= 0)
	{
		if ( s.roll == roll)
		{
			continue;

		}
		fwrite(&s , sizeof(data ), 1, ff);
	}
	remove("student.dat");
	printf("'OLD FILE REMOVED'\n" );
	rename("temp.dat" , "student.dat");
	printf("NEW FILE CREATED\n");
	fclose(fp);
	fclose(ff);


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
		printf("3. TO PHYSICALLY DELETE RECORD FROM FILE\n");
		printf("4. TO SEARCH RECORD TO FILE\n");
		printf("5. TO EDIT RECORD TO FILE\n");
		printf("6. TO WRITE RECORD TO FILE\n");
		printf("7. TO DISPLAY RECORDS OF FILE\n");
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
			delet();
			break;
			case 3:
			phy_delete();
			break;
			case 4:
			search();
			break;
			case 5:
			edit();
			break;
			case 6:
			write();
			break;
			case 7:
			display();
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
