#include <bits/stdc++.h>

using namespace std;
class Student
{
	int roll;
	string name;
	string course;
	string date;
	int marks[5];
	static int number;
	
	void admit()
	{
		cout << "Enter roll";
		cin >> roll;
		cout << "Enter name";
		cin >> name;
		cout << "Enter course";
		cin  >> course;
		cout << "Enter date";
		cin >> date;
	}
	
	void receive_marks()
	{
		cout << "Enter marks in 5 subjects";
		for ( int i =0; i < 5; i++)
			cin >> marks[i];
			
	}
	void display()
	{
		cout << "Name :" << name << "\n";
		cout << "roll :" << roll << "\n";
		cout << "course :" << course << "\n";
		cout << "date :" << date << "\n";
		for ( int i =0; i < 5; i++)
		{
			cout << "Marks " << i+1 <<  " " << marks[i] << "\n";
		}
	
	}

}
int Student::number= 0;
int main()
{
	

}
