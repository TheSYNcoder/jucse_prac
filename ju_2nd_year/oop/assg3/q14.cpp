#include<iostream>
using namespace std;

class Balance{
	string acc_no;
	int balance;
	string  date;
	friend void operate( Transaction & , Balance &b);

};
class BalanceList{
	
}

class Transaction{
	string acc_no;
	int balance;
	string date;
	friend void operate( Transaction &,  Balance &);
};

void operate( Transaction tr & , Balance &b){
	cout << "Enter w for withdrawal or d for deposit :";
	char ch ;
	cin >> ch;
	if ( ch == 'w' || ch == 'W')
	{
		//withdraw

	}
	else
	{
		//Deposit
	}
	
}


int main()
{


}
