#include <iostream>

int main(int argc, char const *argv[])
{
    using std::cout;
    struct dat
    {
        short a;
        short b;
    };

    long value = 0xA224B118;
    dat *pd = reinterpret_cast<dat *>(&value);
    cout << std::hex << pd->a; // display first 2 bytes of value
    return 0;
}
