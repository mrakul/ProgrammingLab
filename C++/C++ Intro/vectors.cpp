#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
        /*** Vectors test ***/
    vector<string> articles{"Hi", "Lane", "Shane"};
    vector<string> articles2(10, "aaa");
    articles2[3] = "asdas";
    string word;
    while (cin >> word)
    {
        articles2.push_back(word); // append word to articles2
    }
    cout << "Number of elements in articles is: " << articles2.size() << endl;
    cout << articles2[3];

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : v)     // for each element in v (note: i is a reference)
        i *= i;           // square the element value

    for (auto i : v)      // for each element in v
        cout << i << " "; // print the element
    cout << endl;

    vector<string> text{"Word1", "\n", "Word2", "End of the text"};

    for (auto it = text.cbegin(); it != text.cend(); it++)
        cout << *it;

    return 0;
}
