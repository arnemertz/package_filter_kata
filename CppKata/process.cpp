#include "process.hpp"

#include <algorithm>
#include <istream>
#include <numeric>
#include <sstream>

#include "Filters.hpp"
#include "Package.hpp"

std::string process(std::istream& is) {
    const auto filters = Filters::parse(is);
    const auto packages = Package::parse(is);

    std::vector<Package> filteredPackages;
    std::copy_if(
        packages.begin(), 
        packages.end(), 
        std::back_inserter(filteredPackages), 
        filters.predicate()
    );

    const auto totalPackageCount = std::accumulate(
        filteredPackages.begin(),
        filteredPackages.end(),
        0u,
        [](unsigned count, Package const& package)
		{
			return count + package.packageCount;
		}
    );
    const auto totalItemCount = std::accumulate(
        filteredPackages.begin(),
        filteredPackages.end(),
        0u,
        [](unsigned count, Package const& package)
		{
    		return count + (package.itemCount * package.packageCount);
		}
    );

	std::stringstream result;
    result << "totalItemCount: " << totalItemCount << ", totalPackageCount: " << totalPackageCount;
    return result.str();
}

