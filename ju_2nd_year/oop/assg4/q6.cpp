#include <iostream>
using namespace std;
const int MAX = 1e2+3;

class Subject{
    string name;
    string code;
    public:
    Subject( string name , string code ): name( name) , code(code) {}
};
class SubjectList{
    // to be used in student class
    Subject subjects[MAX];
    public:
    int subjectCount=0;
    void add();
};
void SubjectList::add(){
    string  name;
    cout << "enter subject name";
    cin  >> name;string code;
    cout <<" enter code :" ;
    cin >> code;
    Subject ss( name, code);
    subjects[subjectCount++]=ss;
}
class Student{
    string roll;
    string name;
    string phone;
    SubjectList sbl;
    public:
    Student( string roll , string name, string phone): roll(roll ) , name(name) , phone(phone){}
};

class StudentList{
    Student students[MAX];
    public:
     int studentCount ;
     void add();
};

void StudentList::add(){
    string  name;
    cout << "enter subject name";
    cin  >> name;string roll;
    cout <<" enter code :" ;
    cin >> code;
    cout << "Enter phone :";
    string phone; cin >> phone;
    Student ss( roll, name , phone);
    students[studentCount++]=ss;
}




int main(){
    StudentList stl;
    SubjectList sbl;
    

}