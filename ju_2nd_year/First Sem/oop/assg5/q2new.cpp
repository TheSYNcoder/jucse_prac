#include <iostream>
using namespace std;
class Book{
    string id;
    string title;
    string author;
    string price;
    public:
    void get_info(string Id){
        id = Id;
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
const int Max = 1e4;
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
    void get_info(string id){
        b.get_info(id);
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
    void inc(){
        available++;
    }
};
class BookList{
    // add a book
    // check a book available for issue given id
    // check a book is there acc to some serial no and id
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
            b.get_info(id);
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
    void ret(string id)
    {
        for (int i = 0; i < cnt; i++)
        {
            if (books[i].get_book().get_id() == id)
            {
                books[i].inc();
                return;
            }
        }
    }
};


class Member{
    string id;
    string name;
    string email;
    int current;

    public:
    Member():current(0){}
    virtual void get_info(string Id){
        id = Id;
        cout << "enter name :";
        cin  >> name;
        cout << "Enter email :";
        cin >> email;
    }

    string get_id(){
        return id;
    }

    int get_curr(){
        return current;
    }

    void issue(){
        current++;
    }
    void ret(){
        current--;
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
    virtual void get_info(string id){
        Member::get_info(id);
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
    virtual void get_info(string id)
    {
        Member::get_info(id);
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
            
           if ( type == "Student"){
                
                members[cnt] = new Student();
                cout << "New student registered\n";
            }
            else
            {
                members[cnt]= new Faculty();
                cout << "new faulty registered\n";
            }
            members[cnt]->get_info(id);
            cnt++;
        }
        else{
            cout << "Member present with this id\n";
        }
 
    }

    void display(){
        for ( int i =0 ; i < cnt; i++){
            cout << (members[i]->return_max_issued()) << "\n";
        }
    }
    int return_maxIssued(string id){
        for (int i = 0; i < cnt; i++)
        {
            if (members[i]->get_id() == id)
                return members[i]->return_max_issued();
        }
        return 0;
    }

    int return_curr(string id)
    {
        for (int i = 0; i < cnt; i++)
        {
            if (members[i]->get_id() == id)
                return members[i]->get_curr();
        }
        return 0;
    }
    void issue(string id){
        for (int i = 0; i < cnt; i++)
        {
            if (members[i]->get_id() == id)
            {
                members[i]->issue();
                return;
            }
        }
        
    }

    void ret(string id){
        for (int i = 0; i < cnt; i++)
        {
            if (members[i]->get_id() == id)
            {
                members[i]->ret();
                return;
            }
        }
        
    }
};


class Transaction{
    string member_id;
    string book_id;
    char status;// I for issue , R for return
    int sn;
    public:
    Transaction(){
        status ='.';
        sn =0;
    }
    public:
    void get_info(){
        cout << "Enter member id :";
        cin >> member_id;
        cout << "Enter book id ";
        cin >> book_id;
    }
    void set_info( string mid, string bid){
        member_id = mid;
        book_id = bid;
    }
    string get_bookId(){
        return book_id;
    }
    string get_memId(){
        return member_id;
    }
    char get_status(){
        return status;
    }
    int get_serial_no(){
        return sn;
    }
    void change_status(char c){
        status = c;
    }
    void set_serial( int n){
        sn =n;
    }



};

class Issue : public Transaction{
    

    public:
    
    void get_info (){
        Transaction::get_info();
    }

    void set_info(string mid, string bid){
            Transaction::set_info(mid, bid);
    }
    void change_status(char c){
        Transaction::change_status(c);
    }
    void set_serial(int n){
        Transaction::set_serial(n);
    }
    
    

};

class Return : public Transaction{
    public:
    void get_info(){
        Transaction::get_info();
    }
    void set_info(string mid, string bid)
    {
        Transaction::set_info(mid, bid);
    }
    void change_status(char c)
    {
        Transaction::change_status(c);
    }
    void set_serial(int n)
    {
        Transaction::set_serial(n);
    }
};

class TransactionList{
    int cnt;
    Transaction trans[Max];
    public:
    TransactionList(){
        cnt =0;
    }
    int verifyMember(MemberList &m , string id){
        return m.verify(id);
    }

    void issue( MemberList &m , string mem_id , BookList &b , string book_id){
        if ( !m.verify(mem_id)){cout <<"Wrong Member id\n"; return;}
        if ( !b.available_for_issue( book_id)){ cout << "Wrong book id or not available\n";return ;}
        b.issue(book_id);
        if ( m.return_curr(mem_id) + 1 <= m.return_maxIssued(mem_id)){
            m.issue(mem_id);
        }
        else{
            cout  <<"Issue quota filled\n";
            return;
        }
        trans[cnt] = Issue();
        trans[cnt].set_info(mem_id , book_id);
        trans[cnt].change_status('I');
        trans[cnt].set_serial(get_sn(book_id));
        cnt++;
        cout << "Successfully issued\n";
    }

    void ret(MemberList &m, string mem_id, BookList &b, string book_id , int sn){
        if (!m.verify(mem_id))
        {
            cout << "Wrong Member id\n";
            return;
        }
        int pos = verifybook(mem_id ,book_id, sn);
        if ( pos == -1) {cout << "Wrong book id or serial no\n";return;}
        b.ret(book_id);
        m.ret(mem_id);
        trans[cnt] = Return();
        trans[cnt].set_info(mem_id , book_id);
        trans[cnt].change_status('R');
        trans[cnt].set_serial(sn);
        cnt++;
    }

    int verifybook(string mem_id , string book_id , int sn){
        int i ;
        for (   i= cnt -1; i >= 0 ; i--){
            if ( trans[i].get_memId() == mem_id){
                if ( trans[i].get_bookId() == book_id && trans[i].get_serial_no() == sn){
                    break;
                }
            }
        }
        return i;
    }

    int get_sn(string book_id)
    {
        //serial starts from 1
        if ( cnt == 0) return 1;
        for ( int i = cnt-1; i >= 0; i--){
            if ( trans[i].get_bookId() == book_id){
                if (trans[i].get_status() == 'R'){
                    return (trans[i].get_serial_no() + 1);
                }

            }
        }
        return 1;
    }


};


class Library{

    public:
        TransactionList tl;
        MemberList ml;
        BookList bl;

    void perform(){

        while( true){
            
            cout << "MENU" << "\n";
            cout << string(40,'-')<<"\n";
            cout << "1 to add book\n2 to register member\n3 to do transaction( issue or return a book)\n";
            cout <<  "Please enter your choice :";

            int choice;
            cin >> choice;
            getchar();
            switch(choice)
            {
                case 1:{
                        cout << "enter book id";
                        string id;
                        cin >> id;
                        bl.add_book(id);
                        break;
                }
                case 2:{
                        cout << "enter member id";
                        string id;
                        cin >> id;
                        cout << "enter type"; 
                        string type;
                        cin >> type;
                        ml.add(id, type);
                        break;
                }
                case 3:{
                            cout << "Enter the member ID :";
                            string memID , bookId;
                            cin >> memID;
                            cout << "Enter the book ID :";
                            cin >> bookId;
                            char c;
                            cout << "Enter I for issue and R for return :";
                            cin >> c;
                            if ( c == 'I')
                            tl.issue(ml, memID, bl, bookId);
                            else{
                                cout << "Enter the serial number of the book you have :";
                                int sn;
                                cin >> sn;
                                tl.ret( ml , memID , bl, bookId , sn);
                            }
                            break;
                }
                default:{
                    cout <<"Wrong choice\n";
                    break;
                }



            }
            cout << "Enter n to stop";

            char c;
            cin >> c;
            if ( c == 'n')
                break;
            getchar();
        }
    }


};



int main(){
    // MemberList ml;
    // ml.add( "123" , "Student");
    // ml.add("124", "Stud");
    // ml.add("1223", "St32ent");
    // ml.add("1213" ,"Faculty");
    // ml.display();

    Library l;
    l.perform();

}