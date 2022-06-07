#include "Filters.hpp"

#include <istream>
#include <map>
#include <regex>
#include <string>

Filters Filters::parse(std::istream& is)
{
	const std::regex filters_start{"filters: \\{"};
	std::string line1;
	while (std::getline(is, line1) && !std::regex_search(line1, filters_start))
	{
		continue;
	}

	std::string line;
	const static std::regex filter_item_regex{ "(\\w+): (\\w+)" };
	const std::regex filters_end{ "\\}" };
	std::map<std::string, std::string> filter_items;
	while (std::getline(is, line) && !std::regex_search(line, filters_end))
	{
		if (std::smatch item_match; std::regex_search(line, item_match, filter_item_regex))
		{
			filter_items.emplace(item_match[1], item_match[2]);
		}
	}

	Filters filters;
	if (const auto pos = filter_items.find("minItemCount"); pos != end(filter_items))
	{
		filters.minItemCount = std::atoi(pos->second.c_str());
	}
	return filters;
}

