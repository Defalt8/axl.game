#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"


int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::game;
	printf("axl.game - version %u.%u.%u  %s %s\n", axl::game::lib::VERSION.major, axl::game::lib::VERSION.minor, axl::game::lib::VERSION.patch, libType(axl::game::lib::LIBRARY_TYPE), buildType(axl::game::lib::BUILD_TYPE));
	printf("axl.util - version %u.%u.%u  %s %s\n", axl::util::lib::VERSION.major, axl::util::lib::VERSION.minor, axl::util::lib::VERSION.patch, libType(axl::util::lib::LIBRARY_TYPE), buildType(axl::util::lib::BUILD_TYPE));
	printf("axl.math - version %u.%u.%u  %s %s\n", axl::math::lib::VERSION.major, axl::math::lib::VERSION.minor, axl::math::lib::VERSION.patch, libType(axl::math::lib::LIBRARY_TYPE), buildType(axl::math::lib::BUILD_TYPE));
	printf("axl.glw - version %u.%u.%u  %s %s\n", axl::glw::lib::VERSION.major, axl::glw::lib::VERSION.minor, axl::glw::lib::VERSION.patch, libType(axl::glw::lib::LIBRARY_TYPE), buildType(axl::glw::lib::BUILD_TYPE));
	puts("----------------------------------------");
	return Assert::_num_failed_tests;
}