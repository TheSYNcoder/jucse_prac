#include <stdio.h>
#include "q2header.h"



void add_op()
{
    resu  rs =add_mat();
    if (rs.val != -1)
        display(rs.r);
    else
        printf("BAD DATA\n");
}

int main()
{
    
    printf("ENTER THE NO OF SPARSE MATRICES :");
    int no;
    scanf("%d"  , &no);
    for ( int i =0; i < no; i++)
        getdata();
    while (1)
    {

        printf("MENU ::::\n");
        printf("1. For adding two matrices\n");
        printf("2. For transposing a matrix\n");
        printf("3. For multiplying two matrices\n");
        printf("4. For displaying a  matrix\n");
        printf("CHOICE ::: ");
        int choice;
        scanf("%d"  , &choice);
        switch(choice)
        {
            case 1:
                add_op();
            break;
            case 2:
                transpose();
            break;
            case 3:
                multiply();
            break;
            case 4:
                printf("Enter the index of the matrix between 0 and %d(inclusive)\n",count -1 );
                int index;
                scanf("%d" , &index);
                display(matrices[index]);
            break;
            default:
                printf("Wrong choice :(\n");
            break;
        }
        getchar();
        char ch;
        printf("Enter y/n to continue or exit\n");
        scanf("%c" , &ch);
        if ( ch != 'Y' &&  ch != 'y')
            break;

    }
    printf("BYE :(\n");
}
