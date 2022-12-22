#ifndef TABTENN_H_
#define TABTENN_H_
#include <string>
#include <iostream>

using std::string;

class TableTennPlayer
{
    private:
        string firstName;
        string lastName;
        bool hasTable;

    public:
        TableTennPlayer();
        TableTennPlayer(const TableTennPlayer &copyPlayer);
        TableTennPlayer(const string &fName, const string &lName = "NoName", bool tabled = false);      // default values can be specified only here, in the header
        virtual ~TableTennPlayer();

        //Functionality
        virtual void showName() const;                              // "virtual" keyword automatically makes this function virtual in the derived class
        bool HasTable() const {return hasTable;}
        void setTable(bool isTabled){hasTable = isTabled;}          // Inline call
        //virtual void showType(void) const = 0;                    // Pure virtual function => class can't have instances of the class
        TableTennPlayer &operator=(TableTennPlayer & tennPlayer);
};

#endif