#include <string>
#include <cctype>
#include <iostream>

using std::string;

void stringToUp(string &);

int main(int argc, char const *argv[])
{
    string stringProcessed{"small letter initially"};
    stringToUp(stringProcessed);

    std::cout << "Uppered string: " << stringProcessed << std::endl;

    return 0;
}

void stringToUp(string &stringProcessed){
    for(auto &aChar : stringProcessed)
      aChar = static_cast<char>(std::toupper(static_cast<unsigned char>(aChar)));
}
