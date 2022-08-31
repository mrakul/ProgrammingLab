// vect2.cpp -- methods and iterators
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[])
{
    using namespace std;

    // Create vector of vectors - vectorBunch. sub-vectors have different sizes
    vector<vector<int>> vectorsBunch = vector<vector<int>>{{1, 3, 5}, {2, 4, 6, 8}};

    // Print out vectorsBunch properties
    cout << "vectorsBunch properties: " << endl;
    cout << "Capacity: " << vectorsBunch.capacity() << endl;
    cout << "Max_size: " << vectorsBunch.max_size() << endl;
    cout << "Size (number of elements): " << vectorsBunch.size() << endl;

    // Insert another one vector at the end and swap it with the first one
    vectorsBunch.push_back({29, 45, 34, 48, 99});
    vectorsBunch[0].swap(vectorsBunch[2]);

    // Print out sub-Vectors params using iterators
    for (auto vectorsIter = vectorsBunch.begin(); vectorsIter != vectorsBunch.end(); vectorsIter++){
        cout << "Vector's size: " << (*vectorsIter).size() << endl;
        cout << "Vector's values: ";
        for (auto curNumber : (*vectorsIter)){
            cout << curNumber << " ";
        }
        cout << (*vectorsIter).at(10) << endl;     //at() provides access by index, but with checking the boundaries, thows out_ot_range exception
        cout << endl;
    }

    return 0;
}
