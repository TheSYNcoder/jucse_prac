#include <iostream>
using namespace std;
class Book{

public:
    Book() : quantity(0) {}

public:
    string id;
    string sN;
    string title;
    string author;
    string publisher;
    string price;
    int quantity;
    void get_data(){
        cout << "Enter book id :";
        cin >> id;
        cout << "Enter book serial number :";
        cin >> sN;
        cout << "Enter book title :";
        cin >> title;
        cout << "Enter book author :";
        cin >> author;
        cout << "Enter book publisher :";
        cin >> publisher;
        cout << "Enter book price :";
        cin >> price;
        cout << "Enter book  quantity :";
        cin >> quantity;
    }
};
Book books[1000];
class BookList:public Book{
    public:
        static int count;
        void get_data()
        {
            books[count++].get_data();
    }
    bool validate(string id , string sn){
        cout << id <<  "  " << sn << " " << count;
        for ( int i =0; i < count; i++){
            cout << books[i].id << " " << books[i].sN << "\n";
            if ( books[i].id == id && books[i].sN == sn)
            {
                cout << "Book details ok " << "\n";
                return true;
            }
        }
        return false;
    }

    int safeIssue(string id, string sn){
        for (int i = 0; i < count; i++)
        {
            if (books[i].id == id && books[i].sN == sn)
                return (books[i].quantity >= 1);
        }
        
    }

    void issue(string id , string sn)
    {
        for (int i = 0; i < count; i++)
        {
            if (books[i].id == id && books[i].sN == sn)
            {
                books[i].quantity -= 1;
                return;
            }
        }
    }
};

int BookList::count =0;

class Member{
    public:
    string id;
    string name;
    string email;
    string address;
    int issued;
    Member():issued(0)
    {    }
    void get_data(){
        cout << "Enter id :";
        cin >> id;
        cout << "Enter name";
        getchar();
        getline(cin  , name);
        cout << "Enter email";
        cin >> email;
        cout << "Enter address";
        getchar();
        getline( cin , address);
    }

    void show_data(){
        cout << "Id :" << id << "\n";
        cout << "name :" << name << "\n";
        cout << "email :" << email << "\n";
        cout << "address : " << address << "\n"; 
    }
};

class Faculty: public Member{
	

};
// user submits memberid and book id and serial no to b = e validated
Member members[1000];
class MemberList : public Member{
public:
    
    static int count;

    void get_data(){
        members[count++].get_data();
    }
    bool validate(string id){
        for (int i =0; i < count ; i++){
            if ( members[i].id == id)
                return true;
        }
        return false;
    }
    int code(string id){
        for (int i = 0; i < count; i++)
        {
            if (members[i].id == id)
                return members[i].code;
        }
        
    }
    int safeIssue( string id){
        for ( int i =0; i < count;  i++){
            if ( members[i].id == id){
                if ( members[i].code == 0)
                return (members[i].issued + 1 <= 2);
                else
                return (members[i].issued +1 <=10);
            }
        }
    }
    void issue( string id){
        for ( int i =0; i < count;  i++){
            if ( members[i].id == id){
            members[i].issued+=1;
            return ;
            }
            }

    }

    
    
};

int MemberList::count =0;



class Transaction: public MemberList , public BookList{

public:
    string date;
    string id;
    string book_id;
    string sn;
    bool returned;
    Transaction():returned(true){}

    void get_data(){
        cout << "Enter date :";
        getchar();
        getline(cin , date);
        cout << "Enter id :";
        cin >> id;
        cout << "Enter book id :";
        cin >> book_id;
        cout << "Enter book serial :";
        cin >> sn;

    }
    bool validate(){
        if ( BookList::validate(book_id, sn) && MemberList::validate(id))
            return true;
        return false;
    }
};
Transaction records[1000];
class TranscationList : public Transaction{
    public:
    static int no;
    void issue(){
        Transaction ob;
        ob.get_data();
        if ( !ob.validate()){
            cout << "Details are invalid\n";
            return;
        }
        else{
            if ( BookList::safeIssue(ob.book_id , ob.sn) && MemberList::safeIssue(ob.id)){
                BookList::issue(ob.book_id , ob.sn);
                MemberList::issue(ob.id);
                ob.returned =false;
                records[no++]=ob;
            }


        }
    }

    void Return(){
        Transaction ob;
        ob.get_data();
        if (!ob.validate())
        {
            cout << "Details are invalid\n";
            return;
        }
        else{
            return;
        }
    }
    void show(){
        for ( int i =0 ; i < no ; i++){
            cout << "\n\nDEtails\n";
            cout << "transcation date :" << records[i].date << "\n";
            cout << "member-id :" << records[i].id << "\n";
            cout << "sn -id :" << records[i].sn << "\n";
            cout << "returned : " << records[i].returned << "\n";
            cout << string(40 , '-') << "\n";  
        }
    }
};

int TranscationList::no =0;

int main(){

    cout << "enter books";
    BookList b;
    while ( true){
        b.get_data();
        cout << "Continue Y/n";
        char c;
        cin >> c;
        if ( c == 'N' || c == 'n')
            break;

    }
    MemberList m;
    while (true)
    {
        m.get_data();
        cout << "Continue Y/n";
        char c;
        cin >> c;
        if (c == 'N' || c == 'n')
            break;
    }
    
    TranscationList tl;
    tl.issue();
    tl.issue();
    tl.show();



}

