#pragma once

#include <iosfwd>
#include <optional>

#include "Package.hpp"

struct Filters
{
	std::optional<unsigned> minItemCount;
	std::optional<unsigned> maxItemCount;
	std::optional<unsigned> minPackageCount;
	std::optional<unsigned> maxPackageCount;

	static Filters parse(std::istream& is);

	[[nodiscard]] auto predicate() const
	{
		return [*this](Package const& package)
		{
			if (minItemCount && package.itemCount < minItemCount) return false;
			if (maxItemCount && package.itemCount > maxItemCount) return false;
			if (minPackageCount && package.packageCount < minPackageCount) return false;
			if (maxPackageCount && package.packageCount > maxPackageCount) return false;
			return true;
		};
	}
};
