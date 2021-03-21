#include <iostream>
using namespace std;

class Item{
public:
	int  code;
	string name;
	int rate;
	
	
	void get_info(){
	cout << " Enter the code three digit number";
	int n;
	cin >> n;
	if ( n >= 100 && n < 1000){
		cout <<"Enter the name\n";
		cin >> name;
		code = n;
		cout << "Enter the rate\n";
		cin >> rate;
}
	else
	get_info();
}
	static int code_arr[1000];
	void change_rate( int new_rate){
	rate = new_rate;
}	
	static int check_available( int item_code){
		return code_arr[item_code];
	}	
	void issue( int item_code){
	if ( !check_available( item_code) ) {cout << "Not available for issue\n";return;}
	code_arr[item_code]--;
	 
}

	void display()
	{
		cout << "Item code : " << code << "\n";
		cout << "Item name : " << name << "\n";
		cout << "Item rate : " << rate << "\n";
	
	}

};
int Item::code_arr[1000] ={0};

class ItemList{
public:
	Item list[1000];
	static int count;
	void getinfo(Item &item)
	{
		item.get_info();
	}
	void add_item(){
		getinfo(list[count]);
		if ( !Item::check_available(list[count].code) )
		{
			
			Item::code_arr[list[count].code]++;
			count++;
		} 
	}
	void display()
	{
		cout << "Enter the item code";
		int code;
		cin >> code;
		for ( int i =0; i < count; i++)
		{
			if ( list[i].code == code)
			{
				list[i].display();
				return;
			}
		
		}
		cout << "Item not available\n";
	}	

};
int ItemList::count =0;
int main(){
	ItemList lis;
	lis.add_item();
	lis.add_item();
	lis.display();
	
	

}
