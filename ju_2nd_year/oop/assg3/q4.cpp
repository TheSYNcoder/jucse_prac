#include <iostream>
using namespace std;
double cal_tax( int income  , int rate =10)
{
	double tax;
	tax = income * 1.0 * rate / 100.0;
	return tax; 
}
int main()
{
		cout << "Enter the income and tax rate " << "\n";
		int income , tax_rate;
		cin >> income >> tax_rate;
		cout << "Taking user defined tax_rate\n";
		cout << "Tax =" << cal_tax( income,  tax_rate) <<"\n";
		cout << "Taking default tax_rate\n";
		cout << "Tax = " << cal_tax( income) << "\n";
		

}
