#include <iostream>
using namespace std;
const int maxs =1e5 +5;
class Stack
{
	int *arr;
	int cur;
	public :
	void init(int )
	{
		arr =new int[maxs];
		cur =0;
		arr[cur] =0;
	}
	void push( int elem)
	{
		if ( curr >= maxs)
		{
			cout << "Overflow";
			return;
		}
		cur +=1;
		arr[cur] =elem;
	}
	void pop()
	{
		if ( cur < 0)
		{
			cout << "Underflow";
			return;
		}
		arr[cur] = -1;
		cur--;
	}
	int top()
	{
		return arr[cur];
	}
	
	

} ;
int main()
{		
	Stack s;
	s.init();
	s.push(9);
	cout << s.top();
	s.push(8);
	cout << s.top();
	s.pop();
	cout << s.top(); 
}
