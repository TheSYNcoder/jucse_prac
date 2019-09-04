#include <iostream>
using namespace std;
void  f(int a, int c)
{
	cout << "Inside f( int , int)\n";
} 
void  f(int a, char c)
{
	cout << "Inside f( int , char)\n";
} 
int main()
{
	int a;
	char c;
	float ff;
	cout << "Enter\n";
	cin >> a >> c >> ff;
	f(a , c);
	f(c ,c);
	//f(ff , ff);
	
	
}
