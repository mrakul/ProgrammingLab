//Types defined for all containers (including vector)

#include <vector>
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char const* argv[])
{
    vector<string> inputWords;
    string inWord;

    while (std::cin >> inWord && inWord != "quit")
        inputWords.push_back(inWord);

    //Iterator type
    vector<string>::iterator itWordToFind = find(inputWords.begin(), inputWords.end(), string("bonus"));

    if (itWordToFind != inputWords.end()){              //If found required
        //Reference type to the data/value (object itself)
        vector<string>::reference refToWord = *itWordToFind;    // refToWord is a reference to the required object, the same as "string & refToWord = *itWordToFind"
        refToWord = "bogus";
    }

    //Value type (object itself)
    if(!inputWords.empty())
        vector<string>::value_type firstWord = inputWords[0];
    return 0;
}
