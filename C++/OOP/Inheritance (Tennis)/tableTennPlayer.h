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
        TableTennPlayer(const string &fName, const string &lName = "NoName", bool tabled = false);
        virtual ~TableTennPlayer(){std::cout << "Base class destructor" << std::endl;};

        //Functionality
        virtual void showName() const;      //virtual automatically makes this function virtual in the derived class
        bool HasTable() const {return hasTable;}
        void setTable(bool isTabled){hasTable = isTabled;}  //Inline call
};

#endif