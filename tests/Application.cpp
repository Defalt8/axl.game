#include <cstdio>
#include <cstdlib>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.gl/Application.hpp>
#include <windows.h>


int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::gl;
	using namespace axl::math;
	printf("axl.gl - version %u.%u.%u  %s %s\n", lib::version.major, lib::version.minor, lib::version.patch, LIB_TYPE, DEBUG_REL);
	puts("----------------------------------------");
	Vec2<int> display_size, pointer_position;
	display_size = Application::getCurrentDisplaySize();
	printf("display_size: (%dx%d)\n", display_size.x, display_size.y);
	Assertv(display_size.x == GetSystemMetrics(SM_CXSCREEN), verbose);
	Assertv(display_size.y == GetSystemMetrics(SM_CYSCREEN), verbose);
	Assertv(Application::IsQuitting == false, verbose);
	pointer_position = Application::getCursorPosition();
	printf("pointer_position: (%dx%d)\n", pointer_position.x, pointer_position.y);
	Application::setCursorPosition(display_size.x/2,display_size.y/2);
	pointer_position = Application::getCursorPosition();
	printf("pointer_position: (%dx%d)\n", pointer_position.x, pointer_position.y);
	Assertv(pointer_position.x == display_size.x/2, verbose);
	Assertv(pointer_position.y == display_size.y/2, verbose);
	Application::pollEvent();
	Application::pollEvents();
	Application::quit(0);
	Application::pollEvents();
	Assertv(Application::IsQuitting == true, verbose);
	puts("----------------------------------------");
	printf("# %d Failed!\n", Assert::_num_failed_tests);
	return Assert::_num_failed_tests;
}