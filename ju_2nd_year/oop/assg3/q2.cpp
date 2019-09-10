#include <iostream>
using namespace std;
#define print(x) cout << #x << "=" << x << "\n";
void swap(int &a, int &b)
{
	a = a+ b;
	b =a -b;
	a = a -b;
}
int main()
{	
	int first , second;
	cout << "Enter two numbers";
	cin >>  first >> second;
	swap( first, second);
	print(first);
	print(second);
}
