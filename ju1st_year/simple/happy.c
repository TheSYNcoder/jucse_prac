#include <stdio.h>
int sqdigits(int n)
{
		int sum=0;
		while (n > 0)
		{
		int r = n%10;
		sum+=r*r;
		n/=10;
		}
		return sum;
}
int main()
{
		int c=1;int d=1;int i=1;
		while (c <=10)
		{
					int temp=i;d=1;
					while (d <=100)
					{
							
							int r = sqdigits(temp);
							if (r ==1){
								c++;
								
								printf("%d\n",i);
								break;
								}
							else{
								temp =r;
								}
								d++;
							
					}
					i++;
		}
	return 0;
}

