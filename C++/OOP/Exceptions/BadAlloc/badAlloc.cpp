// newexcp.cpp -- the bad_alloc exception
#include <iostream>
#include <new>
#include <cstdlib> // for exit(), EXIT_FAILURE
using namespace std;

struct Big
{
    double stuff[200000];
};
int main()
{
    Big *pb;
    try
    {
        cout << "Trying to get a big block of memory:\n";
        pb = new Big[100000]; // 1,600,000,000 bytes
        cout << "Got past the new request:\n";
        // Not to throw an excpetion, old version
        //pb = new (std::nothrow) Big[10000]; // 1,600,000,000 bytes
        // if (pb == 0)
        // {
        //     cout << "Could not allocate memory. Bye.\n";
        //     exit(EXIT_FAILURE);
        // }
    }
    catch (bad_alloc &ba)
    {
        cout << "Caught the exception!\n";
        cout << ba.what() << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Memory successfully allocated\n";
    pb[0].stuff[0] = 4;
    cout << pb[0].stuff[0] << endl;
    delete[] pb;
    return 0;
}