//program to find the base converted form of any number
#include <stdio.h>
#include <string.h>
#include <math.h>
//prints the array
void printnum2(char *arr, int l){
    int i;
    for (i =l-1; i >= 0; i-- ){
      printf("%c" , arr[i]);
    }
}

int main(){
  int base1, base2;char str[1000];
  printf("Enter the base of the first number:\n");
  scanf("%d",&base1);
  printf("Enter the number\n");
  scanf("%s",str);
  printf("Enter the base of the second number:\n");
  scanf("%d",&base2);
  int l = strlen(str);int dec=0;int i;

  for ( i= 0; i < l; i++){
     if ((int)str[i] < 58)
     dec += ((int)str[i] -48)*pow(base1,l-1-i);
     else
     dec += ((int)str[i] -87)*pow(base1,l-1-i);
  }

  char num2[1000];int count=0;int r;
  if (base2 == 10)
  printf("%d" , dec);
  else{

  while (dec >0 ){
    r = dec % base2;
    if ( r <10)
    num2[count++] = (char)(r+48);
    else
    num2[count++] = (char)(r+87);
    dec = dec/base2;
  }
  printnum2(num2,count);
}
return 0;
}
