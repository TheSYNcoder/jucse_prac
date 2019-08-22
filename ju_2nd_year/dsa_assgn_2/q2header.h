#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#define max( x , y) ((x) > (y) ? (x) : (y))

const int MAX = 1e5 +5;
const int ROWS = 30;
const int COLS =30;


typedef struct{
    int i ;
    int j;
    int val;
}tuple;
typedef struct {    
    tuple elems[900];  
}data;
// structure for returning added sparse matrices
typedef struct{
    int val;// determining the count of the elements of data.elems
    data r;
}resu;

static int count =0;

data matrices[MAX];
int getdat()
{
    int n;
    if (!scanf("%d" , &n))
    {
        printf("Entered number should be an integer , taking 0 as the default input\n");
        return 0;
    }
    return n;
}


void display(data res)
{
    printf("NOno zero elements count :: ");
    printf("%d\n",res.elems[0].val );
    for ( int i =1; i <= res.elems[0].val ; i++)
        printf("%d ",res.elems[i].val );
    printf("\n\nThe matrix ::\n\n");
    
    for ( int i =0; i < res.elems[0].i;  i++)
    {
        for ( int j =0; j < res.elems[0].j; j++)
        {
            int flag =0;
            for ( int k =1; k <= res.elems[0].val; k++)
            {
                if (res.elems[k].i == i && res.elems[k].j == j)
                {
                    flag =1;
                    printf("%d " , res.elems[k].val);
                    break;
                }
                
            }
            if ( !flag)
                printf("0 ");
            
        
        }
        printf("\n"); 
    }
}
void getdata()
{
    
    printf("ENTER THE OF NO ROWS\n");
    int rows;
    if (!scanf("%d" , &rows))
    {
        printf("Rows should be postive integer\n");
        return;
    }
    // assert( "No of rows should be more than 0 and positive" && (rows > 0 );
    int cols;
    printf("ENTER THE OF NO COLS\n");
    if(!scanf("%d" , &cols))
    {
        printf("Cols should be postive integer\n");
        return;
    }
    // assert( "No of cols should be more than 0 and positive" && cols > 0);
    printf("ENTER THE ELEMENTS\n");
    int non_zero =0;
    data ne; 
    int c= 1;
    for ( int i =0; i < rows ; i++)
    {
        for ( int j =0; j < cols; j++)
        {
            int r = getdat();
            if (r!=0) {
            non_zero++;
            tuple nn;
            nn.i = i;
            nn.j = j;
            nn.val = r;
            ne.elems[c++] = nn;
            }
        }
    }
    tuple nn;
    nn.i = rows;
    nn.j= cols;
    nn.val = non_zero;
    ne.elems[0] = nn;
    matrices[count++] =  ne;    
}


resu add( data a , data b)
{
    data res;
    int cnt =-1;
    if ( a.elems[0].i != b.elems[0].i)
    {
        printf("The number of rows should be same\n");
        resu s;
        s.val = count;
        s.r = res;
        return s;
    }    
    if ( a.elems[0].j != b.elems[0].j)
    {
        printf("The number of cols should be same\n");
        resu s;
        s.val = count;
        s.r = res;
        return s;
    }
    if ( a.elems[0].val > 20 || b.elems[0].val > 20) //non -zero
        {
        printf("'Non zero elements should be less than or equal to  20\n'" );
        resu s;
        s.val = count;
        s.r = res;
        return s;
        }
    cnt =1;
    int non =0;
    int mark[100];
    for ( int i =0 ; i <= b.elems[i].val ; i++)
        mark[i] =0;

    for ( int i =1; i <= a.elems[0].val; i++)
    {
        int flag =0;
        for ( int j =1; j <= b.elems[0].val; j++)
        {
            if ( a.elems[i].i == b.elems[j].i && a.elems[i].j == b.elems[j].j)
                {
                    tuple dat;
                    dat.i = a.elems[i].i;
                    dat.j = a.elems[i].j;
                    dat.val = a.elems[i].val + b.elems[j].val;
                    non++;
                    res.elems[cnt++] = dat;     
                    mark[j] =1;
                    flag =1;
                    break;

                }
        }
        if (!flag)
        {
            tuple dat;
            dat.i = a.elems[i].i;
            dat.j = a.elems[i].j;
            dat.val = a.elems[i].val;
            non++;
            res.elems[cnt++] =dat;
        }

    }

    for ( int i =1 ; i <= b.elems[i].val;  i++)
    {
        if ( !mark[i])
        {
            tuple dat;
            dat.i = b.elems[i].i;
            dat.j = b.elems[i].j;
            dat.val = b.elems[i].val;
            non++;
            res.elems[cnt++] =dat;
        }
    }

    tuple nn;
    nn.i = a.elems[0].i;
    nn.j = a.elems[0].j;
    nn.val = non;
    res.elems[0]= nn;
    resu s;
    s.val = cnt;
    s.r = res;
    return s;
}


void transpose()
{
    printf("Enter a value between 0  and %d(inclusive) \n",count-1 );
    int index;
    index  =getdata();
    printf("The original matrix\n\n");
    display(matrices[index]);
    data res;
    int cnt =1;
    for ( int i =1 ; i <= matrices[index].elems[0].val ; i++)
    {
        tuple nn;
        nn.i = matrices[index].elems[i].j;
        nn.j = matrices[index].elems[i].i;
        nn.val = matrices[index].elems[i].val;
        res.elems[cnt++] = nn;

    }
    res.elems[0].i = matrices[index].elems[0].i;
    res.elems[0].j = matrices[index].elems[0].j;
    res.elems[0].val = matrices[index].elems[0].val;
    printf("The transposed matrix\n");
    display(res);

}

void multiply()
{
    printf("ENTER TWO INDEXES BETWEEN 0 and %d (inclusive)",count -1 ) ;
    int a , b;
    printf("first = ");
    a =getdat();
    printf("second = ");
    b =getdat();
    // check for dimensions

    // for index(i , j) check all ( j , k) 
    // 0 0 00 
    // 0 1 1 0
    // 0 2 2 0
    data res;
    data aa = matrices[a];
    data bb = matrices[b];
    if ( aa.elems[0].j != bb.elems[0].i)
    {
        printf("Size mismatch for multiplication\n");
        return;
    }
    if ( aa.elems[0].val > 20 || bb.elems[0].val > 20)
    {
        printf("Too many non zero elements\n");
        return;
    }
    int arr[ROWS][COLS];
    for ( int i =0 ; i < ROWS; i++)
        for ( int j =0; j < COLS ; j++)
            arr[i][j]=0;

    for ( int i = 1 ; i <= aa.elems[0].val ; i++)
    {
        int xx = aa.elems[i].i , yy = aa.elems[i].j;
        for (int j = 1; j <= bb.elems[0].val;  j++)
        {
            if ( yy == bb.elems[j].i)
            {
                arr[xx][bb.elems[j].j] += aa.elems[i].val * bb.elems[j].val;
            }
        }
    }

    printf("multiplied matrices : product ::\n");

    for  (int i =0 ; i < aa.elems[0].i ; i++)
    {
        for ( int j =0; j < bb.elems[0].j ; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }


}

resu add_mat()
{
    printf("ENTER TWO INDEXES BETWEEN 0 and %d  (inclusive)",count-1  ) ;
    int a , b;
    printf("first = ");
    a =getdat();
    printf("second = ");
    b =getdat();
    // printf("%d\n", matrices[a].len);
    // printf("%d\n", matrices[b].len);
    return add(matrices[a] , matrices[b] );   
}






