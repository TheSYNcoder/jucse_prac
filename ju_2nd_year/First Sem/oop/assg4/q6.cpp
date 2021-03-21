#include <iostream>
using namespace std;
const int MAX = 1e2+3;
class StudentList;
class SubjectList;
class Map{
	int sub_code;
	int stu_code;
	StudentList stl;
	SubjectList sul;
	public:
	Map arr[1000];
	int count =0;
	Map( int su , int st){
		sub_code= su;
		stu_code = st;
	}
	
	void add(int su , int st)
	{
		Map m(su , st);
		arr[count++] = m;	
	}
	
	void queryst( int su)
	{
		cout << "Printing all students for subject code :" << su << "\n"; 
		for ( int i =0; i < count ; i++){
			if ( arr[i].sub_code == su){
				stl.dis(arr[i].stu_code); // to make 
			}
		}
	}  
	void querysu( int st)
	{
		cout << "Printing all students for student roll :" << st << "\n"; 
		for ( int i =0; i < count ; i++){
			if ( arr[i].stu_code == st){
				sul.dis(arr[i].sub_code); // to make 
			}
		}
	}
}
class Subject{
    string name;
    string code;
    public:
    Subject( string name , string code ): name( name) , code(code) {}
    void display();
};
void Subject::display(){
	cout << string( 40 , '-') << "\n";
	cout << "Details of subject\n";
	cout << "name : " << name << "\n";
	cout << "code : " << code << "\n";
	cout << string( 40 , '-') << "\n";
}
class SubjectList{
    // to be used in student class
    Subject subjects[MAX];
    public:
    int subjectCount=0;
    void add();
    void dis(int);
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
void SubjectList::dis(int code){
	for ( int i =0; i < subjectCount; i++){
		if ( subjects[i].code == code )
		{
			subjects[i].display();
		}
	}
}
class Student{
    string roll;
    string name;
    string phone;
    public:
    Student( string roll , string name, string phone): roll(roll ) , name(name) , phone(phone){}
    void display();
};
void Student::display(){
	cout << string( 40 , '-') << "\n";
	cout << "Details of student\n";
	cout << "name : " << name << "\n";
	cout << "roll : " << roll << "\n";
	cout << "phone : " << phone << "\n";
	cout << string( 40 , '-') << "\n";
}
class StudentList{
    Student students[MAX];
    public:
     int studentCount ;
     void add();
     void dis();
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

void StudentList::dis(int code){
	for ( int i =0; i < studentCount; i++){
		if ( students[i].roll == code )
		{
			students[i].display();
		}
	}
}
int main(){
    StudentList stl;
    SubjectList sbl;
    

}
