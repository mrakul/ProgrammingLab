#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a vector and one empty vector as output to double values of
    vector<int> sourceVector{1, 2, 3, 4, 5};
    vector<int> targetVector{};

    // 1. Transform 1-st variation example: first variation uses the begin-end range of input container, the begin iterator of output container and unary function
    transform(sourceVector.begin(), sourceVector.end(), back_inserter(targetVector), [](const int &curItem){ return (curItem * 2);});                     // Double every source vector's value and save it in the target vector. Note: use back_inserter or insert_iterator (surely) not to have Seg Fault or any bad things
    for_each(targetVector.begin(), targetVector.end(), [](const int &curItem){cout << curItem << endl;});

    // 2. Transform 2nd variation example: uses two input ranges (begin-end and begin), a binary function getting items from both ranges and the output iterator
    vector<float> sourceVectorFloats{10.1f, 20.1f, 30.1f, 40.1f, 50.1f};
    vector<string> numbersInStrings{};

    auto multIntFloat = [](const int &curItemInt, const float &curItemFloat){return to_string(curItemInt * curItemFloat);};
    transform(sourceVector.begin(), sourceVector.end(), sourceVectorFloats.begin(), back_inserter(numbersInStrings), multIntFloat);                      // Use both vectors of ints and floats, process by lambda to multiply the numbers and out the result to the vector of the strings
    numbersInStrings[0] = move(numbersInStrings[numbersInStrings.size() - 1]);                                                                           // Move the last string to the first
    numbersInStrings[numbersInStrings.size() - 1] = "This is the last string";                                                                           // Fill the last with a new string

    for_each(numbersInStrings.begin(), numbersInStrings.end(), [](const string &curItem){cout << curItem << endl;});                                     // Print out the resulting vector

    return 0;
}
