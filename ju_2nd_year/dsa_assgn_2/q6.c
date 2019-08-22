#include <stdio.h>

const int MAX =1e5 +5;
int arr[MAX];
#define max( x , y) ((x) > (y) ? (x) : (y))
#define min( x , y) ((x) < (y) ? (x) : (y))

#define ll long long int
void compute_max(int n, int k)
{
	printf("Max array :: \n");
	if ( k  > n)
		printf("filter size should be less than no of elements\n");
	int output[MAX];
	for ( int i =0; i < MAX; i++)
		output[i]=0;
	int mx = -100000000;
	int i;
	int cnt =0;
	for  (i = 0; i < k ; i++)
		mx = max( mx , arr[i]);
	for ( ; i < n; i++)
	{
		output[cnt++] = mx;
		mx = max( mx, arr[i]);
	}
	for ( int i =0; i < cnt; i++)
		printf("%d  ", output[i] );
	printf("\n");

}

void compute_mean(int n, int k)
{
	printf("Mean array :: \n");
	if ( k  > n)
		printf("filter size should be less than no of elements\n");
	double output[MAX];
	for ( int i =0; i < MAX; i++)
		output[i]=0;
	
	int i;
	int cnt =0;
	ll sum =0;
	for  (i = 0; i < k ; i++)
		sum+= arr[i];
	for ( ; i < n; i++)
	{
		output[cnt++] = (sum*1.0) / (k*1.0);
		sum+= arr[i] - arr[i-k];
	}
	for ( int i =0; i < cnt; i++)
		printf("%d  ", output[i] );
	printf("\n");

}

void compute_min(int n, int k)
{
	printf("Min array :: \n");
	if ( k  > n)
		printf("filter size should be less than no of elements\n");
	int output[MAX];
	for ( int i =0; i < MAX; i++)
		output[i]=0;
	int mn = 100000000;
	int i;
	int cnt =0;
	for  (i = 0; i < k ; i++)
		mn = min( mn , arr[i]);
	for ( ; i < n; i++)
	{
		output[cnt++] = mn;
		mn = min( mx, arr[i]);
	}
	for ( int i =0; i < cnt; i++)
		printf("%d  ", output[i] );
	printf("\n");

}
int pos(aux[MAX] , int el , int k)
{
	int l = 0;
	int r =k-1;
	while ( l < r && l < k )
	{
		int m = ( l + r) >> 1;
		if ( aux[m] > el)
			l = m+1;
		else 
			r= m;
	}
	return l;
}
void compute_median(int n, int k)
{
	printf("Median array :: \n");
	if ( k  > n)
		printf("filter size should be less than no of elements\n");
	int output[MAX];
	for ( int i =0; i < MAX; i++)
		output[i]=0;
	int mn = 100000000;
	int i;
	int cnt =0;
	int aux[MAX];
	int set[MAX];
	for ( int i =0; i < k ; i++)
	{
		aux[i]=arr[i];
	}
	for ( int i=0; i < k; i++)
		for ( int j =0; j < i; j++)
			if ( aux[j] > aux[i])
			{
				int temp = aux[j];
				aux[j] =aux[i];
				aux[i] =temp;
			}
	int med = aux[k/2];

	for ( ; i < n; i++)
	{
		output[cnt++] =med;
		int low =arr[i-k];
		int high = arr[i];
		int pos1 = 
		

	}
	for ( int i =0; i < cnt; i++)
		printf("%d  ", output[i] );
	printf("\n");

}


int main()
{
	printf("ENter the array elements\n");
	printf("Enter the number of elements : \n");
	int n;
	scanf("%d" , &n);
	for ( int i =0; i < n; i++)
		scanf("%d" , &arr[i]);
	printf("Enter the filter size :");
	int filter_size;
	scanf("%d" , filter_size);
	// mean arr
	compute_mean(n , filter_size);
	//max arr
	compute_max(filter_size);
	// min arr
	compute_min(filter_size);
	// median arr
	compute_median(filter_size);
}