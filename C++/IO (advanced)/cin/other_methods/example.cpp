#include <iostream>

int main(int argc, char const* argv[])
{
    using std::cin;
    char gross[10];
    char score[10];

    //cin.read() example: cin reads the data as it is and not append the NULL symbol at the end. Its intention is more for files, not the keyboard input
    cin.read(gross, 10).read(score, 10);

    //cin.gcount() returns the number of unformatted data read: get(), getline(), read(), ignore()
    std::cout << "Number of read characters last time is: " << cin.gcount() << std::endl;

    //cin.peek() example: the next symbol of the buffer can be checked, but the symbol is left in the buffer
    char great_input[80];
    char ch;
    int i = 0;
    while ((ch = cin.peek()) != '.' && ch != '\n'){
        cin.get(great_input[i++]);
        std::cout << ch;
    }
    great_input[i] = '\0';

    //cin.putback() example: read the next symbol from the buffer, but putbach another symbol
    // Note: Using peek() is like using get() to read a character and then using putback() to place
    // the character back in the input stream. However, putback()
    cin.get(ch);
    cin.putback('#');   //insert '#' instead of '.' to the buffer

    //Read the rest of the line (after period, for example): for the string "aaaaaaaaaabbbbbbbbbbccccccc.ddd" -> ".ddd" is the rest
    while ((ch = cin.get()) != EOF){
        std::cout << ch;
    }

    return 0;
}
