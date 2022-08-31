#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const* argv[])
{
    string sentence("That is a funny hat.");
    string substring("hat");
    size_t subPos1 = sentence.find(substring);                  // Find from the beginning
    size_t subPos2 = sentence.find(substring, subPos1 + 1);     // Find from the second symbol

    string subStr(sentence.substr(5, 10));                      //Set to "is a funny" (move constructor is used in this case)

    if (subPos1 == string::npos)
        cout << "Not found\n";
    if (subPos2 == string::npos)
        cout << "Not found\n";

    //rfind() example: find from the right
    subPos1 = sentence.rfind(substring);                  // Find from the end

    //find_first_of(): find the first occurence of any symbol from the passed string
    //Note: find_last_of() is the same from the right.
    //find_first_not_of() and find_last_not_of() - the same excepting that finding the first symbol not in the substring
    sentence = "That is a funny hat.";
    substring = "fluke";
    subPos1 = sentence.find_first_of(substring);                    // sets subPos1 to 10
    subPos2 = sentence.find_first_of("fat");                        // sets subPos2 to 2


    //Compare methods
    string s1("bellflower");
    string s2("bell");
    string s3("cat");
    int compare1 = s1.compare(s3);               // compare1 is < 0
    int compare2 = s1.compare(s2);               // compare2 is > 0
    cout << compare1 << " " << compare2 << endl;

    //Compare with range specified
    int compare3 = s1.compare(0, 4, s2);         // compare3 is 0: 4 symbols from the 0 symbol
    compare3 = compare3;                         // Make compiler happy
    //Compare with range specified for both
    s1 = "stout boar";
    s2 = "mad about ewe";
    int compare4 = s1.compare(2, 3, s2, 6, 3);        // a3 is 0
    compare4 = compare4;                         // Make compiler happy

    //append() method
    string test("The");
    test.append("ory");                               // test is "Theory"
    test.append(3, '!');                              // test is "Theory!!!"
    test.insert(test.begin() + 3, ',');               //Insert 3 symbols
    test.insert(test.size(), "ADDITION");

    //assign() method. Allows move semantics for rvalues since C++11
    string test;
    string stuff("set tubs clones ducks");
    test.assign(stuff, 1, 5);           // test is "et tu"
    test.assign(6, '#');                // test is "######"

    //Other methods: erase(), replace(), copy(), swap

    return 0;
}
