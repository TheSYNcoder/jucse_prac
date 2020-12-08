#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
int abs( int x){
    return x >= 0 ? x : -x;
}
int sol;
char filename[100];
int safe( int col , int row , int *q){

    // will be safe if col == 1
    if ( col == 0) return 1;

    for ( int i =0 ; i < col ; i++){
        // if in the same row
        if ( q[i] == row) return 0;

        // in a diagonal
        if ( abs(q[i] - row) == abs( i - col) ) return 0;
    }
    return 1;

}

void print( int *q , int n){
    FILE *fp;
    char* st = "nQueen";
    // char d = (char)(n + '0');
    char dd[10];
    sprintf(dd , "%d" , n);
    char* ext = ".txt";
    
    strcpy( filename , st);
    strcat(filename ,dd);
    strcat(filename , ext);
    sol++;
    printf("Writing in filename : %s\n" , filename);
    printf("Solution %d written\n" , sol);
    fp = fopen( filename, "a");



  for ( int row = 0 ; row < n ; row++){
      for ( int col = 0; col < n ; col++){
          if (q[col] == row) fprintf(fp,"%c " , '*');
          else fprintf(fp ,"%c " , '.');
      }
      fprintf(fp, "\n");
  }
  fprintf(fp,"\n\n");
  fclose(fp);
}

int  queen( int curr , int *q , int board_size){

    // solution is reached when curr == n,

    if ( curr == board_size){
        print( q , board_size);
        return 1;
    }

    

    // change state and recurse 
    int i;
    for ( i =0 ; i < board_size ; i++){
        
        if ( safe( curr , i , q)){
            int store = q[curr];
            q[curr] = i;
            if ( !queen( curr+1 , q , board_size)) // is  a solution
            q[curr] =store;
        }

    }
    return 0;

}

int main(int argc , char **argv){
    clock_t t;
    int board_size = 8;
    if ( argc > 1)
        board_size = atoi(argv[1]);
    int *q;
    q = (int *) malloc(board_size* sizeof(int));
    int i;
    for ( i =0 ; i < board_size; i++){
        q[i]  =0;
    }
    t = clock();
    queen(0 , q , board_size);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    FILE *fp;
    fp = fopen(filename , "a");
    fprintf(fp,"Time taken = %f\n seconds!!" , time_taken); 
    fprintf(fp , "Number of solutions : %d\n" , sol);
    fclose(fp);

    

    

}