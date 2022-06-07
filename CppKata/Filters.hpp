#pragma once

#include <iosfwd>
#include <optional>

struct Filters
{
	std::optional<unsigned> minItemCount;

	static Filters parse(std::istream& is);
};
