#include <algorithm>
#include <map>
#include <stdio.h>
#include <unordered_map>
#include <iostream>

using namespace::std;

class ConstMap {

    map<int, string> myMap;

public:
    const map<int, string> &getStatistics() const {
        return myMap;
    }    
    
    void fillStatistics() {
        myMap[5] = "String relating to 5";
        myMap[7] = "String relating to 7";
    }

    void printStatistics() {
         for_each(myMap.begin(), myMap.end(), [](const pair<int, string> &curItem){cout << curItem.second << endl;});
         cout << "\n";
    }
};


int main(int argc, char const **argv)
{
    ConstMap constMap;

    const map<int, string> &localMap = constMap.getStatistics();
    // Or use as a reference
    // constMap.getStatistics();
        
    constMap.printStatistics();

    constMap.fillStatistics();
    constMap.printStatistics();

    // (!) [] operator is not allowed, is non-const. Need to use at() or iterators implicitly
    cout << " >> Print using .at() method << " << endl;
    cout << localMap.at(5) << endl;
    cout << localMap.at(7) << endl;
    // cout << localMap.at(9) << endl;         // => This results in exception (surely)
    // cout << localMap[9] << endl;            // => And this is restricted dut to constness of the reference 
    
    // Restricted since const
    // localMap.insert(10);
    // constMap.printStatistics();

    // (!) Note as a reminder: this calls the Copy Constructor copies the map
    map<int, string> localMap2 = constMap.getStatistics();
    localMap2[10] = "Test";           // Insert to the new map
    for_each(localMap2.begin(), localMap2.end(), [](const pair<int, string> &curItem){cout << curItem.second << endl;});
    
    return 0;
}
