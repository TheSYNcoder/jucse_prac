#include <iostream>
using namespace std;
class Complex
{
public:
	int r;
	int img;
	Complex(){
		r =0;
		img =0;
	}
	friend istream & operator>>(istream & i , Complex &c)
	{
		cout << "Enter the real part\n";
		i >> c.r;
		cout << "Enter the imaginary part\n";
		i >> c.img; 
		return i;
	}
	void display()
	{
		cout << r << " + " << img << "j\n"; 
	}
	Complex  operator+( Complex c)
	{
		Complex cc;
		cc.r = r + c.r;
		cc.img = img + c.img;
		return cc;
	}
	Complex  operator-( Complex c)
	{
		Complex cc;
		cc.r = r - c.r;
		cc.img = img - c.img;
		return cc;
	}
	friend ostream & operator<<( ostream & o , Complex &c){
		o << c.r << " + " << c.img << "j\n"; 
		return o;
	}

};

int main()
{
	Complex c;
	cout << "First complex number\n";
	cin >> c;
	cout << "Second complex number\n";
	Complex d;
	cin >> d;
	cout << "First + Second\n";
	Complex e= c+d;
	cout << e;
	Complex f = c -d;
	cout << "First - Second\n";
	cout << f;
	// cout << (c + d);
}

