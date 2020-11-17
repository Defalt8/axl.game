#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"


int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::gl;
	printf("axl.gl - version %u.%u.%u  %s %s\n", lib::version.major, lib::version.minor, lib::version.patch, LIB_TYPE, DEBUG_REL);
	printf("axl.glw - version %u.%u.%u  %s %s\n", axl::glw::lib::version.major, axl::glw::lib::version.minor, axl::glw::lib::version.patch, axlglwLibraryType(), axl::glw::lib::debug ? "Debug" : "Release");
	puts("----------------------------------------");
	printf("# %d Failed!\n", Assert::_num_failed_tests);
	return Assert::_num_failed_tests;
}