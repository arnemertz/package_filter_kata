#include "Package.hpp"

#include <istream>
#include <map>
#include <regex>

namespace
{
	void ignoreLinesUntilPackagesStart(std::istream& is)
	{
		const std::regex packages_start{ "packages: \\[" };
		std::string line1;
		while (std::getline(is, line1) && !std::regex_search(line1, packages_start))
		{
			continue;
		}
	}

	using PackageAttributes = std::map<std::string, std::string, std::less<>>;

	void setPackageAttr(unsigned& attribute, PackageAttributes const& package_attributes, std::string_view const& name)
	{
		if (const auto pos = package_attributes.find(name); pos != end(package_attributes))
		{
			attribute = std::atoi(pos->second.c_str());
		}
	}

	PackageAttributes extractPackageAttributes(std::string const& line)
	{
		const auto start = std::find(line.begin(), line.end(), '{');
		const auto end = std::find(start, line.end(), '}');
		const auto key_value_regex = std::regex{ "(\\w+): (\\w+)" };

		PackageAttributes package_attributes;
		for (auto rit = std::sregex_iterator{ start, end, key_value_regex }; rit != std::sregex_iterator{}; ++rit)
		{
			const auto match = *rit;
			package_attributes.emplace(match[1], match[2]);
		}
		return package_attributes;
	}

	Package parsePackage(std::string const& line)
	{
		const auto package_attributes = extractPackageAttributes(line);

		Package package;
		setPackageAttr(package.itemCount, package_attributes, "itemCount");
		setPackageAttr(package.packageCount, package_attributes, "packageCount");
		return package;
	}

} // anonymous namespace


std::vector<Package> Package::parse(std::istream& is)
{
	ignoreLinesUntilPackagesStart(is);

	std::string line;
	std::vector<Package> packages;
	while (std::getline(is, line) && (line.find(']') == std::string::npos))
	{
		packages.emplace_back(parsePackage(line));
	}

	return packages;
}
