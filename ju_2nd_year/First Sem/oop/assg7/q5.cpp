#include <iostream>
#include "student.hpp"
#include <vector>
#include <string>
#include <map>
using namespace std;

class StudentOperation{

    private:
    
    Student stobj;
    map<int, Student > mm;
    public:
    void add(){
        stobj.getdata();
        mm.insert( { stobj.roll , stobj});
    }
    void display_score( int roll){
    	cout << mm[roll].score << "\n";
    }
    void display(){
    	for ( pair< int , Student > pp: mm){
    		cout << "\n";
    		cout << "name :" << pp.second.name << "\n";
    		cout << "score :" << pp.second.score << "\n";
    		cout << "roll :" << pp.second.roll << "\n";
    	}
    
    }
    

	

};
int main(){
    StudentOperation s;
    s.add();
    s.add();
    s.add();
    s.display();
   	
    
    

}

