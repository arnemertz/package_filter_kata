#pragma once

#include <iosfwd>
#include <optional>

struct Filters
{
	std::optional<unsigned> minItemCount;
	std::optional<unsigned> maxItemCount;
	std::optional<unsigned> minPackageCount;
	std::optional<unsigned> maxPackageCount;

	static Filters parse(std::istream& is);
};
