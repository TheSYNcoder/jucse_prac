#include <stdio.h>
#include <stdlib.h>
#define max( x , y) ((x) > (y) ? (x) : (y))
#define min( x , y) ((x) < (y) ? (x) : (y))
typedef struct node{
    int x;
    int y;
    struct node *next;
}node;

int is_equal( node *a , node * b){
    return ( (a->x == b->x) && (a->y == b-> y));
}


void insert_after( node* prev , node * target){
    target-> next = prev -> next;
    prev-> next = target;
}
int is_empty( node *head){
    return (head == NULL);
}
void insert_front( node* target , node **head){
    target -> next = (*head);
    (*head) = target;
}
node * create( int x, int y){
    node *nn = ( node * )malloc( sizeof(node));
    nn -> x = x;
    nn -> y = y;
    nn -> next = NULL;
    return nn;
}
void insert_last( node *target , node **head){
    target-> next = (*head);
}
void add( node **head , node *target){
    if ( is_empty(*head)){
        insert_front(target ,head );
    }
    else{
        node *temp = *head;
        while ( temp->next!= NULL){
            temp = temp -> next;
        }
        insert_after(temp , target );
    }
}
void display(node **head ){
    node *temp = *head;
    node *check = temp;
    printf("%d %d\n" , temp-> x , temp -> y);
    temp = temp-> next;
    while (!is_equal(temp , check)){
        printf("%d %d\n", temp->x, temp->y);
        temp = temp -> next;
    }
}
node * poly(){
    printf("enter the number of points in polygon :");
    int n;
    scanf("%d", &n);
    int i;
    node *head=NULL;
    printf("Enter the x and y coordinates\n");
    node *target;
    for ( i = 0 ; i < n; i++){
        int x , y;
        getchar();
        scanf("%d %d", &x , &y);
        target = create(x ,y);
        add(&head , target);
    }
    
    insert_last(target , &head);
    return head;

}

double distance( node *a , node *b , node *c , node *d){

    double x1 = a->x;
    double y1 = a->y;
    double x2 = b->x;
    double y2 = b->y;
    double x3 = c->x;
    double y3 = c->y;
    double x4 = d->x;
    double y4 = d->y;
    double a1 = y2 -y1;
    double b1 = x2 -x1;
    double c1 = a1*x1 + b1*y1;
    double a2 = y4 - y3;
    double b2 = x4 - x3;
    double c2 = a2*x3 + b2*y3;
    double det =a1*b2 - a2*b1;
    if (det == 0)
        return 0;
    double x = (b2*c1 -b1*c2)/det;
    double y = (a1*c2 - a2*c1)/det;
    double mxx = max( x1 , x2);
    double mnx =min( x1 , x2);
    double mxy = max( y1 , y2);
    double mny =min( y1, y2);
    if ( x >= mnx && x <= mxx && y <= mxy && y >= mny) return 1;
    return 0;
}

int intersect( node** a , node **b){
    node *temp1 =*a;
    
    node *check1 =temp1;
    
    temp1 =temp1 -> next;
    while ( !is_equal(temp1 , check1)){

        node *temp2 = *b;
        node *check2 = temp2;
        temp2 =temp2 -> next;
        while ( !is_equal(temp2 , check2)){
            if ( distance(  temp1 ,temp1-> next , temp2 , temp2-> next ) )
                return 1;
            temp2 =temp2 -> next;
        }
        if ( distance( temp1 ,temp1-> next , temp2 , temp2-> next ) )
        return 1;
        temp1 =temp1 -> next;
    }
    node *temp2 = *b;
    node *check2 = temp2;
    while ( !is_equal(temp2 , check2)){
            if ( distance( temp1 ,temp1-> next , temp2 , temp2-> next ) )
                return 1;
            temp2 =temp2 -> next;
    }
    if ( distance( temp1 ,temp1-> next , temp2 , temp2-> next ) )
        return 1;


    return 0;

}



int main(){
    
    node *poly1 = poly();
    node *poly2 = poly();
    int a =intersect(&poly1 , &poly2);
    printf("%d" , a);


}