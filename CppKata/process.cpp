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

    struct Results
    {
        unsigned totalPackageCount = 0u;
        unsigned totalItemCount = 0u;
    };

    const auto [totalPackageCount, totalItemCount] = std::accumulate(
        begin(packages),
        end(packages),
        Results{},
        [valid = filters.predicate()](auto results, auto const& package)
        {
	        if (valid(package))
	        {
		        results.totalPackageCount += package.packageCount;
                results.totalItemCount += package.packageCount * package.itemCount;
	        }
            return results;
        }
    );

	std::stringstream result;
    result << "totalItemCount: " << totalItemCount << ", totalPackageCount: " << totalPackageCount;
    return result.str();
}

