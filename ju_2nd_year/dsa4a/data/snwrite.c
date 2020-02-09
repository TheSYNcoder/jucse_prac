#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
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
void hsort( int *arr , int n){
    int j;
    for ( j = n/2; j >= 0 ; j --){
        heapify( arr , n , j);
    }
    for ( j = n-1 ; j>= 0; j--){
        swap( &arr[0] , &arr[j]);
        heapify( arr , j , 0);
    }
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

int part(int *arr, int l, int h)
{
    int pivot = arr[(l+h)/2];
    int i = l - 1;
    int j;
    for (j = l; j < h; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[j], &arr[i]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}
void qq(int *arr, int l, int h)
{
    if (l < h)
    {
        int p = part(arr, l, h);
        qq(arr, l, p - 1);
        qq(arr, p + 1, h);
    }
}

void qqsort(int *arr, int n)
{
    qq(arr, 0, n - 1);
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
void bsort( int *arr , int n){
    int i, j;
    for ( i = 0; i < n; i++){
        for ( int j = 0; j < n-1-i ; j++){
            if ( arr[j] > arr[i]){
                swap(&arr[j], &arr[i]);
            }
        }
    }
}
void selsort( int *arr , int n){
    int i, j;
    for ( i = 0; i < n; i++){
        int mn = 1e9; int index = i;
        for ( int j = i; j < n ; j++){
            if ( mn > arr[j]){
                mn = arr[j];
                index = j;
            }
        }
        swap(&arr[i] , &arr[index]);
    }
}
int main(){
    clock_t t;
    int n = 10000;
    int i = 1;
    FILE *fp;
        fp = fopen("sortcmp.csv" , "a");
        fprintf(fp ,"data,Heap,Merge,Quick,Insertion,Bubble,Selection\n");
        fclose(fp);
        int *arr;
    char *filename;
    char *dd;
    int x;int cnt;
    
    
    for ( ; i <= 10 ; i++){
        int nn = n*i;
        // FILE *fp;
        // char filename[89];
        filename = (char *)malloc(89*sizeof(char));
        dd = (char *)malloc(100*sizeof(char));
        // char filename[89];
        strcpy(filename ,"ran");
        // char dd[999];
        sprintf(dd , "%d" , nn);
        strcat(filename , dd);
        strcat(filename ,".txt" );
        fp = fopen(filename ,"r" );
        // int x;
        arr = (int*)malloc( (nn+1)*sizeof(int));
        cnt = 0;
        while ( 1){
            fscanf(fp ,"%d" , &x);
            arr[cnt++] = x;
            if ( feof(fp))break;
        }
        
        t = clock();
        hsort(arr, nn);
        t = clock() - t;
        double time1 = ((double)t) / CLOCKS_PER_SEC;
        fclose(fp);
        free(arr);
        free(filename);
        free(dd);

        filename = (char *)malloc(89*sizeof(char));
        dd = (char *)malloc(100*sizeof(char));
        // char filename[89];
        strcpy(filename ,"ran");
        // char dd[999];
        sprintf(dd , "%d" , nn);
        strcat(filename , dd);
        strcat(filename ,".txt" );
        fp = fopen(filename ,"r" );
        // int x;
        arr = (int*)malloc( (nn+1)*sizeof(int));
        cnt = 0;
        while ( 1){
            fscanf(fp ,"%d" , &x);
            arr[cnt++] = x;
            if ( feof(fp))break;
        }
        
        t = clock();
        msort(arr, nn);
        t = clock() - t;
        double time2 = ((double)t) / CLOCKS_PER_SEC;
        fclose(fp);
        free(arr);
        free(filename);
        free(dd);

        filename = (char *)malloc(89*sizeof(char));
        dd = (char *)malloc(100*sizeof(char));
        // char filename[89];
        strcpy(filename ,"ran");
        // char dd[999];
        sprintf(dd , "%d" , nn);
        strcat(filename , dd);
        strcat(filename ,".txt" );
        fp = fopen(filename ,"r" );
        // int x;
        arr = (int*)malloc( (nn+1)*sizeof(int));
        cnt = 0;
        while ( 1){
            fscanf(fp ,"%d" , &x);
            arr[cnt++] = x;
            if ( feof(fp))break;
        }
        
        t = clock();
        qqsort(arr, nn);
        t = clock() - t;
        double time3 = ((double)t) / CLOCKS_PER_SEC;
        fclose(fp);
        free(arr);
        free(filename);
        free(dd);

        filename = (char *)malloc(89*sizeof(char));
        dd = (char *)malloc(100*sizeof(char));
        // char filename[89];
        strcpy(filename ,"ran");
        // char dd[999];
        sprintf(dd , "%d" , nn);
        strcat(filename , dd);
        strcat(filename ,".txt" );
        fp = fopen(filename ,"r" );
        // int x;
        arr = (int*)malloc( (nn+1)*sizeof(int));
        cnt = 0;
        while ( 1){
            fscanf(fp ,"%d" , &x);
            arr[cnt++] = x;
            if ( feof(fp))break;
        }
        
        t = clock();
        insort(arr, nn);
        t = clock() - t;
        double time4 = ((double)t) / CLOCKS_PER_SEC;
        fclose(fp);
        free(arr);
        free(filename);
        free(dd);

        filename = (char *)malloc(89*sizeof(char));
        dd = (char *)malloc(100*sizeof(char));
        // char filename[89];
        strcpy(filename ,"ran");
        // char dd[999];
        sprintf(dd , "%d" , nn);
        strcat(filename , dd);
        strcat(filename ,".txt" );
        fp = fopen(filename ,"r" );
        // int x;
        arr = (int*)malloc( (nn+1)*sizeof(int));
        cnt = 0;
        while ( 1){
            fscanf(fp ,"%d" , &x);
            arr[cnt++] = x;
            if ( feof(fp))break;
        }
        
        t = clock();
        bsort(arr, nn);
        t = clock() - t;
        double time5 = ((double)t) / CLOCKS_PER_SEC;
        fclose(fp);
        free(arr);
        free(filename);
        free(dd);

        filename = (char *)malloc(89*sizeof(char));
        dd = (char *)malloc(100*sizeof(char));
        // char filename[89];
        strcpy(filename ,"ran");
        // char dd[999];
        sprintf(dd , "%d" , nn);
        strcat(filename , dd);
        strcat(filename ,".txt" );
        fp = fopen(filename ,"r" );
        // int x;
        arr = (int*)malloc( (nn+1)*sizeof(int));
        cnt = 0;
        while ( 1){
            fscanf(fp ,"%d" , &x);
            arr[cnt++] = x;
            if ( feof(fp))break;
        }
        
        t = clock();
        selsort(arr, nn);
        t = clock() - t;
        double time6 = ((double)t) / CLOCKS_PER_SEC;
        fclose(fp);
        free(arr);
        free(filename);
        free(dd);






        
        fp = fopen("sortcmp.csv" , "a");
        fprintf(fp ,"%d,%f,%f,%f,%f,%f,%f\n" ,nn, time1 ,time2 , time3, time4 , time5 , time6);
        fclose(fp);


    }
}