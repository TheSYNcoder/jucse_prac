#include <stdio.h>


int main(){
		int num[1000];
		printf ("enter the number of integers you want o enter:\n");
		int t,i;
		scanf ("%d", &t);
		int count =0;int max = -1000000;int min = 1000000;
		while (t--){
				int s;
				scanf("%d" , &s);
				num[count++]=s;
				}
		for ( i =0; i < count; i++){
				if ( max < num[i])
					max = num[i];
				if ( min > num[i])
					min = num[i];
		}
		printf (" the range is from %d to %d", min , max);
		printf (" the max - min= %d", max - min);
		return 0;
		

}
