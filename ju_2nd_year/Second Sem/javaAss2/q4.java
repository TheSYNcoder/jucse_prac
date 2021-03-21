import Transaction.*;
import Member.*;
import BookList.*;
import java.util.*;


class Test {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        MemberList ml = new MemberList();
        Booklist.BookList bl = new Booklist.BookList();
        Transaction.TransactionList tl = new Transaction.TransactionList();

        while ( true){
            System.out.println("Menu Screen");
            System.out.println(" 1 to add a new book");
            System.out.println(" 2 to add a new member ");
            System.out.println(" 3 to issue a book for a member");

            int choice = sc.nextInt();
            switch(choice){
                case 1:
                {
                    bl.addBook();
                    break;
                }
                case 2:
                {
                    ml.addMember();
                    break;
                }
                case 3:
                {
                    

                    System.out.print("Enter the member id\n");
                    String mid = sc.next();
                    System.out.print("Enter the book id\n");
                    String bid = sc.next();
                    tl.addIssueTransaction(bl , ml,  bid, mid);
                    break;
                }
                default:
                    System.out.println("Enter again");
                    break;
            }
            System.out.println("Enter n to exit");
            char c = sc.next().charAt(0);
            if (c == 'n'){
                break;
            }
            


        }
    }
}