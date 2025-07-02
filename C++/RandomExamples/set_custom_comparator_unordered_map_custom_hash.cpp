#include <algorithm>
#include <set>
#include <stdio.h>
#include <unordered_set>
#include <iostream>

struct CustomData
{
    int id = 0;
    char symbol = 'a';

    // For set: need to specify operator<() here or externally specify comparator
    // bool operator<(const CustomData &comparedData) const
    // {
    //     return (id < comparedData.id) ? true : false;
    // }

    // For unordered_map: need to specify == operator to be able to compare keys
    // (!!) Important to make method const (cannot modify the object)
    bool operator==(const CustomData &comparedData) const {
        return this->id == comparedData.id ? true : false;
    }
};

bool setComparator(CustomData leftSet, CustomData rightStruct) {
    return leftSet.symbol < rightStruct.id ? true : false;
}

// unordered_set doesn't work without specifying hash-function, can't be compiled
template <>
struct std::hash<CustomData>
{
    std::size_t operator()(const CustomData& hashedStruct) const
    {
        return hash<char>()(hashedStruct.symbol) ^ hash<int>()(hashedStruct.symbol);
    }
};


class ConstSet {

    std::set<int> mySet;

public:
    const std::set<int> &getStatistics() const {
        return mySet;
    }    
    
    void fillStatistics() {
        mySet.insert(5);
        mySet.insert(7);
    }

    void printStatistics() {
         std::for_each(mySet.begin(), mySet.end(), [](const int &curItem){std::cout << curItem << std::endl;});
    }
};

using namespace::std;

int main(int argc, char const **argv)
{
    ConstSet constSet;

    const set<int> &localSet = constSet.getStatistics();
    constSet.printStatistics();

    constSet.getStatistics().
    
    constSet.fillStatistics();
    constSet.printStatistics();
    
    localSet.insert(10);
    constSet.printStatistics();

    // 1. Representation that Comparator is needed for set

    set<CustomData, decltype(&setComparator)> mySet(&setComparator);
    // That doesn't work, since comparator is needed
    // set<CustomData> mySet;    
    CustomData myData{1, 'b'};

    mySet.insert(myData);

    // 2. Representation that hash-function is needed for unordered_map
    unordered_set<CustomData> myHashSet;
    myHashSet.insert(myData);

    return 0;
}
