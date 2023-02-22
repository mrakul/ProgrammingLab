#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

using namespace std;

/*** fill(), generate() examples***/

void printContainer(auto &containerToPrint);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a set
    vector<int> myVector{1, 2, 3, 4, 5, 7, 8, 9};
    printContainer(myVector);

    // 1. fill()
    fill(myVector.begin(), myVector.end(), 10);
    printContainer(myVector);

    // 2. fill_n()
    fill_n(myVector.begin(), 4, 20);
    printContainer(myVector);

    // 3. generate()
    int i = 0;
    auto incrementor = [&i]()->int {return (++i);};
    generate(myVector.begin(), myVector.end(), incrementor);
    printContainer(myVector);

    // 4. generate_n()
    /* Random generator example*/
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> distribution(1.0, 10.0);
    auto randomGenerator = [&distribution, &mt](){ return distribution(mt);};
    /* End Random generator*/

    generate_n(myVector.begin(), 4, randomGenerator);
    printContainer(myVector);

    return 0;
}

void printContainer(auto &containerToPrint)
{
    cout << "Vector's size and capacity: " << containerToPrint.size() << " " << containerToPrint.capacity() << endl;
    for (auto &curItem : containerToPrint)
        cout << curItem << ", ";
    cout << endl;
}