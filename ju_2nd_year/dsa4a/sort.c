#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
// bubble sort

void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}
void sort( int *arr , int n){
    int i, j;
    for ( i = 0; i < n; i++){
        for ( int j = 0; j < n-1-i ; j++){
            if ( arr[j] > arr[i]){
                arr[j] = arr[i] + arr[j];
                arr[i] = arr[j] - arr[i];
                arr[j] = arr[j] - arr[i];
            }
        }
    }
}


void heapify( int *arr , int n , int i){
    int largest = i;
    int left = 2*i +1;
    int right = 2*i +2;

    if ( left < n && arr[left] < arr[largest])
        largest = left;
    if ( right < n && arr[right] < arr[largest])
        largest = right;
    
    if ( largest != i){
        swap( &arr[i] , &arr[largest]);
        heapify( arr , n , largest);
    }
}
void sort( int *arr , int n){
    int j;
    for ( j = n/2; j >= 0 ; j --){
        heapify( arr , n , j);
    }
    for ( j = n-1 ; j>= 0; j--){
        swap( &arr[0] , &arr[j]);
        heapify( arr , j , 0);
    }
}

void insort( int *arr , int n){
    int i , j;
    for (  i = 1 ; i < n ; i++){
        int key = arr[i];
        int j = i-1;
        while ( j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
int part( int *arr ,int l ,int h){
    int pivot = arr[h];
    int i = l-1;
    int j;
    for ( j = l ; j < h ; j++){
        if ( arr[j] < pivot){
            i++;
            swap(&arr[j] , &arr[i]);
        }
    }
    swap(&arr[i+1] , &arr[h]);
    return (i+1);
}
void qq( int *arr , int l , int h){
    if (l < h){
        int p = part( arr , l , h);
        qq( arr , l , p-1);
        qq( arr , p+1 , h);
    }
}

void qqsort( int *arr , int n){
    qq(arr , 0 , n-1);
}
void merge( int *arr , int l , int m, int h){

    int n1 = m - l +1;
    int n2 = h - m ;
    int *left = (int *)malloc( n1 * sizeof(int));
    int *right = (int *)malloc( n2 *sizeof(int));
    
    

    int i=0 , j=0 , k=0;
    for ( i =0 ; i < n1; i++){
        left[i] = arr[l+i];
    }
    for ( i =0; i < n2; i++){
        right[i] = arr[m+1+i];
    }
    i =0;
    while ( i  < n1  && j < n2){

        if ( left[i] < right[i]){
            arr[k] = left[i++];
        }
        else{
            arr[k]=right[j++];
        }
        k++;
    }
    while ( i < n1){
        arr[k] = left[i];
        i++;k++;
    }
    while ( j < n2){
        arr[k] = right[j];
        j++;k++;
    }
}
void mergsort( int *arr , int l , int h){
    if ( l <h){
    int m = ( l + h ) >> 1;
    mergsort( arr , l , m);
    mergsort( arr , m+1 , h);
    merge( arr , l , m , h);
    }
} 
void msort( int *arr , int n){
    mergsort(arr , 0 , n-1);
}
int main(){
    clock_t t;
    
    FILE *fp;
    int n = 100000;
    char filename[89];
    strcpy(filename ,"");
    char dd[999];
    sprintf(dd , "%d" , n);
    strcat(filename , dd);
    strcat(filename ,".txt" );
    // printf("%s\n" ,filename );
    fp = fopen(filename ,"r" );
    int x;
    int *arr = (int*)malloc( (n+1)*sizeof(int));
    int cnt = 0;
    while ( 1){
        fscanf(fp ,"%d" , &x);
        arr[cnt++] = x;
        if ( feof(fp))break;
    }
    t = clock();
    msort(arr, n);
    // fun();
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    fclose(fp);
    printf("%s took %f seconds to execute \n",filename ,time_taken);

    

    
    
}