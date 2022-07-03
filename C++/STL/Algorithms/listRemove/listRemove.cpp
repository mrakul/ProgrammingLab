// listrmv.cpp -- applying the STL to a string
#include <iostream>
#include <list>
#include <algorithm>
void Show(int);
constexpr int LIM = 10;

int main()
{
    using namespace std;

    //Create lists
    list<int> listNumbers {4, 5, 4, 2, 2, 3, 4, 8, 1, 4};
    list<int> listCopy(listNumbers);

    //Print out original list
    cout << "Original list contents:\n\t";
    for_each(listNumbers.begin(), listNumbers.end(), Show);
    cout << endl;

    //Remove number 4 from the list using member function: the list's size automatically adjusted
    listNumbers.remove(4);
    cout << "After using the remove() method:\n";
    cout << "listNumbers:\t";
    for_each(listNumbers.begin(), listNumbers.end(), Show);
    cout << endl;

    //Remove the values using remove Algorithm's, which can't adjust the list's size
    list<int>::iterator lastElem;
    lastElem = remove(listCopy.begin(), listCopy.end(), 4); //returns the iterator of the last element having value
    cout << "After using the remove() function:\n";
    cout << "listCopy:\t";
    for_each(listCopy.begin(), listCopy.end(), Show);       //The last 4 elemens still remains in the list
    cout << endl;

    //Clear the rest of elements at the end of the list adjusting the size
    listCopy.erase(lastElem, listCopy.end());
    cout << "After using the erase() method:\n";
    cout << "listCopy:\t";
    for_each(listCopy.begin(), listCopy.end(), Show);
    cout << endl;

    return 0;
}

void Show(int v)
{
    std::cout << v << ' ';
}