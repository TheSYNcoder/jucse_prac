#include <iostream>
using namespace std;
class Book{
    string id;
    string title;
    string author;
    string price;
    public:
    void get_info(){
        cout << "Enter id :";
        cin >> id;
        cout << "Enter title :";
        cin >> title;
        cout << "Enter  author :";
        cin >> author;
        cout << "Enter price :";
        cin >> price;
    }
    string get_id(){
        return id;
    }
};
const int Max = 1e5;
class BookMap{
    Book b;
    int available;
    int total;
    
    public:
    BookMap( ){  
        available =0;
        total =0;
    }
    void add(){
        available++;
        total++;
    }
    void get_info(){
        b.get_info();
        available =1;
        total =1;
    }
    Book get_book(){
        return b;
    }
    int av(){
        return available;
    }
    void dec(){
        available--;
    }
};
class BookList{
    // add a book
    // check a book available for issue given id
    // chek a book is there acc to some serial no and id
    BookMap books[Max];
    int cnt;
    public:
    BookList():cnt(0){}
    void add_book( string id){
        int flag =0;
        for ( int i =0 ; i < cnt; i++){
            if ( books[i].get_book().get_id() == id)
                {
                    books[i].add();
                    flag =1;
                    break;
                }
        }
        if (!flag){
            BookMap b;
            b.get_info();
            books[cnt++] = b;
        }
    }

    int available_for_issue( string id){
        for ( int i =0 ; i < cnt; i++){
            if ( books[i].get_book().get_id() == id){
                return (books[i].av() > 0);
            }
        }
        return 0;
        
    }

    int issue(string id){
        for  (int i =0; i < cnt; i++){
            if ( books[i].get_book().get_id() == id){
                books[i].dec();
            }
        }
    }



};


class Member{
    string id;
    string name;
    string email;

    public:
    Member(){}
    virtual void get_info(){
        cout << "ENter id :";
        cin >> id;
        cout << "enter name :";
        cin  >> name;
        cout << "Enter email :";
        cin >> email;
    }

    string get_id(){
        return id;
    }

    virtual int return_max_issued();
    virtual ~Member() = default;

};

class Student : public Member{
    const int max_issued =2;
    public:
    virtual void issue();
    virtual int return_max_issued(){
        return max_issued;
    }
    virtual void get_info(){
        Member::get_info();
    }

};

class Faculty : public Member{
    const int max_issued =10;
    public:
    virtual void issue();
    virtual int return_max_issued()
    {
        return max_issued;
    }
    virtual void get_info()
    {
        Member::get_info();
    }
};


class MemberList{
    Member *members[Max];
    int cnt;
    public:
    
    int verify( string id){
        for ( int i =0; i < cnt; i++){
            if ( members[i]-> get_id() == id)
            return 1;
        }
        return 0;
    }
    void add( string id , string type){
        if ( !verify(id) ) {
            Member *b;
            
            if ( type == "Student"){
                b = new Student();
            }
            else
                b = new Faculty();
            b->get_info();
            members[cnt++] = b;
        }
 
    }

    void display(){
        for ( int i =0 ; i < cnt; i++){
            cout << (members[i]-> return_max_issued()) << "\n";
        }
    }


};


class Transaction{
    string member_id;
    string book_id;
    string date;

    public:
    void get_info();


};

class Issue : public Transaction{

    public:


};

class Return : public Transaction{

};

class TransactionList{


};



int main(){
    MemberList ml;
    ml.add( "123" , "Student");
    ml.add("124", "Stud");
    ml.add("1223", "St32ent");
    ml.add("1213" ,"Faculty");
    ml.display();

}