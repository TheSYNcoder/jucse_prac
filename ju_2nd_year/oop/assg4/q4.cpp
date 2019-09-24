#include <iostream>
#include <cstring>
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;

class STRING{
    char *s;
    int size;
    public:
    STRING():s(NULL) , size(0){
        cout <<"System default constructor called\n";
    }
    STRING( char *ss , int si){
        cout << "Default constructor called\n";
        s= new char[si];
        strcpy( s , ss);
        size = si;
    }
    STRING ( const STRING &b){

        if ( s!= NULL) delete[] s;
        int size = b.size;
        s = new char[size];
        strcpy( s , b.s);
    }

    void display(){
        for ( int i =0 ; i < size; i++)
            cout << s[i];
            cout << "\n";
    }

    ~STRING(){
        cout << "Destructor called \n";
        if ( s!= NULL) delete[] s;
        size =0;
        s =NULL;
    }
    friend STRING  operator +( STRING &, STRING &) ;
    friend bool  operator ==( STRING &, STRING &) ;
    friend bool  operator >( STRING &, STRING &) ;
    friend bool  operator <( STRING &, STRING &) ;


    void operator =( const STRING &b){
        cout << "ASSIGNMENT OVERLOADING CALLED\n";
        if ( s != NULL) delete[] s;
    s= NULL;
    size = b.size;
    s = new char[size];
    strcpy(s , b.s);
    }



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