#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include "rtti.h"

Grand *GetOne();

int main()
{
    std::srand(std::time(0));
    Grand *pg;
    Superb *ps;
    Magnificent *pm;

    for (int i = 0; i < 5; i++){
        pg = GetOne();
        pg->Speak();
        cout << "Now processing type " << typeid(*pg).name() << ".\n";
        //Only Superb and Magnificent may be upcasted to Superb, so the Say() function may be called,
        //which is defined in Superb class initially
        //(note: actually, a pointer to Grand is downcasted to Superb, if it is allowed, that is an object IS Superb, or Magnificent as Is-A Superb)
        // Note: for references bad_cast exception is used
        if ((ps = dynamic_cast<Superb *>(pg))){
            ps->Say();

            if (((pm = dynamic_cast<Magnificent *>(pg))))
                pm->Test();
            if (typeid(Magnificent) == typeid(*pg))
                cout << "This is Magnificent object!" << endl;
        }
    }

    return 0;
}

Grand *GetOne() // generate one of three kinds of objects randomly
{
    Grand *p;
    switch (std::rand() % 3)
    {
    case 0:
        p = new Grand(std::rand() % 100);
        break;
    case 1:
        p = new Superb(std::rand() % 100);
        break;
    case 2:
        p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26);
        break;
    }
    return p;
}