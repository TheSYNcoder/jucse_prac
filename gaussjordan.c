#include <stdio.h>
void pr(float mat[1000][1001], int n)
{
  int i , j;
  for (i=0; i < n; i++)
  {
    for (j=0; j < n+1;j++)
    {
      printf("%f\t", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
void change(float mat[1000][1001], int i, int j)
{
  int k;
  for ( k=0; k < 4; k++)
  {
    float temp = mat[i][k];
    mat[i][k]=mat[j][k];
    mat[j][k]=temp;
  }
}
int main()
{
    printf("Enter the number of unknowns:" );
    int n;
    scanf ("%d", &n);
    printf("Enter the  augmented matrix\n" );
    int i, j, k;
    float mat[1000][1001];
    for (i=0; i < 1000; i++)
      for (j=0; j < 1001;j++)
        mat[i][j]=0.0;
    for ( i=0; i < n; i++)
      for ( j=0; j < n+1; j++)
        scanf("%f", &mat[i][j]);
        pr(mat, n);
    for ( i=0; i < n; i++)
    {
        int p=i;
				//for changing the rows if pivot element is 0
        while ( (mat[i][i]) == 0 && p <= n)
        {
          change(mat,i,p+1);
          p++;
        }
        float temp= mat[i][i];
        for ( j=i; j < n+1; j++)
        {
          mat[i][j] = mat[i][j]/temp;
        }
        for ( j=0; j < n;j++ )
        {
          if ( j != i)
          {
                float f = mat[j][i]/mat[i][i];
                for (k=i;k < n+1;k++)
                {
                  mat[j][k] -=f*mat[i][k];
                }
          }
        }
    }
    pr(mat, n);
}
