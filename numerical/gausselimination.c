#include <stdio.h>
#define pi 3.14159265358979


#include <stdlib.h>
#include <math.h>
void change ( float mat[100][100], int i, int j, int n)
{
    int k;
    for ( k =0; k < n+1; k++ )
    {
        float temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] =  temp;
    }
}

void pr( float mat[100][100], int n)
{
    int i, j;
    for ( i=0; i < n; i++)
    {
        for (j =0; j < n+1; j++)
            printf( "%f  " , mat[i][j]);
        printf("\n");
    }
    printf("\n\n");
}
int main()
{
    printf( "enter the number of unknowns:");
    int n;
    scanf( "%d", &n);
    static float mat[100][100];
    int i, j, k;
    for ( i =0; i < n; i++)
    {
        for ( j =0; j < n+1; j++)
            scanf( "%f" , &mat[i][j]);
    }
    for ( i =0; i < n; i++)
    {
        float temp = mat[i][i];
        int p=i+1;
        while ( mat[i][i] == 0 && p < n)
        {
            change( mat, i, p, n);
            p++;
        }
        for ( j =0; j < n+1; j++)
            mat[i][j]= mat[i][j]/ temp;
        for ( j =i+1; j < n; j++)
        {
            float f  = mat[ j][i]/ mat[i][i];
            for ( k=0;k< n+1;k++)
            {
                mat[j][k]-= f* mat[i][k];
            }
        }
        pr( mat, n);
    }
    pr(mat, n);
    static float x[100];
    for ( i=n-1; i >= 0; i--)
    {
        float sum =0;
        for ( j = n-1; j>  i;j-- )
            sum+=x[j]*mat[i][j];
        x[i]=(mat[i][n] - sum)/mat[i][i];
            
    }
    printf("The solution vector :\n");
    for ( i=0; i < n;i++)
        printf("x[%d] = %f \n" ,i+1, x[i]);
}

