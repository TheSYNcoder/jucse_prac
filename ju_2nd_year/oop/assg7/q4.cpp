#include <iostream>
#include "student.hpp"
#include <vector>
#include <string>
#include <map>
using namespace std;

class StudentOperation{

    private:
    
    Student stobj;
    multimap<int, Student, greater<int> > mm;
    public:
    void add(){
        stobj.getdata();
        mm.insert( { stobj.score , stobj});
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

