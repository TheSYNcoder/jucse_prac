#include <iostream>
using namespace std;
int &  max( int &a , int &b)
{
	return ( a > b ? a : b);
}
#define pp(x) cout << #x << " =" << x << "\n";
void print(int a , int b , int x)
{
	pp(a);
	pp(b);
	pp(x);
}
int main()
{
	cout << "Enter two numbers\n";
	int a, b;
	cin  >> a >> b;
	int x= max( a , b);
	cout << "Max of " << a << " and " << b << " is " << x <<"\n";
	cout << "On modifying the value setting to , a+=2 , b+=2\n";
	a+=2;
	b+=2;
	//x =100;
	print(a , b , x);
	a-=2;
	b-=2;
	cout << "On taking reference\n";
	int &xx = max(a , b);
	cout << "Max of " << a << " and " << b << " is " << xx <<"\n";
	cout << "On modifying the value setting to  ";
	a+=2;
	b+=2;
	print(a , b, xx);
	
	
}
