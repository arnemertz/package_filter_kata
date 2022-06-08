#include "process.hpp"

#include <istream>

#include "Filters.hpp"
#include "Package.hpp"

std::string process(std::istream& is) {
    const auto filters = Filters::parse(is);
    const auto packages = Package::parse(is);

    std::string result;
    return result;
}

