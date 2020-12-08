#include <stdio.h>

int pow1(int n , int i){
          int j;int temp =n;
          if (i==0)
            return 1;
          else{
          for (j=1; j < i; j++){
            n=n*temp;
          }
          return n;
        }
}
void sortarr(int *arr){
int i,j;
  for (i=0; i < 4; i++)
    for ( j =0; j < 3; j++)
              if (arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
              }

}
void printarr(int *arr){
  int i;
  for (i =0; i < 4; i++){
    printf ("%d", arr[i]);
  }
  printf("\n");
}
int kaprekar(int n){
              int arr[4];
              int i;int max=0, min=0;
              for (i=3; i >= 0; i--){
                        arr[i]= n%10;
                        n/=10;
              }
              //to sort the array
              sortarr(arr);
              // arr is ascending
              int revarr[4];
              for ( i =0; i < 4; i++)
                          revarr[i]= arr[3-i];

              for ( i =0; i < 4; i++){
                          max += revarr[i] * pow1(10,3-i);
                          min += arr[i] * pow1(10, 3-i);
              }
              //printf("%d\n",max);
              //printf("%d\n",min);

              return (max - min);
}


int main(){
      //to input the the number from the user
      int n;
      scanf("%d", &n);
      FILE *ouf = fopen("output.txt","wt");
      //to insert the number into an char array
      int c=kaprekar(n);int count=1;
      //printf("%d\n",c);
      if ( c== n)
          fprintf(ouf, "the kaprekar number = %d", c);
      else
          {

                  fprintf(ouf, "iterating round:%d , number =%d\n",count, c );
                  count++;
                  int d = kaprekar(c);
                        while (1){
                        if (d == c){
                            fprintf(ouf, "the kaprekar number = %d", d);
                            break;
                          }
                        else{
                          fprintf(ouf, "iterating round:%d, number=%d\n",count, d );
                          count++;
                          int e = kaprekar(d);
                          c=d;
                          d=e;
                        }

                }
          }
        }
