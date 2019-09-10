#include <iostream>
using namespace std;

class Application
{
	string name;
	
	int score;
	public:
	static int id;
	void receive_data( )
	{
		cout << "Enter name\n";
		cin >> name;
		cout << "Enter score\n";
		id++;
		cin >> score;
		
	}	
	void show_data()
	{
		cout << "Name: " << name << "\n";
		cout << "score :" << score << "\n";
	}
};

int Application::id =0;	
int main()
{	
	
	Application aa, bb, cc;
	aa.receive_data();
	aa.show_data();
	bb.receive_data();
	cc.receive_data();
	cout << "number of applicant s :" << Application::id; 
}	
