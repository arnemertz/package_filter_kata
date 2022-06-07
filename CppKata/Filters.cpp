#include "Filters.hpp"

#include <istream>
#include <map>
#include <regex>
#include <string>

using FilterItems = std::map<std::string, std::string, std::less<>>;

namespace {
	void ignoreLinesUntilFilterStart(std::istream& is)
	{
		const std::regex filters_start{ "filters: \\{" };
		std::string line1;
		while (std::getline(is, line1) && !std::regex_search(line1, filters_start))
		{
			continue;
		}
	}

	auto parseFilterItems(std::istream& is)
	{
		const std::regex filter_item_regex{ "(\\w+): (\\w+)" };
		const std::regex filters_end{ "\\}" };

		FilterItems filter_items;
		std::string line;
		while (std::getline(is, line) && !std::regex_search(line, filters_end))
		{
			if (std::smatch item_match; std::regex_search(line, item_match, filter_item_regex))
			{
				filter_items.emplace(item_match[1], item_match[2]);
			}
		}
		return filter_items;
	}

	void setFilterFromItem(std::optional<unsigned>& filter, FilterItems const& filter_items, std::string_view const& name)
	{
		if (const auto pos = filter_items.find(name); pos != end(filter_items))
		{
			filter = std::atoi(pos->second.c_str());
		}
	}

} // anonymous namespace


Filters Filters::parse(std::istream& is)
{
	ignoreLinesUntilFilterStart(is);
	const auto filter_items = parseFilterItems(is);

	Filters filters;
	setFilterFromItem(filters.minItemCount, filter_items, "minItemCount");
	return filters;
}

