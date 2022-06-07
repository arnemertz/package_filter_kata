#include <iostream>
#include <fstream>
#include "../CppKata/process.hpp"

int main()
{
    std::ifstream input_file("input.txt");
    if (!input_file)
    {
        std::cerr << "Could not open input.txt!";
    }
    std::cout << process(input_file);
}
