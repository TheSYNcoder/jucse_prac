#include <iostream>
using namespace std;

class Market{
	int  code;
	string name;
	int rate;
	
	public:
	void get_info(int &n , string &s , int rat){
	cout << " Enter the code three digit number";
	
	cin >> n;
	if ( n >= 100 && n < 1000){
		cout <<"Enter the name\n";
		cin >> s;
		name =s;
		code = n;
		cout << "Enter the rate\n";
		cin >> rat;
		rate =rat;
}
	else
	get_info();
}
	static int code_arr[1000];
	void change_rate( int new_rate){
	rate = new_rate;
}	
	int check_available( int item_code){
		return code_arr[item_code];
	}	
	void issue( int item_code){
	if ( !check_available( item_code) ) {cout << "Not available for issue\n";return;}
	code_arr[item_code]--;
	 
}

}


int main(){


}
