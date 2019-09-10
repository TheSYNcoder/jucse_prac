#include <iostream>
#include <algorithm>
using namespace std;
#define MAX(a , b) ((a) > (b) ? (a) : (b)) 

inline int maxm( int a, int b)
{
	return max(a , b);
}
int main()
{
	cout << "Enter two numbers " << "\n";
	int a , b;
	cin >> a >> b;
	cout << "Max of two numbers =" << MAX( a , b) << "\n";
	cout << "Enter two strings\n";
	string aa ,bb;
	cin>> aa >> bb;
	cout << "Max of two strings :" << MAX(aa , bb) << "\n";
	cout << "max of two numbers using inline function " << maxm(a, b) <<"\n";   

}
