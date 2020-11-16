#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include <axl.gl/lib.hpp>


int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::gl;
	printf("axl.gl - version %u.%u.%u\n", lib::version.major, lib::version.minor, lib::version.patch);
	puts("----------------------------------------");
	printf("# %d Failed!\n", Assert::_num_failed_tests);
	return Assert::_num_failed_tests;
}