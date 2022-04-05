#if !defined STRING_H_
#define STRING_H_
#include <iostream>
class String
{
private:
    static int objectsNumber;
    char *strPtr;
    int strLen;

public:
    //Constructors / Destructor section
    String();              // default constructor
    String(const char *s); // constructor
    String(const String &st);
    ~String();             // destructor

    int length () const { return strLen; }  //Make inline
    // Compare functions like:
    //friend bool operator<(const String &str1, const String &str2);

    //Friend functions
    friend std::ostream &operator<<(std::ostream &out,
                                    const String &str);

    //Assignment operator
    String &operator=(const String &source);
    char &operator[](int i);
    const char &operator[](int i) const;    //The last const allow to distinguish versions

    //Static function: can access only static class members
    static int numOfObjects(){return objectsNumber;}
};

#endif