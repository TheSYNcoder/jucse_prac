#include <iostream>
#include <fstream>

using namespace std;

class Book
{
    string id;
    string title;
    string author;
    string price;

public:
    void get_info(string Id)
    {
        id = Id;
        cout << "Enter title :";
        cin >> title;
        cout << "Enter  author :";
        cin >> author;
        cout << "Enter price :";
        cin >> price;
    }
    string get_id()
    {
        return id;
    }
};
const int Max = 1e4;
class BookMap
{
    Book b;
    int available;
    int total;

public:
    BookMap()
    {
        available = 0;
        total = 0;
    }
    void add()
    {
        available++;
        total++;
    }
    void get_info(string id)
    {
        b.get_info(id);
        available = 1;
        total = 1;
    }
    Book get_book()
    {
        return b;
    }
    int av()
    {
        return available;
    }
    void dec()
    {
        available--;
    }
    void inc()
    {
        available++;
    }
};
int main(){
    while(true){
    BookMap obj;
    string filename = "books.txt";
    fstream o;
    o.open(filename);
    o.seekp(0 , ios_base::end);
    obj.get_info("1");
    o.write( (char*)(&obj) , sizeof(obj));
    obj.get_info("2");
    o.write((char *)(&obj), sizeof(obj));

    o.close();
    fstream i;
    i.open(filename);
    i.read((char*)(&obj) , sizeof(obj));
    i.seekp(0 , ios_base::beg);
    cout << i.tellp() << "\n";
    while ( !i.eof()){
        cout << "reading\n";
        i.read((char*)(&obj) , sizeof(obj));
    }
    i.close();
    fstream f;
    f.open(filename);
    f.seekg(-sizeof(obj), ios_base::end);
    
    f.read((char*)(&obj) , sizeof(obj));
    while( !f.eof()){
        cout << "after\n";
        f.read( (char*)(&obj) , sizeof(obj));
    }
    f.close();
    }
}