#include <iostream>
using namespace std;

class Time
{	
	int hour;
	int minutes;
	int seconds;
	public:
	void display_24()
	{
		cout << "Time : " << hour << ":" << minutes << ":" << seconds << "\n";
	}
	void display_AM_PM()
	{
		int h;
		string s ="AM";
		if ( hour > 12)
		{
			h = hour -12;s ="PM";
			}
		cout << "Time : " << h << ":" << minutes << ":" << seconds << " " << s << "\n";
	}
	void get_time_24()
	{
		cout << "Enter hours ";
		cin >> hour;
		cout << "Enter mins ";
		cin >> minutes;
		cout << "Enter seconds ";
		cin >> seconds;
		
		
	}
	void get_time_AM_PM()
	{
		cout << "Enter hours ";
		cin >> hour;
		cout << "Enter mins ";
		cin >> minutes;
		cout << "Enter seconds ";
		cin >> seconds;
		cout << "Enter AM/PM";
		string s;
		cin >> s;
		if ( s == "PM")
		hour+=12;
		
		
	}
	void add( int minute)
	{
		int hr = minute /60;
		hour+=hr;
		minute -= hr*60;
		minutes += minute;
		if ( minutes >= 60)
		{
			hour += minutes/60;
			minutes -= minutes/60 * 60;
		}
		if ( hour > 24) 
			hour = 0;
	
	}
};

int main()
{
	Time t;
	cout << "In 24 hour format\n";
	t.get_time_24();
	cout << "adding 50 minutes\n";
	t.display_24();
	t.add(50);
	t.display_24();
	cout << "In AM/Pm format\n";
	t.get_time_AM_PM();
	t.add(100);
	t.display_AM_PM();
	
	

}
