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
const int Max = 1e2;
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

    void issue(string id){
        for  (int i =0; i < cnt; i++){
            if ( books[i].get_book().get_id() == id){
                books[i].dec();
                return;
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

    virtual int return_max_issued(){
        return 0;
    };
    virtual ~Member() = default;

};

class Student : public Member{
    const int max_issued =2;
    public:
    // virtual void issue();
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
    // virtual void issue();
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
public:
    Member *members[Max];
    int cnt;
    MemberList(){
        for ( int i =0; i < Max; i++)
            members[i] = new Member();
        cnt  =0;
    }
    
    
    
    int verify( string id){
        for ( int i =0; i < cnt; i++){
            if ( members[i]->get_id() == id)
            return 1;
        }
        return 0;
    }
    void add( string id , string type){
        if ( !verify(id) ) {
            members[cnt]-> get_info();
           if ( type == "Student"){
                
                members[cnt++] = new Student();
            }
            else
            {
                members[cnt++]= new Faculty();
            }
        }
 
    }

    void display(){
        for ( int i =0 ; i < cnt; i++){
            cout << (members[i]->return_max_issued()) << "\n";
        }
    }


};


class Transaction{
    string member_id;
    string book_id;
    char status;
    public:
    Transaction(){
        status ='.';
    }
    public:
    void get_info(){
        cout << "Enter member id :";
        cin >> member_id;
        cout << "Enter book id ";
        cin >> book_id;
    }



};

class Issue : public Transaction{

    public:
    void get_info (){
        Transaction::get_info();
    }
    int verify(string id);

};

class Return : public Transaction{
    int sn;
    public:
    void get_info(){
        Transaction::get_info();
        cout << "Enter serial number";
        cin >> sn;
    }
    

};

class TransactionList{
    int cnt;
    Transaction trans[Max];
    public:
    TransactionList(){
        cnt =0;
        for ( int i =0; i < Max ; i++)
            trans[i]= Transaction();
    }
    int verifyMember(MemberList &m , string id){
        return m.verify(id);
    }

    void issue( MemberList &m , string mem_id , BookList &b , string book_id){
        if ( !m.verify(mem_id)) return;
        if ( !b.available_for_issue( book_id)) return ;
        b.issue(book_id);
    }

    void Return(){

    }
    
    



};


class Library{

    public:
        TransactionList tl;
        MemberList ml;
        BookList bl;

    void perform(){
        while( true){
            cout << "enter book id";
            string id;
            cin >> id;
            bl.add_book(id);
            cout << "Enter n to stop";
            char c;
            cin >> c;
            if ( c == 'n')
                break;
        }

        while(true){
            cout << "enter member id";
            string id;
            cin >> id;
            cout << "enter type"; 
            string type;
            cin >> type;
            ml.add(id, type);
            cout << "Enter n to stop";
            char c;
            cin >> c;
            if (c == 'n')
                break;
        }

        // Transactions
        while( true){
            cout << "Enter R to return and I to issue";
            char c;
            cin >> c;
            if ( c == 'R'){
                //Return
            }
            else{
                //Issue
            }
        }
    }


};



int main(){
    MemberList ml;
    ml.add( "123" , "Student");
    // ml.add("124", "Stud");
    // ml.add("1223", "St32ent");
    // ml.add("1213" ,"Faculty");
    // ml.display();
    

}