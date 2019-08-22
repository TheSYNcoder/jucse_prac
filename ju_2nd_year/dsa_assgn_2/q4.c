#include <stdio.h>
#include "q4header.h"



int main()
{
	while ( 1)
	{
	    printf("MENU ::::\n");
	    printf("1.To insert an element\n");
	    printf("2.To check an existence of an  element\n");
	    printf("3.To delete an element\n");
	    printf("4.To know size of the set \n");

	    printf("CHOICE ::: ");
	    int choice;
	    choice = getdata();
	    
	    
	    switch(choice)
	    {
	        case 1:
	            insert();
	        break;
	        case 2:
	            has();
	        break;
	        case 3:
	            delet();
	        break;
	        case 4:
	            size();
	        break;
	        default:
	            printf("Wrong choice :(\n");
	        break;
	    }

	}
}