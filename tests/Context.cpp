#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.gl/Application.hpp>
#include <axl.gl/View.hpp>
#include <axl.gl/Context.hpp>
#include <axl.glw/glw.hpp>
#include <axl.glw/gl.hpp>

class GameView : public axl::gl::View
{
	public:
		GameView(
			const axl::util::WString& _title,
			axl::math::Vec2<int> _pos,
			axl::math::Vec2<int> _size,
			axl::gl::View::Cursor _cursor = axl::gl::View::DefaultCursor) :
			axl::gl::View(_title, _pos, _size, _cursor)
		{}
		void onDestroy(void)
		{
			axl::gl::Application::quit(0);
		}
		void onSize(int w, int h)
		{
			axl::gl::View::onSize(w, h);
		}
	private:

};

void terminate(void)
{
	axl::gl::Application::quit(0);
	axl::glw::cleanup();
}

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::gl;
	using namespace axl::math;
	printf("axl.gl - version %u.%u.%u  %s %s\n", lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch, libType(lib::LIBRARY_TYPE), buildType(lib::BUILD_TYPE));
	printf("axl.glw - version %u.%u.%u  %s %s\n", axl::glw::lib::VERSION.major, axl::glw::lib::VERSION.minor, axl::glw::lib::VERSION.patch, libType(axl::glw::lib::LIBRARY_TYPE), buildType(axl::glw::lib::BUILD_TYPE));
	puts("----------------------------------------");
	atexit(terminate);
	axl::math::Vec2<int> screen = axl::gl::Application::getCurrentDesktopSize();
	axl::math::Vec2<int> size = {640, 480};
	axl::math::Vec2<int> pos = (screen - size)/2;
	GameView::Config view_configs[] =
	{
		GameView::Config(1, GameView::Config::PT_RGBA, 32,8,8,8,8, 24,8, 0,0,0,0,0, 16, true, false),
		GameView::Config(2, GameView::Config::PT_RGBA, 32,8,8,8,8, 24,8, 0,0,0,0,0, 8, true, false),
		GameView::Config(3, GameView::Config::PT_RGBA, 32,8,8,8,8, 24,8, 0,0,0,0,0, 4, true, false),
		GameView::Config(4, GameView::Config::PT_RGBA, 32,8,8,8,8, 24,8, 0,0,0,0,0, 0, true, false)
	};
	GameView view(L"Context Test", pos, size, GameView::CUR_CROSS);
	Assertv(view.setIcon(L"Resources/Icons/axl.ico"), verbose);
	Assertv(view.create(true, view_configs, sizeof(view_configs)/sizeof(GameView::Config)), verbose);
	Assertv(view.isValid(), verbose);
	printf("view.config.id: %d\n", view.config.id);
	
	axl::gl::Context context;
	axl::gl::Context::Config context_configs[] = {
		axl::gl::Context::Config(1, 0, 0, axl::gl::Context::Config::GLP_COMPATIBLITY)
	};
	Assertv(context.create(false, &view, context_configs, sizeof(context_configs)/sizeof(axl::gl::Context::Config)), verbose);
	Assertv(context.isValid(), verbose);
	printf("context.config.id: %d\n", context.config.id);
	Assertv(context.makeCurrent(), verbose);
	{
		using namespace axl::glw::gl;
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	Assertv(view.swap(), verbose);
	view.show(GameView::SM_SHOW);
	axl::gl::Application::loopEvents();
	puts("----------------------------------------");
	printf("# %d Failed!\n", Assert::_num_failed_tests);
	return Assert::_num_failed_tests;
}