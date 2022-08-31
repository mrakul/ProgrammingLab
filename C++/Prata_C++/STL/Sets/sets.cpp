// setops.cpp -- some set operations
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

int main(int argc, const char *argv[])
{
    using namespace std;
    const int N = 6;
    //Arrrays of strings
    string s1[N] = {"buffoon", "thinkers", "for", "heavy", "can", "for"};
    string s2[N] = {"metal", "any", "food", "elegant", "deliver", "for"};
    //Create two sets basing on the arrays (pointers in this case)
    set<string> A(s1, s1 + N);
    set<string> B(s2, s2 + N);

    //ostream_iterator to output data: print out string type in char type, cout as output stream, " " is a separator, which is sent after every string
    ostream_iterator<string, char> out(cout, " ");

    //Print out A and B
    cout << "Set A: ";
    copy(A.begin(), A.end(), out);
    cout << endl;
    cout << "Set B: ";
    copy(B.begin(), B.end(), out);
    cout << endl;

    //Insert a word
    A.insert("AddedWord");
    //Or use variable:
    //string s3("grungy");
    //C.insert(s3);
    copy(A.begin(), A.end(), out);
    cout << endl;

    //Check union function and print out it (not creating another set)
    cout << "Union of A and B:\n";
    set_union(A.begin(), A.end(), B.begin(), B.end(), out);
    cout << endl;

    //Check intersection function
    cout << "Intersection of A and B:\n";
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), out);
    cout << endl;

    //Check difference function
    cout << "Difference of A and B:\n";
    set_difference(A.begin(), A.end(), B.begin(), B.end(), out);
    cout << endl;

    //Set C is a new set of strings to save union of A and B
    set<string> C;
    cout << "Set C:\n";
    set_union(A.begin(), A.end(), B.begin(), B.end(),
              insert_iterator<set<string>>(C, C.begin()));      //Use insert_iterator to adjust the size of C dynamically

    //Output C set
    //copy(C.begin(), C.end(), out);
    for(auto strOut : C) cout << strOut << endl;    //Also works, despite that C is not a sequence
    cout << endl;

    //Use copy() + insert_iterator to copy to D
    set<string> D;
    copy(C.begin(), C.end(), insert_iterator<set<string>>(D, D.begin()));
    //copy(C.begin(), C.end(), D.begin());    //this doesn't work, since returns only read_only (constant) iterator (note: begin() allows change value, cbegin() doesn't allow)
    for(auto strOut : D) cout << strOut << endl;    //Also works, despite that C is not a sequence
    cout << endl;

    cout << "Showing a range:\n";
    copy(C.lower_bound("b"), C.upper_bound("i"), out);
    cout << endl;

    return 0;
}