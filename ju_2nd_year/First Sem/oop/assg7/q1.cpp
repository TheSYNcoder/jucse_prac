#include <iostream>
#include "student.hpp"
#include <vector>
#include <string>
using namespace std;

class StudentOperation{

    private:
    vector<Student> students;
    Student stobj;
    public:
    void add(){
        stobj.getdata();
        students.push_back(stobj);
    }

    int noOfStudents(){
        return (int)students.size();
    }

    void removeByRoll( int roll){
        students.erase(find(students.begin(), students.end(), roll));
    }

    Student highestScore(){
        int mx = 0;
        Student s;
        for ( Student ss : students){
            if ( ss.score > mx){
                mx = ss.score;
                s = ss;
            }
        }
        return s;

    }



    void display(){
        for ( Student student : students){
            cout << "Name : " << student.name <<"\n";
            cout << "Roll : " << student.roll << "\n";
            cout << "Score : " << student.score << "\n";
            cout << "\n";
        }
    }
    
    vector<Student> find_substring_in_name( string s){
    	vector<Student> st;
    	for ( Student student : students){
    		if (student.name.find_first_of(s) != string::npos){
    			st.push_back(student);
    		}
    		
    	}
    	return st;
    }
    
    vector<Student> find_not_substring_in_name( string s){
    	vector<Student> st;
    	for ( Student student : students){
    		if (student.name.find_first_of(s) == string::npos){
    			st.push_back(student);
    		}
    		
    	}
    	return st;
    }


};
int main(){
    StudentOperation s;
    s.add();
    s.add();
    s.add();
    cout << s.noOfStudents();
    s.removeByRoll(12);
    s.display();
    vector<Student>  = s.find_substring_in_name('a');
    

}

