#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <random>

using namespace std;

/*** random_shuffle(), shuffle(), sample() examples ***/

void printVector(auto &vectToOut);

int main(int argc, char const *argv[])
{
    vector<int> myVector{1, 2, 3, 4, 5, 7, 8, 9};
    vector<int> myVector2(myVector);
    vector<int> myVector3(myVector);
    printVector(myVector);

    // 1. random_shuffle() example. Note: random_shuffle() is deprecated since C++17
    srand(time(0));
    random_shuffle(myVector.begin(), myVector.end(), [](auto curNum){return std::rand() % curNum;});
    printVector(myVector);

    // 2. shuffle() example: random generator is mandatory, not optional
    unsigned long seed = chrono::system_clock::now().time_since_epoch().count();                            // Make a seed to use in shuffle function below
    shuffle(myVector2.begin(), myVector2.end(), default_random_engine(seed));
    printVector(myVector);

    // 3. sample() example: takes n number of items from the input range and out it to the output container.
    // Important: sample() is stable algorithm, so it preserves the order if items
    vector<int> targetVector(myVector3.size());
    seed = chrono::system_clock::now().time_since_epoch().count();

    auto newEnd = sample(myVector3.begin(), myVector3.end(), targetVector.begin(), 3, default_random_engine(seed));     // Sample returns the end of the target container (one past the last written)
    printVector(targetVector);
    targetVector.erase(newEnd, targetVector.end());
    printVector(targetVector);

}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << ", ";
    cout << endl;
}