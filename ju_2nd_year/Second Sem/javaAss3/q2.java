import java.util.*;



class Account{
    String acc_no;
    String name;
    int balance;


    public Account() {
    }

    public Account(String acc_no, String name, int balance) {
        this.acc_no = acc_no;
        this.name = name;
        this.balance = balance;
    }

    public String getAcc_no() {
        return this.acc_no;
    }

    public void setAcc_no(String acc_no) {
        this.acc_no = acc_no;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getBalance() {
        return this.balance;
    }

    public void setBalance(int balance) {
        this.balance = balance;
    }

    public Account acc_no(String acc_no) {
        this.acc_no = acc_no;
        return this;
    }

    public Account name(String name) {
        this.name = name;
        return this;
    }

    public Account balance(int balance) {
        this.balance = balance;
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Account)) {
            return false;
        }
        Account account = (Account) o;
        return Objects.equals(acc_no, account.acc_no) && Objects.equals(name, account.name) && balance == account.balance;
    }

    // @Override
    // public int hashCode() {
    //     return Objects.hash(acc_no, name, balance);
    // }

    @Override
    public String toString() {
        return "{" +
            " acc_no='" + getAcc_no() + "'" +
            ", name='" + getName() + "'" +
            ", balance='" + getBalance() + "'" +
            "}";
    }

    void get_data(){
        Account a;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the account_no");
        acc_no = sc.nextLine();
        System.out.println("Enter the name");
        name = sc.nextLine();
        System.out.println("Enter the balance");
        balance = sc.nextInt();
    }

    void display(){
        System.out.println(acc_no);
        System.out.println(name);
        System.out.println(balance);
    }
}

class Acc_List{
    ArrayList<Account> arr;
    HashMap<String, Integer> m;
    Acc_List(){
        arr = new ArrayList<>();
        m = new HashMap<String , Integer>();
        
    }

    void add(){
        Account a = new Account();
        a.get_data();
        for ( int i =0 ; i < arr.size() ; i++){
            if ( arr.get(i).getAcc_no().equals(a.acc_no)){
                System.out.println("Already exists");
                return; 
            }
        }
        arr.add(a);
        m.put(a.acc_no , a.balance);
    }

    void display(String no){
        for ( int i =0; i < arr.size() ; i++){
            if ( arr.get(i).getAcc_no().equals(no)){
                arr.get(i).display();
                return;
            }
        }
    }

    // void Add(Account a){
    //     arr.add(a);
    //     m.put(a, a.balance);
    // }


    boolean exist(String no){
            return ( m.containsKey(no) );
    }

    Integer getBalance ( String no){
        return ( m.get(no));
    }

}


class Test{

    public static void main(String args[]){
        // Account a , b;
        // a = new Account("1" , "name1" , 1000);
        // b = new Account( "2" , "name2" , 2000);
        Acc_List al =new Acc_List();
        // al.Add(a);
        // al.Add(b);
        // System.out.println(al.exist(a));
        // System.out.println(al.exist(new Account("3 " , "name3" , 4000)));
        // System.out.println(al.getBalance(b));

        Scanner sc = new Scanner(System.in);
        String dum;

        while(true){
            System.out.println("Menu");
            System.out.println("Enter 1 to add account");
            System.out.println("Enter 2 to display account");
            System.out.println("Enter 3 to check if it exists");
            System.out.println("Enter 4 to show balance");
            int x;
            x = sc.nextInt();
            String nn;
            switch(x){
               case 1:{
                   al.add();
                   break;
               }
               case 2:{
                   System.out.print("ENter account no\n");
                   dum = sc.nextLine();
                    nn = sc.nextLine();
                    al.display(nn);
                   break;
               }
               case 3:{
                   System.out.print("ENter account no\n");
                   dum = sc.nextLine();
                   nn = sc.nextLine();
                  if( al.exist(nn)){
                      System.out.println("Account exists");
                  }
                  else{
                      System.out.println("account does not exist");
                  }
                   break;
               }
               case 4:{
                   System.out.print("ENter account no\n");
                   dum = sc.nextLine();
                   nn = sc.nextLine();
                   System.out.println("Balance for" + nn +  " = " + al.getBalance(nn));
                   break;
               }


            }
            System.out.println("Enter n to break");
            char c = sc.next().charAt(0);
            if (c == 'n')
                break;

        }

    }
}