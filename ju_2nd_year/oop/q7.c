#include <stdio.h>
#include <stdlib.h>

struct student{
	int roll;
	char name[100];
	int score;
};
struct node{
	struct student data;
	struct node *ptr;
};
void getdata( struct student *data)
{
//truct student *data;
	
	printf("ENTER THE NAME ");
	scanf("%[^\n]%*c" ,data -> name);
	printf("ENTER ROLL NUMBER ");
	scanf("%d" , & (data -> roll));
	printf("ENTER SCORE ");
	scanf("%d", & (data-> score));
	getchar();
	
	
}
void create( struct node *pt)
{
	struct node *p;
	p =( struct node *)malloc(sizeof(struct node));
	p -> ptr =NULL;
	struct student dat;
	getdata(&dat);
	p-> data =dat;
	while (pt-> ptr)
		pt= pt -> ptr;
	pt -> ptr =p;
	
}

void del( int roll_no , struct node *head)
{
	while ( head -> ptr )
	{
		if ( head -> ptr-> data.roll == roll_no)
		{
			if ( head -> ptr -> ptr == NULL)
			{
				head -> ptr -> ptr =(struct node*) malloc(sizeof(struct node));
				head -> ptr -> ptr -> ptr =NULL;
			}
			head -> ptr = head -> ptr -> ptr;
			free(head-> ptr);
		}
		head = head-> ptr;
	
	}
	printf("ROLL not found\n");


}
void insert( int roll_no,struct node *head)
{
	
	
	struct node *p = (struct node *) malloc ( sizeof ( struct node ));
	struct student dat;
	getdata(&dat);
p->data= dat;
	while ( head -> ptr)
	{
		if ( head -> ptr -> data.roll == roll_no)
		{
			p-> ptr = head-> ptr;
			head-> ptr =p;
			
			return;
		}
		head = head -> ptr;
	}
	printf("ROLL not found\n");

}
void display( struct node *p)
{
	while ( p)
	{
		printf("NAME : %s\n", p ->data.name);
		printf("ROLL : %d\n" , p-> data.roll);
		printf("Score : %d\n", p-> data.score);
		printf("\n");
		p = p -> ptr;
		
	}

}

int main()
{
	struct node *head;
	head = (struct node*) malloc(sizeof(struct node));
	head -> ptr =NULL;
	head -> data.roll =0;
	head -> data.score =0;

	create(head);
	insert( 1 , head);
	del( 1, head);
	display(head);

}
