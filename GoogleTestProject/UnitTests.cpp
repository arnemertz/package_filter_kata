#include "pch.h"
#include "../CppKata/process.hpp"

#include <string>
#include <sstream>

using namespace std::literals;
TEST(process, prints_hello_world)
{
	const auto sample_input =
		"line 1\n"
		"other line\n"
		"line 3\n"
	""s;
	std::stringstream sstr{sample_input};
	ASSERT_EQ(process(sstr), "lol"s);
}
