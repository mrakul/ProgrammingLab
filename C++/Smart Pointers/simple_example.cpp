// smrtptrs.cpp -- using three kinds of smart pointers
#include <iostream>
#include <string>
#include <memory>
#include <string>
using std::string;
std::unique_ptr<string> demo(const char *s);

class Report
{
private:
    std::string str;

public:
    Report(const std::string s) : str(s)
    {
        std::cout << "Object created!\n";
    }
    ~Report() { std::cout << "Object deleted!\n"; }
    void comment() const { std::cout << str << "\n"; }
};

int main(int argc, char const *argv[])
{
    {
        //std::auto_ptr<Report> ps(new Report("using auto_ptr"));   //Auto is deprecated now
        //ps->comment(); // use -> to invoke a member function
    }
    {
        std::shared_ptr<Report> ps(new Report("using shared_ptr"));
        ps->comment();
    }
    {
        std::unique_ptr<Report> ps(new Report("using unique_ptr"));
        ps->comment();
    }

    std::unique_ptr<string> ps;
    ps = demo("Uniquely special");      //This is working well since demo() returns temporary object (rvalue)

    return 0;
}

std::unique_ptr<string> demo(const char *s)
{
    std::unique_ptr<string> temp(new string(s));
    return temp;
}