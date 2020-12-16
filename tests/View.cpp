#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include "KeyCodeToStr.hpp"
#include <axl.game/Application.hpp>
#include <axl.game/View.hpp>

bool printing_one_liner = false;

class TestView : public axl::game::View
{
		bool capture_on_click;
	public:
		TestView(const axl::util::WString& title_, const axl::math::Vec2i& position_, const axl::math::Vec2i& size_, const Cursor& cursor_ = View::DefaultCursor) :
			axl::game::View(title_, position_, size_, cursor_),
			capture_on_click(false)
		{}
		bool onCreate(bool recreating)
		{
			printf("Event.onCreate\n");
			return axl::game::View::onCreate(recreating);
		}
		void onDestroy(bool recreating)
		{
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onDestroy\n");
			axl::game::View::onDestroy(recreating);
			axl::game::Application::quit(0);
		}
		void onMove(int x, int y)
		{
			axl::game::View::onMove(x, y);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onMove: %4d, %4d\n", x, y);
		}
		void onSize(int w, int h)
		{
			axl::game::View::onSize(w, h);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onSize: %4d, %4d\n", w, h);
		}
		void onPause(void)
		{
			axl::game::View::onPause();
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onPause\n");
		}
		void onResume(void)
		{
			axl::game::View::onResume();
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onResume\n");
		}
		void onKey(axl::game::input::KeyCode key_code, bool is_down)
		{
			axl::game::View::onKey(key_code, is_down);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onKey: %3d - %s - %s\n", key_code, CStrKeyCode(key_code), (is_down ? "Down" : "Up"));
			if(is_down)
			{
				using namespace axl::game::input;
				switch (key_code)
				{
					case KEY_ESCAPE:
						this->destroy();
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
			axl::game::View::onChar(char_code);
			printf("Event.onChar: %3hhd - '%c'\n", char_code, char_code);
		}
		void onPointer(int index, int x, int y, bool is_down)
		{
			axl::game::View::onPointer(index, x, y, is_down);
			if(capture_on_click) capturePointer(is_down);
			if(printing_one_liner) putchar('\n');
			printing_one_liner = false;
			printf("Event.onPointer: [%d]-> x(%4d) y(%4d) - %s \n", index, x, y, (is_down ? "Down" : "Up"));
			if(pointers[PI_TOUCH] && pointers[PI_TOUCH+1])
				printf("\rTouch2Delta: (%4d, %4d)", touch2.x - touch1.x, touch2.y - touch1.y);
		}
		void onPointerMove(int index, int x, int y)
		{
			axl::game::View::onPointerMove(index, x, y);
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
		void onScroll(bool is_vertical, int delta, int x, int y)
		{
			axl::game::View::onScroll(is_vertical, delta, x, y);
			printf("\rEvent.onScroll: [%s]-> delta(%4d)  x(%4d) y(%4d)", is_vertical ? "Vertical" : "Horizontal", delta, x, y);
		}
		axl::math::Vec2i touch1, touch2;
};

void terminating()
{
	TestView::cleanup();
}

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::game;
	using namespace axl::math;
	printf("axl.game - version %u.%u.%u  %s %s\n", axl::game::lib::VERSION.major, axl::game::lib::VERSION.minor, axl::game::lib::VERSION.patch, libType(axl::game::lib::LIBRARY_TYPE), buildType(axl::game::lib::BUILD_TYPE));
	printf("axl.util - version %u.%u.%u  %s %s\n", axl::util::lib::VERSION.major, axl::util::lib::VERSION.minor, axl::util::lib::VERSION.patch, libType(axl::util::lib::LIBRARY_TYPE), buildType(axl::util::lib::BUILD_TYPE));
	printf("axl.math - version %u.%u.%u  %s %s\n", axl::math::lib::VERSION.major, axl::math::lib::VERSION.minor, axl::math::lib::VERSION.patch, libType(axl::math::lib::LIBRARY_TYPE), buildType(axl::math::lib::BUILD_TYPE));
	printf("axl.glw - version %u.%u.%u  %s %s\n", axl::glw::lib::VERSION.major, axl::glw::lib::VERSION.minor, axl::glw::lib::VERSION.patch, libType(axl::glw::lib::LIBRARY_TYPE), buildType(axl::glw::lib::BUILD_TYPE));
	puts("----------------------------------------");
	std::atexit(terminating);
	Vec2i screen = Application::getCurrentDesktopSize(), size(640, 480);
	TestView view(L"My View", (screen - size)/2, size);
	view.setCursor(View::CUR_HAND);
	FILE* icon_file = std::fopen("resources/icons/axl.ico", "rb");
	if(icon_file)
	{
		std::fclose(icon_file);
		Assertv(view.setIcon(L"resources/icons/axl.ico"), verbose);
	}
	Assertv(view.create(), verbose);
	printf("view.config.id: %ld\n", view.config.id);
	printf("view.config.pixel_type: %s\n", (view.config.pixel_type==View::Config::PT_RGB?"RGB":(view.config.pixel_type==View::Config::PT_RGBA?"RGBA":view.config.pixel_type==View::Config::PT_RGBA_FLOAT?"RGBA_FLOAT":view.config.pixel_type==View::Config::PT_COLORINDEX?"Colorindex":"Unknown")));
	printf("view.config.bits_color: %hhd\n", view.config.bits_color);
	printf("view.config.bits_red: %hhd\n", view.config.bits_red);
	printf("view.config.bits_green: %hhd\n", view.config.bits_green);
	printf("view.config.bits_blue: %hhd\n", view.config.bits_blue);
	printf("view.config.bits_alpha: %hhd\n", view.config.bits_alpha);
	printf("view.config.bits_depth: %hhd\n", view.config.bits_depth);
	printf("view.config.bits_stencil: %hhd\n", view.config.bits_stencil);
	printf("view.config.bits_accum: %hhd\n", view.config.bits_accum);
	printf("view.config.bits_red_accum: %hhd\n", view.config.bits_red_accum);
	printf("view.config.bits_green_accum: %hhd\n", view.config.bits_green_accum);
	printf("view.config.bits_blue_accum: %hhd\n", view.config.bits_blue_accum);
	printf("view.config.bits_alpha_accum: %hhd\n", view.config.bits_alpha_accum);
	printf("view.config.samples: %hhd\n", view.config.samples);
	printf("view.config.double_buffered: %hhd\n", view.config.double_buffered);
	printf("view.config.stereo: %hhd\n", view.config.stereo);
	Assertv(0 == wcscmp(view.title.cwstr(), L"My View"), verbose);
	Assertv(view.setTitle(L"View"), verbose);
	Assertv(0 == wcscmp(view.title.cwstr(), L"View"), verbose);
	Assertv(view.position == (screen-size)/2, verbose);
	Assertv(view.size == Vec2i(640,480), verbose);
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