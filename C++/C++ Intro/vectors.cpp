#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
    /*** Vectors test ***/
    vector<string> articles{"Hi", "Lane", "Shane"};
    vector<string> articles2(10, "aaa");
    articles2[3] = "asdas";
    string word;
    // while (cin >> word)
    // {
    //     articles2.push_back(word); // append word to articles2
    // }
    // cout << "Number of elements in articles is: " << articles2.size() << endl;
    // cout << articles2[3];

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : v) // for each element in v (note: i is a reference)
        i *= i;       // square the element value

    for (auto i : v)      // for each element in v
        cout << i << " "; // print the element
    cout << endl;

    vector<string> text{"Word1", "\n", "Word2", "\n" "End of the text" "\n"};

    for (auto it = text.cbegin(); it != text.cend(); it++)
        cout << *it;

    /*** Check time for C-style array, array and vector ***/
    float Carray[100000] = {0.0};
    array<float, 100000> array1 = {0.0};
    vector<float> vector1(100000, 0.0);
    // 1. C-array time test
    clock_t point1 = clock();
    clock_t point2;
    for (auto i = 1; i != 1000; i++)
    {
        for (auto it = begin(Carray); it != end(Carray); it++)
        {
            *it = i;
            //  cout << endl << i << " element: " << *i;
            *it = pow(static_cast<int>(*it), 5);
            *it = sqrt(*it) * pow(static_cast<int>(*it), 3);
            //  cout << i << " element: " << *i << endl;
        }
    }
    point2 = clock();
    cout << "C-array spent time is: " << (point2 - point1) / (double)CLOCKS_PER_SEC << endl;

    // 2. Array time test
    point1 = clock();
    for (auto i = 1; i != 1000; i++)
    {
        for (auto it = array1.begin(); it != array1.cend(); it++)
        {
            *it = i;
            //  cout << endl << i << " element: " << *i;
            *it = pow(static_cast<int>(*it), 5);
            *it = sqrt(*it) * pow(static_cast<int>(*it), 3);
            //  cout << i << " element: " << *i << endl;
        }
    }
    point2 = clock();
    cout << "Array spent time is: " << (point2 - point1) / (double)CLOCKS_PER_SEC << endl;

    // 3. Vector time test
    point1 = clock();
    for (auto i = 1; i != 1000; i++)
    {
        for (auto it = array1.begin(); it != array1.cend(); it++)
        {
            *it = i;
            //  cout << endl << i << " element: " << *i;
            *it = pow(static_cast<int>(*it), 5);
            *it = sqrt(*it) * pow(static_cast<int>(*it), 3);
            //  cout << i << " element: " << *i << endl;
        }
    }
    point2 = clock();
    cout << "Vector spent time is: " << (point2 - point1) / (double)CLOCKS_PER_SEC << endl;

    char endChar;
    cin.get(endChar);
    while (!cin.fail()) // test for EOF or while (cin.get(ch)), since cin.get(ch) returns reference to cin, which converted to bool false if EOF
    //while ((ch = cin.get()) != EOF) // or this way,
    {       cout << "Current char is: " << endChar << endl;
            cin.get(endChar); // attempt to read another char
    }


    return 0;
}
