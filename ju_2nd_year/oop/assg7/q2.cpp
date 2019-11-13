#include <iostream>
#include "student.hpp"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class StudentOperation{

    private:
    vector<Student> students;
    Student stobj;
    map<int, Student> st;
    public:
    void add(){
        stobj.getdata();
        students.push_back(stobj);
        st[stobj.roll] = stobj;
    }

    int noOfStudents(){
        return (int)students.size();
    }
    
    

    void removeByRoll( int roll){
        st.erase(st.find(roll));
    }
    bool cm(Student s1 ,Student s2){
    	return (s1.score > s2.score);
    
    }
    
   
    
    void sortAndPrint(){
    		vector<Student> copy;
   			for ( pair<int,Student> ss : st){
   				copy.push_back(ss.second);
   			}
   			
   			for ( int i =0; i < copy.size();  i++){
   				for ( int j = i ; j < copy.size() ; j++){
   					if ( copy[i].score < copy[j].score){
   						Student ss = copy[i];
   						copy[i] = copy[j];
   						copy[j] = ss;
   					}
   				}
   			}
   			
   			for ( Student student : copy){
            cout << "Name : " << student.name <<"\n";
            cout << "Roll : " << student.roll << "\n";
            cout << "Score : " << student.score << "\n";
            cout << "\n";
        } 	
    
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
    
    
    void merge( StudentOperation &s){
    	cout << "merging\n";
    	for ( Student ss :s.students){
    		students.push_back(ss);
    	}
    	cout << noOfStudents() << "\n";
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
    s.sortAndPrint();
    StudentOperation a;
    a.add();
    s.merge(a);
    

}

