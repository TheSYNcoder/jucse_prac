#include <iostream>
using namespace std;
const int MAX_ACCOUNT_NO = 1e2+5;
class AccountList;
class account{
    string acc_no;
    int amount;

public:
    account():acc_no(""), amount(0){}
    account(string s , int amt):acc_no(s), amount(amt){}
        friend void display_acc(account);
        friend string get_accNo(account);
        friend int get_amount(account);
        friend void withdraw( account & , AccountList &);
        
};


string get_accNo(account ac){
    return ac.acc_no;
}

int get_amount( account ac){
    return ac.amount;
}

void display_acc( account ac){

    cout << "The account number :" << ac.acc_no << "\n";
    cout << "The balance contained :" << ac.amount << "\n";
    cout << string(40, '-') << "\n";
}

class AccountList{
    account accounts[MAX_ACCOUNT_NO];
    // add
    // withdraw
    // find account
    // unique acc no
    // display info of all accounts
    public:
    static int ACC_COUNT;
    void add();
    friend void withdraw(account &, AccountList &);
    int find_account(string );
    void display();
    friend void Withdraw(AccountList &);
};

int AccountList::ACC_COUNT =0;

void withdraw( account &withdrawObject , AccountList &ac){
    for ( int i =0; i < AccountList::ACC_COUNT; i++){
        if ( ac.accounts[i].acc_no == withdrawObject.acc_no){
            if ( ac.accounts[i].amount < withdrawObject.amount)
                {
                    cout << "Amount in account is insufficient \n";
                    return;
                }
            ac.accounts[i].amount -= withdrawObject.amount;
            return;
        }
    }
}

void Withdraw(AccountList &lis){

    string acc_no;
    cout << "Enter the account number from which money is to be withdrawn :";
    cin >> acc_no;
    if ( lis.find_account(acc_no))
    {
        int amt;
        cout << "Enter the amount to be withdrawn :";
        cin >> amt;
        account withdrawObject( acc_no , amt);
        withdraw( withdrawObject , lis);

    }
    else
    {
        cout <<"The account must exist\n";
        return;
    }
}
void AccountList::add(){
    string acc;
    cout << "Enter new account no :";
    cin >> acc;
    for ( int i = 0; i < ACC_COUNT; i++){
        if (get_accNo(accounts[i]) == acc){
            cout << "Account number has to be unique\n";
            return;
        }
    }
    int amt;
    cout << "Enter amount in new account :";
    cin >> amt;
    account ac(acc , amt);
    accounts[ACC_COUNT++]=ac;
}

void AccountList::display(){
    for ( int i =0 ; i < ACC_COUNT; i++){
        cout << string(40, '-') << "\n";
        cout << "Account details for id :" << i+1 << " " << "\n";
        display_acc(accounts[i]);
    }
}

int AccountList::find_account(string accNo){
    
    for ( int i =0 ; i < ACC_COUNT; i++){
        if ( get_accNo(accounts[i]) == accNo)
        {
            cout << "The account is found " << "\n";
            display_acc(accounts[i]);
            return 1;
        }
    }
    cout << " The account is not found\n";
    return 0;
    

}

int main(){
    AccountList lis;
    while(true){

        cout << "Menu\n";
        cout << string(40, '-') << "\n";
        cout << "1 to add new account\n2 to display info of all accounts\n3 to withdraw\n";
        int n;
        cin >> n;
        switch(n){
            case 1:
            lis.add();
            break;
            case 2:
            lis.display();
            break;
            case 3:
            Withdraw(lis);
            break;
            default:
            cout <<"wrong choice\n";
            break;
            
        }

        char ch;
        cout << "Y/N to continue/exit\n";
        cin >>ch;
        if (ch == 'Y' || ch == 'y')
            continue;
        else
            break;
    }
}