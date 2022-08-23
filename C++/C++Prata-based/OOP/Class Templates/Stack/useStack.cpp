#include "stack.h"
#include <string>
#include <iostream>

using std::string;

// Test class to test templateness
class Man
{
private:
    string name;
    int age;

public:
    Man() {}
    Man(string curName, int curAge) : name(curName), age(curAge) {}
    ~Man() {}
    void setName(string nameToSet) { name = nameToSet; }
    friend std::ostream &operator<<(std::ostream &outStream, const Man &outMan);
};

// for Man class
std::ostream &operator<<(std::ostream &outStream, const Man &outMan)
{
    std::cout << "Man's name: " << outMan.name << " Years old: " << outMan.age << std::endl;
    return outStream;
}

int main(int argc, char const *argv[])
{
    Stack<Man> people;
    string curName;
    int curAge;

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Input the name: ";
        std::cin >> curName;
        std::cout << "Input the age: ";
        std::cin >> curAge;

        // Create local Man,  construct it using local values and push to the stack
        Man curMan{curName, curAge};
        people.push(curMan);
        std::cout << "Added person ->";
        std::cout << curMan;
    }
    Man curMan; //another one curMan
    // pop the last value and print it
    people.pop(curMan);
    std::cout << curMan;
    people.pop(curMan);
    std::cout << curMan;
    people.pop(curMan);
    std::cout << curMan;

    return 0;
}
