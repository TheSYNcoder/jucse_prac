#include <iostream>
using namespace std;
#define max(x , y) ( (x) > (y) ? (x) : (y)) 
class Array{
public:
	int *arr;
	int size;
	Array(int siz , int val =0){
		arr = new int[siz];
		size =siz;
		for ( int i =0; i < siz; i++)
			arr[i] =val;
	}
	int operator[]( int index)
	{
		if (index > size) return 0;
		return arr[index];
	}
	Array( Array &b){
		int t = b.size;
		size = t;
		if ( arr!= NULL) delete arr;
		arr = new int[t];
		for ( int i =0; i < t; i++)
			arr[i] = b.arr[i];
	
	}
	Array ( int *p , int siz){
		//if ( arr!= NULL) delete arr;
		arr = new int[siz];
		size = siz;
		for ( int i =0; i < siz; i++)
			arr[i] = p[i];
	}
	
	
	Array operator+( Array  &a)
	{
		int siz = max( size , a.size);
		Array aa( siz );
		int i;
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
	
	
	Array operator=( Array  &a)
	{
		int siz = a.size;
		Array aa( siz );
		
		for ( int i =0; i < siz ; i++)
			aa.arr[i] = a.arr[i];
		return aa;
	}
	void display(){
		cout << size << "\n";
		for ( int i =0; i < size; i++)
			cout << arr[i] << " ";
			cout <<"\n";
	}
	/*
	~Array(){
		cout << "Yo" << "\n";
		delete arr;
	}
*/


};
int main(){
	int arr[100];
	//arr = new int[100];
	for ( int i =0; i < 100; i++)
		arr[i] = i;
	Array aa(arr , 100);
	aa.display();
	//Array b(100);
	Array c = aa + aa;
	c.display();		
}
