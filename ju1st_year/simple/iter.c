#include <stdio.h>


int main()
{
			printf("Enter a number\n");
			int n;
			scanf("%d" , &n);
			int result =n;int iter=0;
			printf("Initial value is= %d", n);
			while (result!=1)
			{
						 
						iter++;
						if (result & 1)
							result = result*3 +1;
						else
							result/=2;
							
						printf("Next value is= %d\n",result);
			} 
			printf("NUmber of operations = %d", iter);

}
