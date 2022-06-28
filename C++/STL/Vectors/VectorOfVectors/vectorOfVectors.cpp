// vect2.cpp -- methods and iterators
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[])
{
    using namespace std;

    //Create vector of vectors - vectorBunch. sub-vectors have different sizes
    vector<vector<int>> vectorsBunch = vector<vector<int>>{{1, 3, 5}, {2, 4, 6, 8}};

    //Print out vectorsBunch properties
    cout << "vectorsBunch properties: " << endl;
    cout << "Capacity: " << vectorsBunch.capacity() << endl;
    cout << "Max_size: " << vectorsBunch.max_size() << endl;
    cout << "Size (number of elements): " << vectorsBunch.size() << endl;

    //Insert another one vector at the end and swap it with the first one
    vectorsBunch.push_back({29, 45, 34, 48, 99});
    vectorsBunch[0].swap(vectorsBunch[2]);

    //Print out sub-Vectors params using iterators
    for(auto vectorsIter = vectorsBunch.begin(); vectorsIter != vectorsBunch.end(); vectorsIter++){
        cout << "Vector's size: " << (*vectorsIter).size() << endl;
        cout << "Vector's values: ";
        for(auto curNumber: (*vectorsIter)){

        }
    }

    constexpr int arrSize = 20;
    int * array = new int[arrSize]{0, 1, 2};     //Initialize fields: !!! initializer list may be for dynamic memory allocation

    int array2[20]{0, 1, 2};
    //int sizeArr = sizeof(array2) / sizeof(*array2);
    //cout << sizeArr;

    for(int i; i < 20; i++){
        cout << array[i] << endl;
    }

    return 0;
}
