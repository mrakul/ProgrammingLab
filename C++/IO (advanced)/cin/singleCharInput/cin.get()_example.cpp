#include <iostream>

int main(int argc, char const* argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;

    int ct = 0;
    char ch;
    cin.get(ch);        //cin >> ch would never assign '\n' to ch, it is skipped always
    //or ch = cin.get(), so it returns int instead of the reference to the stream
    while (ch != '\n')  //or (ch = cin.get() != EOF), that is until the end of the
    {
        cout << ch;
        ct++;
        cin.get(ch);
    }
    cout << ct << endl;
    return 0;
}
