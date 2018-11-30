//
//  add.cpp
//  testing
//
//  Created by Shuvayan Ghosh Dastidar on 28/06/18.
//  Copyright © 2018 Shuvayan Ghosh Dastidar. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#define fie ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;
#define ll long long int
#include <vector>
#define pi 3.14159265358979


#include <stdlib.h>
#include <math.h>
int main()
{
    printf( " Enter the number of unknowns\n");
    int n;scanf( "%d", &n);
    float mat[100][100];
    printf("Enter the augmented matrix\n");
    int i,j;float xd[100];
    for ( i=0; i < n; i++)
    {
        for ( j=0; j < n+1 ; j++)
            scanf( "%f", &mat[i][j]);
    }
    float x[100];
    for ( i =0; i < n; i++)
    {
        x[i] = 0;
    }
    int iter;
    printf("Enter the max no of iterations");
    int maxm;
    scanf("%d", &maxm );
   
    for ( iter =1; iter <= maxm; iter++)
    {
        float big =0.0;
        for ( i=0; i < n; i++)
        {
            float sum =0.0;
            for (  j =0; j < n ;j++)
            {
                if ( i!= j)
                    sum += mat[i][j]/mat[i][i] * x[j];
            }
            xd[i] = mat[i][n]/mat[i][i] - sum;
            float reler = fabs((xd[i] -x[i])/x[i]);
            if ( reler > big)
                big= reler;
            
        }
        for ( i=0; i < n; i++)
        {
            x[i] =xd[i];
        }
        printf("Iteration %d:\t", iter);
        for ( i=0; i < n; i++)
            printf("%.6f\t", x[i]);
        printf("\n");
        if ( big <= 0.00001)
        {
            printf("converges\n" );
            return 0;
        }
    }
    printf("Does not converge");
    
    
}


