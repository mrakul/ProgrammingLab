#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

struct billionaire
{
    string name;
    double dollars;
    string country;
};

int main(int argc, char const *argv[])
{
    list<billionaire> billionaires{
        {"Bill Gates", 86.0, "USA"},
        {"Warren Buffet", 75.6, "USA"},
        {"Jeff Bezos", 72.8, "USA"},
        {"Amancio Ortega", 71.3, "Spain"},
        {"Mark Zuckerberg", 56.0, "USA"},
        {"Carlos Slim", 54.5, "Mexico"},
        {"Bernard Arnault", 41.5, "France"},
        {"Liliane Bettencourt", 39.5, "France"},
        {"Wang Jianlin", 31.3, "China"},
        {"Li Ka-shing", 31.2, "Hong Kong"}
    };

    map<string, pair<const billionaire, size_t>> myMap;             // Map with the records of: [Country, [Highest billionire, Number of billionaires of the country]]

    // Explanation: we are placing the records from the list to the map with the key of the country name.
    // The list is already sorted in descending order by dollars.
    // If the country already exists, we are checking the success boolean to increment the number of billionares of this country having the current iterator.
    for (const auto &curBillionaire : billionaires){
        auto [iterator, success] = myMap.try_emplace(curBillionaire.country, curBillionaire, 1);

        if (!success){
            //(*iterator).second.second += 1;                                // Increment the internal pair's counter (the book's example)
            auto &[country, nameAndNumOfBillionaires] = (*iterator);         // Get the values by structured bindings, use & to change it (use the data in item directly). Note: nested structured bidnings are not allowed in C++17 at least
            nameAndNumOfBillionaires.second += 1;                            // Increment the internal pair's counter
        }
    }

    for (const auto &[key, value] : myMap){
        const auto &[curBillionaire, count] = value;

        cout << curBillionaire.country << " : " << count << " billionaires. Richest is "
            << curBillionaire.name << " with " << curBillionaire.dollars << " B$\n";
    }
}