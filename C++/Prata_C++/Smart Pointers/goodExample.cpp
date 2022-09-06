// fowl.cpp -- auto_ptr a poor choice
#include <iostream>
#include <string>
#include <memory>

int main(int argc, char const *argv[])
{
    using namespace std;
    /*** 1. Deprecated auto_ptr using ***/

    // 0. auto_ptr<string> films[5] =
    //     {
    //         auto_ptr<string>(new string("Fowl Balls")),
    //         auto_ptr<string>(new string("Duck Walks")),
    //         auto_ptr<string>(new string("Chicken Runs")),
    //         auto_ptr<string>(new string("Turkey Errors")),
    //         auto_ptr<string>(new string("Goose Eggs"))};
    // auto_ptr<string> ptrFilm;
    // ptrFilm = films[2];            // films[2] loses ownership => Segmentation fault when using films[2]


    /*** 1. unique_ptr using ***/
    unique_ptr<string> films[5] =
        {
            unique_ptr<string>(new string("Fowl Balls")),
            unique_ptr<string>(new string("Duck Walks")),
            unique_ptr<string>(new string("Chicken Runs")),
            unique_ptr<string>(new string("Turkey Errors")),
            unique_ptr<string>(new string("Goose Eggs"))};
    unique_ptr<string> ptrFilm;
    shared_ptr<string> ptrFilmShared;;
    //ptrFilm = films[2];                    //compiler prevents this assignment
    cout << "The nominees for best avian baseball film are" << endl;
    for (auto &filmPtr : films){     //Go through the pointers list: (!!!) may be used as a link only, since unique-ptr can't be copied
        //filmPtr.reset(new string{"New string"});      //Replaces the managed object and deletes the old object (!) Need to specify deleter for it?
        //filmPtr.reset();           // Deletes the old object and lose ownership (!) Need to specify deleter for it?

        cout << *filmPtr << endl;
        string *aString = filmPtr.release();   //return the pointer explicitly, release the ownership of the object
        delete aString;                        //destroy object
    }

    //cout << "The winner is " << *ptrFilm << "!\n";
    // cin.get();

    /*** 2. shared_ptr using ***/
    shared_ptr<string> films2[5] =
        {
            shared_ptr<string>(new string("Fowl Balls")),
            shared_ptr<string>(new string("Duck Walks")),
            shared_ptr<string>(new string("Chicken Runs")),
            shared_ptr<string>(new string("Turkey Errors")),
            shared_ptr<string>(new string("Goose Eggs"))};
    shared_ptr<string> ptrFilm2;

    ptrFilm2 = films2[4];       //Allowed, both points to the same area, but only the last Destructor will release memory (of the films2)
    cout << "ptrFilm2.useCount() = " << ptrFilm2.use_count()
         << " films2[4].useCount() = " << films2[4].use_count() << endl;

    ptrFilm2.reset();           //Reset the pointer, not destroying object

    cout << "ptrFilm2.useCount() = " << ptrFilm2.use_count()
         << " films2[4].useCount() = " << films2[4].use_count() << endl;

    films2[4].unique() ? cout << "Yes" : cout << "No";
    cout << (ptrFilm2.unique() ? "Yes" : "No") << endl;     //braces makes conditional operator more prioritized (meaning operator precedence)

    films2[4].reset();           //Reset the pointer, destroying the object?

    cout << "ptrFilm2.useCount() = " << ptrFilm2.use_count()
         << " films2[4].useCount() = " << films2[4].use_count() << endl;

    return 0;
}