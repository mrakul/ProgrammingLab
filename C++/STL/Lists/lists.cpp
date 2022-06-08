// list.cpp -- using a list
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

void outint(int n) {std::cout << n << " ";}

int main()
{
    using namespace std;
    list<int> one(5, 2); // list of 5 2s

    int stuff[5] = {1, 2, 4, 8, 6};
    list<int> two;      //empty list
    two.insert(two.begin(), stuff, stuff + 5);

    int more[6] = {6, 4, 2, 4, 6, 5};
    list<int> three(two);
    three.insert(three.end(), more, more + 6);


    cout << "List one: ";
    //for_each(one.begin(), one.end(), outint);
    for(auto number: one) cout << number << ' ';

    cout << endl << "List two: ";
    for(auto number: two) cout << number << ' ';

    cout << endl << "List three: ";
    for(auto number: three) cout << number << ' ';
    three.remove(2);
    cout << endl << "List three minus 2s: ";
    for(auto number: three) cout << number << ' ';

    three.splice(three.begin(), one);
    cout << endl << "List three after splice: ";

    for_each(three.begin(), three.end(), outint);
    cout << endl << "List one: ";

    for_each(one.begin(), one.end(), outint);
    three.unique();

    cout << endl << "List three after unique: ";
    for_each(three.begin(), three.end(), outint);
    three.sort();
    three.unique();

    cout << endl << "List three after sort & unique: ";
    for_each(three.begin(), three.end(), outint);

    two.sort();
    three.merge(two);
    cout << endl << "Sorted two merged into three: ";

    for_each(three.begin(), three.end(), outint);
    cout << endl;

    return 0;
}
