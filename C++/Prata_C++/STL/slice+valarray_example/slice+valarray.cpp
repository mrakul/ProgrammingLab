// vslice.cpp -- using valarray slices
#include <iostream>
#include <valarray>
#include <cstdlib>
const int SIZE = 12;

typedef std::valarray<int> valarrInt; // simplify declarations

void show(const valarrInt &v, int cols);
int main(int argc, char const *argv[])
{
    using std::cout;
    using std::slice;  // from <valarray>
    valarrInt vInts(SIZE); // think of as 4 rows of 3
    int i;
    for(i = 0; i < SIZE; ++i)
        vInts[i] = std::rand() % 10;
    cout << "Original array:\n";

    show(vInts, 3);                   // show in 3 columns
    valarrInt vcol(vInts[slice(1, 4, 3)]); // extract 2nd column
    cout << "Second column:\n";
    show(vcol, 1);                     // show in 1 column
    valarrInt vrow(vInts[slice(3, 3, 1)]); // extract 2nd row
    cout << "Second row:\n";
    show(vrow, 3);

    vInts[slice(2, 4, 3)] = 10; // assign to 2nd column
    cout << "Set last column to 10:\n";
    show(vInts, 3);

    cout << "Set first column to sum of next two:\n";
    // (!!!) '+' is not defined for slices, so convert to valarray<int>
    vInts[slice(0, 4, 3)] = valarrInt(vInts[slice(1, 4, 3)]) + valarrInt(vInts[slice(2, 4, 3)]);
    show(vInts, 3);
    return 0;
}

void show(const valarrInt &v, int cols){
    using std::cout;
    using std::endl;
    int lim = v.size();
    for (int i = 0; i < lim; ++i){
        cout.width(3);
        cout << v[i];
        if (i % cols == cols - 1)
            cout << endl;
        else
            cout << ' ';
    }
    if (lim % cols != 0)
        cout << endl;
}