#include "pch.h"
#include "../CppKata/process.hpp"
#include "../CppKata/Filters.hpp"
#include "../CppKata/Package.hpp"

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
R"(filters: {
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
    ASSERT_TRUE(filters.maxItemCount);
    ASSERT_EQ(filters.maxItemCount, 50);
    ASSERT_TRUE(filters.minPackageCount);
    ASSERT_EQ(filters.minPackageCount, 1);
    ASSERT_TRUE(filters.maxPackageCount);
    ASSERT_EQ(filters.maxPackageCount, 50);
}

TEST(package_filter, parse_packages)
{
    const auto packages_string =
R"(packages: [
    {itemName: "screwDriver", itemWeight: "400g", itemCount: 5, packageCount: 12},
    {itemName: "powerDrill", itemWeight: "2500g", packageCount: 5},
    {itemName: "screw", itemCount: 500, packageCount: 10, packageWeight: "500g"},
    {itemID: "DA456-32F", packageWeight: "4000g", itemWeight: "800g"},
    {itemWeight: "800g", itemCount: 6, packageWeight: "5kg", packageCount: 2, itemID: "FIA-77-g64x"},
    {itemCount: 20, itemName: "gummy bears", packageCount: 50},
    {itemCount: 10, itemWeight: "2300g", itemName: "powerDrill", powerUse="1400W"}
]
)";

    std::stringstream sstr{ packages_string };
    const auto packages = Package::parse(sstr);
    ASSERT_EQ(packages.size(), 7);
    EXPECT_EQ(packages[0].itemCount, 5);
    EXPECT_EQ(packages[0].packageCount, 12);
    EXPECT_EQ(packages[3].itemCount, 1);
    EXPECT_EQ(packages[3].packageCount, 1);
}

TEST(package_filter, apply_package_filter)
{
    Filters filters{};
    filters.maxItemCount = 4;
    filters.minPackageCount = 3;

    const auto filter_predicate = filters.predicate();
    const Package within_limits{ 3, 6 };
    EXPECT_TRUE(filter_predicate(within_limits));

    const Package too_many_items{ 5000, 6 };
    EXPECT_FALSE(filter_predicate(too_many_items));

    const Package not_enough_packages{ 3, 2 };
    EXPECT_FALSE(filter_predicate(not_enough_packages));
}