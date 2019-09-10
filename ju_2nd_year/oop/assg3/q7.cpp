#include <iostream>
using namespace std;
#define print(x) cout << #x << " = " << x << "\n";
struct student{
	int roll;
	int score;
	void getdata( )
	{
		cout << "Enter attributes\n";
		cin >> roll >> score;
	} 
	void showdata()
	{
		print(roll);
		print(score);
	}

};
void modify( student &s)
{	
	cout << "Modified roll =";
	cin >> s.roll;
	cout << "Modified score =";
	cin >> s.score; 
}
void pprint(student s)
{
	print(s.roll);
	print(s.score);
}
int main()
{
	student s;
	s.getdata();
	s.showdata();
	cout << "Modifying ...\n";
	modify(s);
	pprint(s);
	

}
