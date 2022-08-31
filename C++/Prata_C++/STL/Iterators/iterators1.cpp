// copyit.cpp -- copy() and iterators
#include <iostream>
#include <iterator>
#include <vector>
int main()
{
    using namespace std;
    int numbers[10] = {6, 7, 2, 9, 4, 11, 8, 7, 10, 5};
    vector<int> numbersVect(10);

    // copy from array to vector
    copy(numbers, numbers + 10, numbersVect.begin());
    cout << "Let the dice be cast!\n";

    // create an ostream iterator
    ostream_iterator<int, char> out_iter(cout, " ");

    // copy from vector to output
    copy(numbersVect.begin(), numbersVect.end(), out_iter);
    cout << endl;

    //Reverse iterator
    cout << "Implicit use of reverse iterator.\n";
    copy(numbersVect.rbegin(), numbersVect.rend(), out_iter);
    cout << endl;

    //Explicit named iterator
    cout << "Explicit use of reverse iterator.\n";
    vector<int>::reverse_iterator ri;
    for (ri = numbersVect.rbegin(); ri != numbersVect.rend(); ++ri)
        cout << *ri << ' ';
    cout << endl;

    return 0;
}