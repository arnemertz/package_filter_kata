#include "process.hpp"

#include <istream>

std::string process(std::istream& is) {
    std::string result;
    std::string line;
    while (std::getline(is, line) && !line.empty())
    {
        result.push_back(line[0]);
    }
    return result;
}

