#include "pch.h"
#include "../CppKata/process.hpp"
#include "../CppKata/Filters.hpp"

#include <string>
#include <sstream>

using namespace std::literals;
TEST(package_filter, DISABLED_readme_example_works)
{
	const auto readme_input =
R"(filters: {
    minPackageWeight: "2kg",
    maxPackageWeight: "15kg",
    minItemWeight: "200g",
    maxItemWeight: "5kg",
    minItemCount: 2,
    maxItemCount: 50,
    minPackageCount: 1,
    maxPackageCount: 50
},
packages: [
    {itemName: "screwDriver", itemWeight: "400g", itemCount: 5, packageCount: 12},
    {itemName: "powerDrill", itemWeight: "2500g", packageCount: 5},
    {itemName: "screw", itemCount: 500, packageCount: 10, packageWeight: "500g"},
    {itemID: "DA456-32F", packageWeight: "4000g", itemWeight: "800g"},
    {itemWeight: "800g", itemCount: 6, packageWeight: "5kg", packageCount: 2, itemID: "FIA-77-g64x"},
    {itemCount: 20, itemName: "gummy bears", packageCount: 50},
    {itemCount: 10, itemWeight: "2300g", itemName: "powerDrill", powerUse="1400W"}
]
)"s;

	const auto readme_output =
R"(totalItemCount: 73, totalPackageCount: 15, totalWeight: "38000g")"s;

	std::stringstream sstr{ readme_input };
	ASSERT_EQ(process(sstr), readme_output);
}

TEST(package_filter, parse_filters_parses_counts)
{
    const auto filter_string =
R"(R"(filters: {
    minItemCount: 2,
    maxItemCount: 50,
    minPackageCount: 1,
    maxPackageCount: 50
},
)";

	std::stringstream sstr{ filter_string };
    const auto filters = Filters::parse(sstr);
    ASSERT_TRUE(filters.minItemCount);
    ASSERT_EQ(filters.minItemCount, 2);
}
