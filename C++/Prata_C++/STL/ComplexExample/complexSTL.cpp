// Use complex STL functionality
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include <cctype>

using namespace std;

string &ToLowerString(string &stringToLow);
// char toLowerChar(char ch) { return tolower(ch); }
void displayString(const string &stringToPrint);

int main(int argc, char const *argv[])
{
    string words[]{"The", "dog", "saw", "the", "cat", "and", "thought", "the", "cat", "fat"};
    string wordsToAdd[]{"The", "cat", "thought","the", "cat", "perfect"};
    vector<string> wordsVect(words, words + 10);            //vector of strings (wordsVect). May be initialized this way: vector<string> wordsVect(words, words + 10);

    // 1. Complement wordsVect with wordsToAdd by going through the words
    for (auto &word : wordsToAdd)
        wordsVect.push_back(word);
    //  Or use input like this:
    //string oneWord;
    //cout << "Enter wordsVect (enter quit to quit):" << endl;
    //while (cin >> oneWord && oneWord != "quit")       //Insert by input
    //    wordsVect.push_back(oneWord);

    // 2. Print out the wordsVect
    cout << "You entered the following words:\n";
    for_each(wordsVect.begin(), wordsVect.end(), [](string &stringToPrint){cout << stringToPrint << " ";});
    cout << endl;

    // 3. Copy the wordsVect content in set, converting to lowercase and to get the alphabetic order: set is ordering input automatically
    set<string> setOfWords;
    transform(wordsVect.begin(), wordsVect.end(),
        insert_iterator<set<string>>(setOfWords, setOfWords.begin()),     // Need to use insert_iterator to adjust the size automatically
        ToLowerString);

    // Print out the words, they are stored in alphabetic order automatically and NO dublicates
    cout << endl << "Alphabetic list of words:" << endl;
    for_each(setOfWords.begin(), setOfWords.end(), displayString);
    cout << endl;

    // 3. Place words and theirs frequency in map: word as a key, int as a value
    map<const string, int> mapOfWords;      //To make string const or not const? Preliminary, no difference in processing, key becomes immutable anyway
    set<string>::iterator setIter;

    // Insert a value to the map by using key as a word as [*setIter], for example ["dog"]
    for (setIter = setOfWords.begin(); setIter != setOfWords.end(); setIter++)
        mapOfWords[*setIter] = count(wordsVect.begin(), wordsVect.end(), *setIter);     //Count the number of the word appears in the vector

    // Display the map contents: go through the set and use the index for the map to print the frequency
    cout << endl << "Word frequency:" << endl;
    for (setIter = setOfWords.begin(); setIter != setOfWords.end(); setIter++)
        cout << *setIter << ": " << mapOfWords[*setIter] << endl;

    // Display the map content by iterating on the map (output is the same as above)
    cout << endl << "Word frequency by iterating on the map:" << endl;
    for (auto mapIter = mapOfWords.begin(); mapIter != mapOfWords.end(); mapIter++)
        // cout << (*mapIter).first << ": " << mapOfWords[(*mapIter).first] << endl;
        cout << (*mapIter).first << ": " << (*mapIter).second << endl;

    return 0;
}

// Go through the string char-by-char using iterators, transform every symbol and out is the same string
string &ToLowerString(string &stringToLow){
    transform(stringToLow.begin(), stringToLow.end(), stringToLow.begin(), [](char &curChar){return tolower(curChar);});        // Use lambda for transforming chars
    return stringToLow;
}

void displayString(const string &stringToPrint){
    cout << stringToPrint << " ";
}