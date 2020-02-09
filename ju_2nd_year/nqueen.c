#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define abs(x) ((x) >= 0 ? (x) : -(x))
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void display(int *arr, int n)
{
    int i = 0;
    for (; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void permute( int *arr , int n){

    if ( n == 0) return;
    srand(time(NULL));
    int index = rand() % n;
    swap(&arr[n-1] , &arr[index]);
    permute( arr , n-1);
}

// int compute_collisions( int *dn , int *dp , int n , int q[]){
//     int r ;
//     int i;
//     for ( i  =0; i < 2*n ; i++)
//         dn[i]=0;
//     for (i = 0; i < 2 * n; i++)
//         dp[i] = 0;
    
//     for ( r =0;  r < n; r++){
//         int c = q[r];
//         dn[r+c]++;
//         dn[(r-c)+n-1]++;
//     }
//     int sum =0;
//     for (  i =0; i < 2*n; i++){
//         sum += dn[i] + dp[i];
//     }
//     return sum;

// }
// int compute_attacks( int q[], int *attack , int *dp , int *dn){
//     int cnt =0;


// }
int safe(int n, int *q)
{

    int a, b, c, x;
    a = q[n];
    b = a - n;
    c = a + n;
    for (x = 0; x < n; x++, b++, c--)
    {
        if (q[x] == a || q[x] == b || q[x] == c)
        {
            return 0;
        }
    }
    return 1;
}
void print( int *q , int n){
    int i , j;
    for ( i =0 ; i < n ; i++){
        for ( j =0; j < n ; j++){
            if (q[j] == i) printf("Q ");
            else printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}
int queen(int *q, int n, int bsize, int limit)
{
    static int iteration = 0;
    int t = bsize;
    if (n > bsize - 1)
        return (1);
    if (n == 0)
        iteration = 0;
    do
    {
        
            if (safe(n, q))
            { 
                // print(q,bsize);
                if (queen(q,n + 1, bsize , limit))return 1; // is  a solution
                 
            }
        
        /* move_vertical */
        if (++q[n] == bsize)
            q[n] = 0;
    }
    /* iteration limit is optional */
    while (--t && ++iteration < limit);
    return (0);
}

int main(int argc, char **argv)
{
    int n, bsize = 8;
    int *q;
    // srand(time(0));
    if (argc > 1)
        bsize = atoi(argv[1]);
    if (bsize < 1)
        bsize = 8;
    q = malloc(bsize * sizeof(int));
    int i;
    for ( i = 0; i < bsize ; i++)
        q[i]= i;
    int sol =0;
    clock_t t, init;
    init =clock();
    while ( 1){
        permute(q , bsize);
        // print(q,bsize);
        // display(q , bsize);
        if (queen(q, 0, bsize, bsize * bsize))
        {
            sol++;
            // print(q,bsize);
            t = clock() - init;
            double time_taken = ((double)t) / CLOCKS_PER_SEC;
            printf("sol:%d ,Time : %f ,Speed : %f\n",sol, time_taken , sol/time_taken);
        }
        else{
            printf("-");
        }
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("No of sol: %d\n" , sol);
    printf("Time : %f\n" , time_taken);
}