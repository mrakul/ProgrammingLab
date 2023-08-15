#include <iostream>
#include <string>
#include <regex>

struct OuterStructure{
    struct {
        int a{0};
        int b{0};
    } InnerStructure;
};

struct OuterStructure2{
    struct InnerStructure2{
        int a{0};
        int b{0};
    };
};

int main(int argc, char const *argv[])
{
    // Regex test
    static const std::regex regexString(R"(abc\w*)");                     // Starting with "abc", then any alphanumeric character [A-Za-z0-9_]
    static const std::regex regexString2(R"(abc.*\d)");                   // Starting with "abc", then any symbols, ended with number
    static const std::regex regexString3(R"(abc[\d|\w])");                // Starting with "abc", followed by only one digit or alphanumeric character
    static const std::regex regexString4(R"(abc[\d|\w]*)");               // Starting with "abc", followed by any number of digits or alphanumeric characters
    static const std::regex regexString5(R"(abc[\d|\w]*Z)");              // Starting with "abc", followed by any number of digits or alphanumeric characters, ended with Z

    // Regex calls
    std::regex_match("zabcdef3d", regexString) ? (std::cout << "Matched\n") : (std::cout << "Not Matched\n");
    std::regex_match("abcdef3a", regexString2) ? (std::cout << "Matched\n") : (std::cout << "Not Matched\n");
    std::regex_match("abcdef5", regexString2) ? (std::cout << "Matched\n") : (std::cout << "Not Matched\n");
    std::regex_match("abc3", regexString3) ? (std::cout << "Matched\n") : (std::cout << "Not Matched\n");
    std::regex_match("abcdef", regexString4) ? (std::cout << "Matched\n") : (std::cout << "Not Matched\n");
    std::regex_match("abcdef", regexString5) ? (std::cout << "Matched\n") : (std::cout << "Not Matched\n");
                                                                        // IP regex: ^([0-9]{1,3}.){3}([0-9]{1,3})$
    // Nested Structures testing
    OuterStructure myStruct;
    myStruct.InnerStructure.a = 4;
    OuterStructure2 myStruct2;
    reinterpret_cast<OuterStructure2::InnerStructure2*>(&myStruct2)->a = 7;

    // Printing
    uint32_t hexToPrint = 255;
    printf("%#010x\n", hexToPrint);                   // Max 10 symbols including 0x (specified by #) and prepended by 0
    printf("0x%08x\n", hexToPrint);                   // Max 8 symbols and prepended by 0, "0x" added manually
    printf("0x%02X\n", hexToPrint);                   // %02X = Max 2 symbols and prepended by 0, "0x" added manually. X to use large letters

    // Char multiplication test
    char myLetter = 'A';
    std::cout << "myLetter: " << std::hex << myLetter << std::endl;
    std::cout << "myLetter + 3: " << static_cast<char>(myLetter + 3)<< std::endl;

    return 0;
}