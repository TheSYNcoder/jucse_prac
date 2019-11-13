#include <iostream>
using namespace std;
class Student{
    public:
    string name;
    int roll;
    int score;
    
    void getdata(){
        cout << "Enter name";
        cin >> name;
        cout << "Enter roll";
        cin >> roll;
        cout << "Enter score";
        cin >> score;
    }

    bool operator==( int roll){
        return this-> roll == roll;
    }


};