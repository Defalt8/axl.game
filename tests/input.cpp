#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include "KeyCodeToStr.hpp"
#include <axl.game/Application.hpp>
#include <axl.game/input/Keyboard.hpp>
#include <axl.game/input/Mouse.hpp>
#include <axl.game/input/Touch.hpp>

void onKey(axl::game::input::KeyCode key_code, bool is_down)
{
	printf("%s %s\n", CStrKeyCode(key_code), is_down ? "Down" : "Up");
}

void onMouse(axl::game::input::MouseButton button, int x, int y, bool is_down)
{
	const char* str_button = "";
	switch(button)
	{ using namespace axl::game::input;
		case MBTN_LEFT: str_button = "Left"; break;
		case MBTN_RIGHT: str_button = "Right"; break;
		case MBTN_MIDDLE: str_button = "Middle"; break;
		case MBTN_EXTRA: str_button = "Extra1"; break;
	}
	printf("Mouse%4s (%3d, %3d) - %s\n", (is_down ? "Down" : "Up  "), x, y, str_button);
}

void onMouseMove(int x, int y)
{
	using namespace axl::game::input;
	if(Mouse::isButtonDown(MBTN_LEFT))
		printf("MouseMove (%3d, %3d)\r", x, y);
}

void onMouseWheel(bool is_vertical, int delta, int x, int y)
{
	using namespace axl::game::input;
	printf("MouseWheel %s  Delta(%3d) X,Y(%3d, %3d)\n", is_vertical ? "Vertical" : "Horizontal", delta, x, y);
}

void terminating()
{
	using namespace axl::game::input;
	Keyboard::Listener::release();
	Mouse::Listener::release();
}

////
///
//

int main(int argc, char *argv[])
{
	std::atexit(terminating);
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::game;
	printf("axl.game - version %u.%u.%u  %s %s\n", axl::game::lib::VERSION.major, axl::game::lib::VERSION.minor, axl::game::lib::VERSION.patch, libType(axl::game::lib::LIBRARY_TYPE), buildType(axl::game::lib::BUILD_TYPE));
	printf("axl.util - version %u.%u.%u  %s %s\n", axl::util::lib::VERSION.major, axl::util::lib::VERSION.minor, axl::util::lib::VERSION.patch, libType(axl::util::lib::LIBRARY_TYPE), buildType(axl::util::lib::BUILD_TYPE));
	printf("axl.math - version %u.%u.%u  %s %s\n", axl::math::lib::VERSION.major, axl::math::lib::VERSION.minor, axl::math::lib::VERSION.patch, libType(axl::math::lib::LIBRARY_TYPE), buildType(axl::math::lib::BUILD_TYPE));
	printf("axl.glw - version %u.%u.%u  %s %s\n", axl::glw::lib::VERSION.major, axl::glw::lib::VERSION.minor, axl::glw::lib::VERSION.patch, libType(axl::glw::lib::LIBRARY_TYPE), buildType(axl::glw::lib::BUILD_TYPE));
	puts("----------------------------------------");
	printf("Has-Keyboard: %s\n", input::Keyboard::isPresent() ? "yes" :"no");
	printf("Has-Mouse: %s\n", input::Mouse::isPresent() ? "yes" :"no");
	printf("Has-Touch: %s\n", input::Touch::isPresent() ? "yes" :"no");
	if(input::Keyboard::isPresent())
	{
		input::Keyboard::Listener::onKey = onKey;;
		printf("Keyboard-Listener-initialized: %s\n", input::Keyboard::Listener::init() ? "yes" : "no");
	}
	if(input::Mouse::isPresent())
	{
		input::Mouse::setCursorPosition(100,100);
		input::Mouse::Listener::onMouse = onMouse;
		input::Mouse::Listener::onMouseMove = onMouseMove;
		input::Mouse::Listener::onMouseWheel = onMouseWheel;
		printf("Mouse-Listener-initialized: %s\n", input::Mouse::Listener::init() ? "yes" : "no");
	}
	while(!Application::IsQuitting)
	{
		if(Application::pollEvent()) continue;
		Application::sleep(15);
	}
	puts("----------------------------------------");
	printf("# %d Failed!\n", Assert::_num_failed_tests);
	return Assert::_num_failed_tests;
}