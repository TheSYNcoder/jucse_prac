#include <iostream>
#include <cstdio>
using namespace std;
class node{
public:
	int data;
	node *next;
	node(){
	data = 0;
	next = NULL;
}
  	node* createNode( int info){
	node *nn = new node;
	nn->data = info;
	nn->next = NULL;
	return nn;

}

};

class LinkedList{


private: 

	void getinfo(int &val){
	printf("enter value to be inserted\n");
	cin >> val;
	
}
	node h;
	node *head = h.createNode(0);

public:
	
	
	void insert_after( node *p){
	int val;getinfo(val);
	node *temp = h.createNode(val);
	temp->next = p -> next;
	p-> next = temp;
	 
}
	void insert_front(){
	int val;getinfo(val);
	node *temp = h.createNode(val);
	temp -> next = head -> next;
	
	head -> next = temp;

}
	void delete_front(){
	node *temp = h.createNode(0);
	temp = head -> next;

	head -> next = temp -> next;
	temp -> next = NULL;
	free(temp);
}
	void display(){
	node *temp = h.createNode(0);
	temp = head;
	temp = temp -> next;
	while ( temp != NULL){
		cout << temp -> data << (temp -> next != NULL ?" --> ":"");
		temp = temp-> next; 
	}
	cout << "\n";
}

};
int main()
{
	// LinkedList called by adding new values to it
	LinkedList ll;
	ll.insert_front();
	ll.insert_front();
	ll.display();
	ll.delete_front();
	ll.display();
	
}
