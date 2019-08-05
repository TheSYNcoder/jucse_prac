#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct trienode{
	trienode *alpha[26];
	int isend;
};

#define node struct trienode 
node *getnode( )
{
	node *n;
	n = ( node * )malloc(sizeof(trienode));
	n ->isend = 0;
	for ( int i =0; i < 26; i++)
		n ->alpha[i] =NULL;
	return n;
}
void insert( node* root , char *s)
{
	for ( int i =0; i < strlen(s); i++)
	{
		int s1 = s[i]-'a';
		if ( !root -> alpha[s1])
			root -> alpha[s1] =getnode();
		root = root -> alpha[s1];
	}
	root->isend=1;
}
int search( node* root , char* s)
{
	for ( int i =0; i < strlen(s); i++)
	{
		int s1 = s[i] -'a';
		if ( !root -> alpha[s1])
			return 0;
		root = root-> alpha[s1];
	}
	if ( !root -> isend) return 0;
	return 1;
}
int main()
{
	node * root =getnode();
	int count =0;
	FILE *fp;
	fp = fopen("text.txt" , "w");
	int coll =0;
	while ( count < 1e5)
	{
			char s[10];
		for ( int i =0; i < 10; i++)
		{
			char c =(char) (rand()%26 + 'a');
			s[i]=c;
		}
		if ( search(root , s))
		{
			printf("Collision\n");
			coll++;
		}
		else
		{
			insert(root ,s);
			count++;
			fprintf( fp , "%s\n", s);

		}

    }
    fclose(fp);
    printf("%d\n", coll);

}