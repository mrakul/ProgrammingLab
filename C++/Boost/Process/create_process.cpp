#include <string>
#include <iostream>
#include <boost/process.hpp>

using namespace boost::process;

int main(int argc, char const *argv[])
{
    ipstream pipe_stream;
    child childProc("gcc --version", std_out > pipe_stream);

    std::string line;

    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
       std::cout << line << std::endl;

    std::cout << "Test testing" << std::endl;


    std::cin.get();
    std::cin.get();

    childProc.wait();

}