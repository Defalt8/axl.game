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
		case KEY_MBUTTON: return "KEY_MBUTTON";
		case KEY_XBUTTON1: return "KEY_XBUTTON1";
		case KEY_XBUTTON2: return "KEY_XBUTTON2";
		case KEY_CANCEL: return "KEY_CANCEL";
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
		case KEY_CMD: return "KEY_CMD";
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
		case KEY_0: return "KEY_0";
		case KEY_1: return "KEY_1";
		case KEY_2: return "KEY_2";
		case KEY_3: return "KEY_3";
		case KEY_4: return "KEY_4";
		case KEY_5: return "KEY_5";
		case KEY_6: return "KEY_6";
		case KEY_7: return "KEY_7";
		case KEY_8: return "KEY_8";
		case KEY_9: return "KEY_9";
		case KEY_A: return "KEY_A";
		case KEY_B: return "KEY_B";
		case KEY_C: return "KEY_C";
		case KEY_D: return "KEY_D";
		case KEY_E: return "KEY_E";
		case KEY_F: return "KEY_F";
		case KEY_G: return "KEY_G";
		case KEY_H: return "KEY_H";
		case KEY_I: return "KEY_I";
		case KEY_J: return "KEY_J";
		case KEY_K: return "KEY_K";
		case KEY_L: return "KEY_L";
		case KEY_M: return "KEY_M";
		case KEY_N: return "KEY_N";
		case KEY_O: return "KEY_O";
		case KEY_P: return "KEY_P";
		case KEY_Q: return "KEY_Q";
		case KEY_R: return "KEY_R";
		case KEY_S: return "KEY_S";
		case KEY_T: return "KEY_T";
		case KEY_U: return "KEY_U";
		case KEY_V: return "KEY_V";
		case KEY_W: return "KEY_W";
		case KEY_X: return "KEY_X";
		case KEY_Y: return "KEY_Y";
		case KEY_Z: return "KEY_Z";
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
		case KEY_PRINT: return "KEY_PRINT";
		case KEY_APPS: return "KEY_APPS";
		case KEY_SLEEP: return "KEY_SLEEP";
		case KEY_VOLUME_MUTE: return "KEY_VOLUME_MUTE";
		case KEY_VOLUME_DOWN: return "KEY_VOLUME_DOWN";
		case KEY_VOLUME_UP: return "KEY_VOLUME_UP";
		case KEY_MEDIA_NEXT_TRACK: return "KEY_MEDIA_NEXT_TRACK";
		case KEY_MEDIA_PREV_TRACK: return "KEY_MEDIA_PREV_TRACK";
		case KEY_MEDIA_STOP: return "KEY_MEDIA_STOP";
		case KEY_MEDIA_PLAY_PAUSE: return "KEY_MEDIA_PLAY_PAUSE";
		case KEY_LAUNCH_MAIL: return "KEY_LAUNCH_MAIL";
		case KEY_LAUNCH_MEDIA_SELECT: return "KEY_LAUNCH_MEDIA_SELECT";
		case KEY_LAUNCH_APP1: return "KEY_LAUNCH_APP1";
		case KEY_LAUNCH_APP2: return "KEY_LAUNCH_APP2";
		case KEY_TILDE: return "KEY_TILDE";
		case KEY_MINUS: return "KEY_MINUS";
		case KEY_EQUALS: return "KEY_EQUALS";
		case KEY_OPENBRACE: return "KEY_OPENBRACE";
		case KEY_CLOSEBRACE: return "KEY_CLOSEBRACE";
		case KEY_BACKSLASH: return "KEY_BACKSLASH";
		case KEY_FORWARDSLASH: return "KEY_FORWARDSLASH";
		case KEY_SEMICOLON: return "KEY_SEMICOLON";
		case KEY_QUOTE: return "KEY_QUOTE";
		case KEY_COMMA: return "KEY_COMMA";
		case KEY_PERIOD: return "KEY_PERIOD";
	}
	return "KEY_UNKNOWN";
}

bool printing_one_liner = false;

class MyView : public axl::gl::View
{
		bool capture_on_click;
	public:
		MyView(const axl::utils::WString& title_, const axl::math::Vec2<int>& position_, const axl::math::Vec2<int>& size_, const Cursor& cursor_ = View::DefaultCursor) :
			axl::gl::View(title_, position_, size_, cursor_),
			capture_on_click(false)
		{}
		bool onCreate()
		{
			printf("Event.onCreate\n");
			return axl::gl::View::onCreate();
		}
		void onDestroy()
		{
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onDestroy\n");
			axl::gl::Application::quit(0);
			axl::gl::View::onDestroy();
		}
		void onMove(int x, int y)
		{
			axl::gl::View::onMove(x, y);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onMove: %4d, %4d\n", x, y);
		}
		void onSize(int w, int h)
		{
			axl::gl::View::onSize(w, h);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onSize: %4d, %4d\n", w, h);
		}
		void onPause(void)
		{
			axl::gl::View::onPause();
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onPause\n");
		}
		void onResume(void)
		{
			axl::gl::View::onResume();
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onResume\n");
		}
		void onKey(axl::gl::KeyCode key_code, bool is_down)
		{
			axl::gl::View::onKey(key_code, is_down);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onKey: %3d - %s - %s\n", key_code, CStrKeyCode(key_code), (is_down ? "Down" : "Up"));
			if(is_down)
			{
				using namespace axl::gl;
				switch (key_code)
				{
					case KEY_ESCAPE:
						// this->destroy();
						break;
					case KEY_F2:
						show(visiblity==VS_FULLSCREEN ? SM_SHOW : SM_FULLSCREEN);
						break;
					case KEY_F3:
						if(capturePointer(!isPointerCaptured()))
							printf("> Pointer Captured: %s\n", isPointerCaptured() ? "yes" : "no");
						break;
					case KEY_F4:
						capture_on_click = !capture_on_click;
						printf("> Capture on click: %s\n", capture_on_click ? "yes" : "no");
						break;
				}
			}
		}
		void onChar(char char_code)
		{
			View::onChar(char_code);
			printf("Event.onChar: %3hhd - '%c'\n", char_code, char_code);
		}
		void onPointer(int index, int x, int y, bool is_down)
		{
			View::onPointer(index, x, y, is_down);
			if(capture_on_click) capturePointer(is_down);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onPointer: [%d]-> x(%4d) y(%4d) - %s \n", index, x, y, (is_down ? "Down" : "Up"));
			if(pointers[PI_TOUCH] && pointers[PI_TOUCH+1])
				printf("\rTouch2Delta: (%4d, %4d)", touch2.x - touch1.x, touch2.y - touch1.y);
		}
		void onPointerMove(int index, int x, int y)
		{
			View::onPointerMove(index, x, y);
			switch(index)
			{
				case PI_TOUCH + 0: touch1.set(x, y); break;
				case PI_TOUCH + 1: touch2.set(x, y); break;
			}
			printing_one_liner = true;
			if(pointers[PI_TOUCH] && pointers[PI_TOUCH+1])
				printf("\rTouch2Delta: (%4d, %4d)", touch2.x - touch1.x, touch2.y - touch1.y);
			else
				printf("\rEvent.onPointerMove: [%d]-> x(%4d) y(%4d)", index, x, y);
		}
		axl::math::Vec2<int> touch1, touch2;
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