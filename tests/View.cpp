#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.gl/Application.hpp>
#include <axl.gl/View.hpp>
#include <axl.gl/KeyCodes.hpp>

const char* CStrKeyCode(axl::gl::KeyCode key_code)
{
	using namespace axl::gl;
	switch (key_code)
	{
		case KEY_LBUTTON: return "KEY_LBUTTON";
		case KEY_RBUTTON: return "KEY_RBUTTON";
		case KEY_CANCEL: return "KEY_CANCEL";
		case KEY_MBUTTON: return "KEY_MBUTTON";
		case KEY_BACK: return "KEY_BACK";
		case KEY_TAB: return "KEY_TAB";
		case KEY_CLEAR: return "KEY_CLEAR";
		case KEY_RETURN: return "KEY_RETURN";
		case KEY_SHIFT: return "KEY_SHIFT";
		case KEY_LSHIFT: return "KEY_LSHIFT";
		case KEY_RSHIFT: return "KEY_RSHIFT";
		case KEY_CONTROL: return "KEY_CONTROL";
		case KEY_LCONTROL: return "KEY_LCONTROL";
		case KEY_RCONTROL: return "KEY_RCONTROL";
		case KEY_ALT: return "KEY_ALT";
		case KEY_LALT: return "KEY_LALT";
		case KEY_RALT: return "KEY_RALT";
		case KEY_LCMD: return "KEY_LCMD";
		case KEY_RCMD: return "KEY_RCMD";
		case KEY_PAUSE: return "KEY_PAUSE";
		case KEY_CAPITAL: return "KEY_CAPITAL";
		case KEY_ESCAPE: return "KEY_ESCAPE";
		case KEY_SPACE: return "KEY_SPACE";
		case KEY_PAGEUP: return "KEY_PAGEUP";
		case KEY_PAGEDOWN: return "KEY_PAGEDOWN";
		case KEY_END: return "KEY_END";
		case KEY_HOME: return "KEY_HOME";
		case KEY_LEFT: return "KEY_LEFT";
		case KEY_UP: return "KEY_UP";
		case KEY_RIGHT: return "KEY_RIGHT";
		case KEY_DOWN: return "KEY_DOWN";
		case KEY_SELECT: return "KEY_SELECT";
		case KEY_EXEC: return "KEY_EXEC";
		case KEY_SNAPSHOT: return "KEY_SNAPSHOT";
		case KEY_INSERT: return "KEY_INSERT";
		case KEY_DELETE: return "KEY_DELETE";
		case KEY_HELP: return "KEY_HELP";
		case KEY_0: return "0";
		case KEY_1: return "1";
		case KEY_2: return "2";
		case KEY_3: return "3";
		case KEY_4: return "4";
		case KEY_5: return "5";
		case KEY_6: return "6";
		case KEY_7: return "7";
		case KEY_8: return "8";
		case KEY_9: return "9";
		case KEY_A: return "A";
		case KEY_B: return "B";
		case KEY_C: return "C";
		case KEY_D: return "D";
		case KEY_E: return "E";
		case KEY_F: return "F";
		case KEY_G: return "G";
		case KEY_H: return "H";
		case KEY_I: return "I";
		case KEY_J: return "J";
		case KEY_K: return "K";
		case KEY_L: return "L";
		case KEY_M: return "M";
		case KEY_N: return "N";
		case KEY_O: return "O";
		case KEY_P: return "P";
		case KEY_Q: return "Q";
		case KEY_R: return "R";
		case KEY_S: return "S";
		case KEY_T: return "T";
		case KEY_U: return "U";
		case KEY_V: return "V";
		case KEY_W: return "W";
		case KEY_X: return "X";
		case KEY_Y: return "Y";
		case KEY_Z: return "Z";
		case KEY_NUMPAD0: return "KEY_NUMPAD0";
		case KEY_NUMPAD1: return "KEY_NUMPAD1";
		case KEY_NUMPAD2: return "KEY_NUMPAD2";
		case KEY_NUMPAD3: return "KEY_NUMPAD3";
		case KEY_NUMPAD4: return "KEY_NUMPAD4";
		case KEY_NUMPAD5: return "KEY_NUMPAD5";
		case KEY_NUMPAD6: return "KEY_NUMPAD6";
		case KEY_NUMPAD7: return "KEY_NUMPAD7";
		case KEY_NUMPAD8: return "KEY_NUMPAD8";
		case KEY_NUMPAD9: return "KEY_NUMPAD9";
		case KEY_MULTIPLY: return "KEY_MULTIPLY";
		case KEY_ADD: return "KEY_ADD";
		case KEY_SEPARATOR: return "KEY_SEPARATOR";
		case KEY_SUBTRACT: return "KEY_SUBTRACT";
		case KEY_DECIMAL: return "KEY_DECIMAL";
		case KEY_DIVIDE: return "KEY_DIVIDE";
		case KEY_F1: return "KEY_F1";
		case KEY_F2: return "KEY_F2";
		case KEY_F3: return "KEY_F3";
		case KEY_F4: return "KEY_F4";
		case KEY_F5: return "KEY_F5";
		case KEY_F6: return "KEY_F6";
		case KEY_F7: return "KEY_F7";
		case KEY_F8: return "KEY_F8";
		case KEY_F9: return "KEY_F9";
		case KEY_F10: return "KEY_F10";
		case KEY_F11: return "KEY_F11";
		case KEY_F12: return "KEY_F12";
		case KEY_F13: return "KEY_F13";
		case KEY_F14: return "KEY_F14";
		case KEY_F15: return "KEY_F15";
		case KEY_F16: return "KEY_F16";
		case KEY_F17: return "KEY_F17";
		case KEY_F18: return "KEY_F18";
		case KEY_F19: return "KEY_F19";
		case KEY_F20: return "KEY_F20";
		case KEY_F21: return "KEY_F21";
		case KEY_F22: return "KEY_F22";
		case KEY_F23: return "KEY_F23";
		case KEY_F24: return "KEY_F24";
		case KEY_NUMLOCK: return "KEY_NUMLOCK";
		case KEY_SCROLL: return "KEY_SCROLL";
	}
	return "KEY_UNKNOWN";
}

class MyView : public axl::gl::View
{
	public:
		MyView(const axl::utils::WString& title_, const axl::math::Vec2<int>& position_, const axl::math::Vec2<int>& size_, const Cursor& cursor_ = View::DefaultCursor) :
			axl::gl::View(title_, position_, size_, cursor_)
		{}
		bool onCreate()
		{
			printf("Event.onCreate\n");
			return axl::gl::View::onCreate();
		}
		void onDestroy()
		{
			printf("Event.onDestroy\n");
			axl::gl::Application::quit(0);
			axl::gl::View::onDestroy();
		}
		void onMove(int x, int y)
		{
			axl::gl::View::onMove(x, y);
			printf("Event.onMove: %4d, %4d\n", x, y);
		}
		void onSize(int w, int h)
		{
			axl::gl::View::onSize(w, h);
			printf("Event.onSize: %4d, %4d\n", w, h);
		}
		void onPause(void)
		{
			axl::gl::View::onPause();
			printf("Event.onPause\n");
		}
		void onResume(void)
		{
			axl::gl::View::onResume();
			printf("Event.onResume\n");
		}
		void onKey(axl::gl::KeyCode key_code, bool is_down)
		{
			axl::gl::View::onKey(key_code, is_down);
			printf("Event.onKey: %3d - %s - %s\n", key_code, CStrKeyCode(key_code), (is_down ? "Down" : "Up"));
			if(is_down)
			{
				using namespace axl::gl;
				switch (key_code)
				{
					case KEY_ESCAPE:
						destroy();
						break;
					case KEY_F2:
						show(visiblity==VS_FULLSCREEN ? SM_SHOW : SM_FULLSCREEN);
						break;
				}
			}
		}
		void onChar(char char_code)
		{
			View::onChar(char_code);
			// printf("Event.onChar: %3hhd - '%c'\n", char_code, char_code);
		}
		void onPointer(int index, int x, int y, bool is_down)
		{
			View::onPointer(index, x, y, is_down);
			printf("Event.onPointer: [%d]-> x(%d) y(%d) - %s \n", index, x, y, (is_down ? "Down" : "Up"));
		}
		void onPointerMove(int index, int x, int y)
		{
			View::onPointerMove(index, x, y);
			// printf("Event.onPointerMove: [%d]-> x(%d) y(%d)\r", index, x, y);
		}
};

void terminating()
{
	MyView::cleanup();
}

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::gl;
	using namespace axl::math;
	printf("axl.gl - version %u.%u.%u  %s %s\n", lib::version.major, lib::version.minor, lib::version.patch, LIB_TYPE, DEBUG_REL);
	printf("axl.glw - version %u.%u.%u  %s %s\n", axl::glw::lib::version.major, axl::glw::lib::version.minor, axl::glw::lib::version.patch, axlglwLibraryType(), axl::glw::lib::debug ? "Debug" : "Release");
	puts("----------------------------------------");
	std::atexit(terminating);
	Vec2<int> screen = Application::getCurrentDesktopSize(), size(640, 480);
	MyView view(L"My View", (screen - size)/2, size);
	view.setCursor(View::CUR_HAND);
	Assertv(view.setIcon(L"Resources/Icons/axl.ico"), verbose);
	Assertv(view.create(), verbose);
	Assertv(0 == wcscmp(view.title.cwstr(), L"My View"), verbose);
	Assertv(view.setTitle(L"View"), verbose);
	Assertv(0 == wcscmp(view.title.cwstr(), L"View"), verbose);
	Assertv(view.position == (screen-size)/2, verbose);
	Assertv(view.size == Vec2<int>(640,480), verbose);
	Assertv(view.visiblity == View::VS_HIDDEN, verbose);
	Assertv(view.cursor == View::CUR_HAND, verbose);
	Assertv(view.config == View::Config::Default, verbose);
	Assertv(view.pointers, verbose);
	for(int i=0; i<View::MAX_POINTERS; ++i)
	{ Assertv(!view.pointers[i], verbose); }
	Assertv(view.isValid(), verbose);
	Assertv(view.visiblity == View::VS_HIDDEN, verbose);
	Assertv(view.show(View::SM_SHOW), verbose);
	Application::pollEvents();
	Assertv(view.visiblity == View::VS_SHOWN, verbose);
	Application::loopEvents();
	puts("----------------------------------------");
	printf("# %d Failed!\n", Assert::_num_failed_tests);
	return Assert::_num_failed_tests;
}