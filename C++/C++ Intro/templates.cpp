#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct job
{
    char name[40];
    double salary;
    int floor;
};

// Non-template function prototype - overrides template function generated
// void Swap(job &, job &);

// Template prototype
template <typename T>
void Swap(T &a, T &b);    //Or template <class T> - implicit instantiation: compiler generates code only when encounter particular use with specified types within the code

// Explicit specialization                      //Overrides template function generated
template <>
void Swap<job> (job &job1, job &job2);

//Explicit instantiation
//template void Swap<int>(int, int); // explicit instantiation -> force the compiler to generate the code for int (?)

void Show(job &j);

int main()
{
    using namespace std;
    ios_base::fmtflags initial;
    initial = cout.setf(ios_base::fixed); // save initial formatting state
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);

    //Use template (generated from the general definition)
    int i = 10, j = 20;
    cout << "i, j = " << i << ", " << j << ".\n";
    cout << "Using compiler-generated int swapper:\n";
    Swap(i, j); // generates void Swap(int &, int &)
    cout << "Now i, j = " << i << ", " << j << ".\n";

    // Use Swap of Explicit specialization
    job sue = {"Susan Yaffee", 73000.60, 7};
    job sidney = {"Sidney Taffee", 78060.72, 9};
    cout << "Before job swapping:\n";

    Show(sue);
    Show(sidney);
    Swap(sue, sidney); // uses void Swap(job &, job &), overrides general template
    cout << "After job swapping:\n";
    Show(sue);
    Show(sidney);
    // cin.get();

    cout.setf(initial); // restore initial formatting state
    return 0;
}

template <typename T>
void Swap(T &a, T &b) // General template version
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

// Explicit specialization definition
template <> void Swap<job> (job &job1, job &job2) // specialization
//template void Swap<char> (char &ch1, char &ch2)  // !! explicit instantiation
{
    double temp1;
    int temp2;

    temp1 = job1.salary;
    job1.salary = job2.salary;
    job2.salary = temp1;

    temp2 = job1.floor;
    job1.floor = job2.floor;
    job2.floor = temp2;
}

void Show(job &j)
{
    using namespace std;
    cout << j.name << ": $" << j.salary << " on floor " << j.floor << endl;
}