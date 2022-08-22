#include <string>
#include <iostream>

using namespace std;

void CopyFoo(string text) {}                //Pass by value
void CopyRefFoo(const string& text) {}      //Pass by reference
void MoveFoo(string&& text) {}              // Rvalue reference

int main(int argc, char const *argv[])
{
    string text{"some text"};

    CopyRefFoo(text);
    CopyFoo(text);

    // MoveFoo(text); // compile error: "an rvalue reference cannot be bound to an lvalue"
    MoveFoo("another text");
    //MoveFoo(move(text));

    string text2{move(text)};       //If text is const, then text is copied. If non-const, then text is moved as text2

    //Print out the texts: test2 became text
    cout << text << " -> " << text.size() << endl;
    cout << text2 << " -> " << text2.size() << endl;

    int a{5};
    int b{move(a)};
    //a == 5, b == 5 in this case
    cout << "a: " << a << " b: " << b << endl;

    return EXIT_SUCCESS;
}