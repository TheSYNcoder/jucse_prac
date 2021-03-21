#include <iostream>
#include <cstdlib>
using namespace std;
#define max(x , y) ( (x) > (y) ? (x) : (y)) 
class Array{
public:
	int *arr;
	int size;
	Array():arr(NULL) , size(0){}
	Array(int siz , int val =0){
		cout << "Default constructor called\n";
		arr = new int[siz];
		size =siz;
		for ( int i =0; i < siz; i++)
			arr[i] =val;
	}
	int operator[]( int index)
	{
		if (index >= size) return 0;
		return arr[index];
	}
	Array(const Array &b){
		cout << "Copy constructor called \n";
		int t = b.size;
		size = t;
		if ( arr!= NULL){cout << "Inside copy dees, check if des is called\n "; delete[] arr;}
		arr = new int[t];
		for ( int i =0; i < t; i++)
			arr[i] = b.arr[i];
	
	}
	Array ( int *p , int siz){
		cout <<  "Parameterized constructor called \n"; 
		if ( arr!= NULL) delete[] arr;
		arr = new int[siz];
		size = siz;
		for ( int i =0; i < siz; i++)
			arr[i] = p[i];
	}
	
	
	Array operator+( const Array  a)
	{
		cout << " Inside only  + operator\n";

		int siz = max( size , a.size);
		Array aa(siz);// = new Array( siz );
		int i;
		aa.size = siz;
		for ( i =0; i < min(size , a.size) ; i++)
			aa.arr[i] =  arr[i] + a.arr[i];
		for ( ;i < siz;i++)
		{
			if ( a.size >= i)
			aa.arr[i] = a.arr[i];
			else
			aa.arr[i] = arr[i];
		
		} 
		return aa;
		
	
	}
	friend Array operator* (Array &b, int x){
	Array a(b.size);
	for ( int i =0; i < b.size;  i++)
		a.arr[i] = b.arr[i]*x;
	return a;
}
	friend Array operator*(int x ,Array &b){
		return (b * x);
} 
	void display(){
		cout << size << "\n";
		for ( int i =0; i < size; i++)
			cout << arr[i] << " ";
			cout <<"\n";
	}
	void operator =( const Array &b){
        cout << "ASSIGNMENT OVERLOADING CALLED\n";
        if ( arr != NULL) delete[] arr;
    arr= NULL;
    size = b.size;
    arr = new int[size];
    for ( int i =0 ; i < size; i++)
		arr[i] = b.arr[i];
    }
	
	~Array(){
		cout << "Destructor called" << "\n";
		cout << size << "\n";
		if ( arr != NULL)
			delete[] arr;
		arr =NULL;
	}



};
int main(){
	int arr[100];
	//arr = new int[100];
	for ( int i =0; i < 100; i++)
		arr[i] = i;
	cout << "Array obj created \n";
	Array aa(arr , 100);
	aa.display();
	// cout << "Another array object created\n";
	// Array b(100);
	// b = aa; // Byte wise copying
	// b.display();   Byte wise copying does not allocate space hence destructor crashes.
	Array c=aa + aa; // copy constructor not called
	Array d(5*c);
	d.display();
	c.display();			
}
