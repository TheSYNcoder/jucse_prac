#include <iostream>
#include <cstring>
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;

class STRING{
    char *s;
    int size;
    int *ref_count;
    public:
    STRING():s(NULL) , size(0){
        cout <<"System default constructor called\n";
        ref_count= new int;
        *ref_count =0;
    }
    STRING( char *ss , int si){
        cout << "Default constructor called\n";
        if ( si == 0) s =NULL;
        else{
        s= new char[si];
        strcpy( s , ss);
        size = si;
        }
        if ( s!= NULL) ref_count = new int;
    }
    STRING ( const STRING &b){

        if ( s!= NULL) delete[] s;
        if ( ref_count != NULL) delete ref_count;
        size = b.size;
        s = new char[size];
        strcpy( s , b.s);
        ref_count = b.ref_count;
    }
    void operator=( const STRING &b){
        if ( s!= NULL) delete[] s;
        if ( ref_count != NULL) delete ref_count;
        size = b.size;
        s = new char[size];
        strcpy( s , b.s);
        ref_count = b.ref_count;
        *ref_count++;
    }

    void display(){
        for ( int i =0 ; i < size; i++)
            cout << s[i];
            cout << "\n";
    }

    ~STRING(){
        cout << "Destructor called \n";
        if ( *ref_count == 0)
        {
        if ( s!= NULL) delete[] s;
        size =0;
        s =NULL;}
        else{
            *ref_count--;
        }
    }
    friend STRING  operator +( STRING &, STRING &) ;
    friend bool  operator ==( STRING &, STRING &) ;
    friend bool  operator >( STRING &, STRING &) ;
    friend bool  operator <( STRING &, STRING &) ;
};
STRING  operator +( STRING &a, STRING &b){
    STRING s;
    s.size = a.size + b.size;
    s.s = new char[s.size];
    int i;
    for ( i=0 ; i < a.size; i++)
        s.s[i] = a.s[i];
    for ( int j =0; j < b.size; j++)
        s.s[i++] =b.s[j];
    return s;
}
bool operator ==( STRING &a , STRING &b){
    if ( a.size != b.size) return 0;
    for ( int i=0; i < a.size; i++)
        if ( a.s[i] != b.s[i]) return 0;
    return 1;
}
bool operator <(STRING &a , STRING &b){
    int i;
    if ( a == b) return 1;
    for (  i =0 ; i < min(a.size , b.size) ; i++){
            if ( a.s[i] < b.s[i]) return 1;
            if ( a.s[i] > b.s[i]) return 0;
    }
    if (a.size > b.size) return 0;
    return 1;
}

bool operator >(STRING &a , STRING &b){
    int i;
    if ( a == b) return 1;
    for (  i =0 ; i < min(a.size , b.size) ; i++){
            if ( a.s[i] > b.s[i]) return 1;
            if ( a.s[i] < b.s[i]) return 0;
    }
    if (a.size < b.size) return 0;
    return 1;
}


int main(){
    char *s ="wowGreat";
    STRING ss(s,strlen(s));
    ss.display(); 
   	STRING sss; // assignment overloading has to be non-static , cannot be  a friend
    sss = ss + ss;
    sss.display();
    cout << ( ss == ss) << "\n";

}
