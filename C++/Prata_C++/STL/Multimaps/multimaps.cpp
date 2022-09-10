// multmap.cpp -- use a multimap
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

typedef int KeyType;                                    // (!) Make int KeyType
typedef std::pair<const KeyType, std::string> Pair;     // work with pairs: keys as ints and value as strings
typedef std::multimap<KeyType, std::string> MyMultiMap; // Multimap with KeyType of ints and values of strings

int main(int argc, const char *argv[])
{
    using namespace std;
    MyMultiMap cities;
    //Populate the map: added values are ordered automatically
    cities.insert(Pair(415, "San Francisco"));
    cities.insert(Pair(510, "Oakland"));
    cities.insert(Pair(718, "Brooklyn"));
    cities.insert(Pair(718, "Staten Island"));
    cities.insert(Pair(415, "San Rafael"));
    cities.insert(make_pair(510, "Berkeley"));          // May be added this way

    //Count the number of cities by codes
    cout << "Number of cities with area code 415: "
         << cities.count(415) << endl;
    cout << "Number of cities with area code 718: "
         << cities.count(718) << endl;
    cout << "Number of cities with area code 510: "
         << cities.count(510) << endl;
    cout << "Area Code City\n";

    //Print all pairs of the map
    MyMultiMap::iterator it;        //Create iterator explicitly
    for (it = cities.begin(); it != cities.end(); ++it)
        cout << " " << (*it).first << " "
             << (*it).second << endl;

    //Print only the cities with the code 718
    pair<MyMultiMap::iterator, MyMultiMap::iterator> range = cities.equal_range(718);     //Returns the pair of iterators to get the values of map with particular city code
    // The simplest declaration is:
    // auto range = cities.equal_range(718);
    cout << "Cities with area code 718:\n";
    for (it = range.first; it != range.second; ++it)
        cout << (*it).second << endl;

    return 0;
}
