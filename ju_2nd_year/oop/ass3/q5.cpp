#include <iostream>
using namespace std;
void f(int a)
{
	cout << "Inside f(int)" << "\n";
}
void f( float ff)
{
	cout << "Inside f(flaot) " << "\n";
}
int main()
{
		int a ;
		char b;
		float ff;
		double d;
		cout << "Enter int";
		cin >> a;
		f(a);
		cout << "Enter char";
		cin >> b;
		f(b);
		cout << "Enter float";
		cin >> ff;
		f(ff);
		cout << "Enter double";
		cin >> d;
	 f(d);
}
