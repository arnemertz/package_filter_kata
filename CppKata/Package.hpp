#pragma once

#include <iosfwd>
#include <vector>

struct Package
{
	unsigned itemCount = 1;
	unsigned packageCount = 1;

	static std::vector<Package> parse(std::istream& is);
};