#include <bits/stdc++.h>
using namespace std;
#include <fstream>
#include <chrono>
#include <iterator>


class A{
    int x;
    friend int getx(A &a){
        return a.x;
    }
    public:
    A(): x(5){}
};


class B{
    int y;
    public:
    int getx(A &a);
};
int main()
{
    A a;
    B b;
    cout  << b.getx(a);
    // //Time taken by cin >> 0.037473
    // //Time taken by iterator >> 0.039581
    // //Time taken by scanf % 0.022861
    // //

    // // auto start = chrono::high_resolution_clock::now();

    // // // unsync the I/O of C and C++.
    // // ios_base::sync_with_stdio(false);

    // // FILE *fp;
    // // fp =fopen( "input.txt" , "r");
    // // int x;
    // // while ( true ){
    // //     if (!fscanf(fp, "%d", &x))
    // //         break;
        
    // //     if (feof(fp))
    // //     break;
        
    // // }

    // // auto end = chrono::high_resolution_clock::now();

    // // // Calculating total time taken by the program.
    // // double time_taken =
    // //     chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    // // time_taken *= 1e-9;

    // // cout << "Time taken by program is : " << fixed
    // //      << time_taken << setprecision(9);
    // // cout << " sec" << endl;
    // // return 0;
    // int n = 4;

    // try{
    //     n=6;
    //     if ( n > 4)
    //     throw "more than index value\n";
    // }
    // catch (char const * s ){
    //     string ss(s);
    //     cout << ss  << "\n";
    // }
}