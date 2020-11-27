#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.gl/Application.hpp>
#include <axl.gl/View.hpp>
#include <axl.gl/Context.hpp>
#include <axl.glw/glw.hpp>
#include <axl.glw/gl.hpp>
#include <axl.math/angle.hpp>

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
			if(context.isValid() && context.makeCurrent())
			{
				using namespace axl::glw::gl;
				glViewport(0, 0, w, h);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				double ratio = (double)w/h;
				glOrtho(-ratio, ratio, -1.0, 1.0, -1.0, 1.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
			}
		}
	public:
		axl::gl::Context context;
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
	printf("axl.gl - version %u.%u.%u  %s %s\n", axl::glw::lib::VERSION.major, axl::glw::lib::VERSION.minor, axl::glw::lib::VERSION.patch, libType(axl::glw::lib::LIBRARY_TYPE), buildType(axl::glw::lib::BUILD_TYPE));
	printf("axl.util - version %u.%u.%u  %s %s\n", axl::util::lib::VERSION.major, axl::util::lib::VERSION.minor, axl::util::lib::VERSION.patch, libType(axl::util::lib::LIBRARY_TYPE), buildType(axl::util::lib::BUILD_TYPE));
	printf("axl.math - version %u.%u.%u  %s %s\n", axl::math::lib::VERSION.major, axl::math::lib::VERSION.minor, axl::math::lib::VERSION.patch, libType(axl::math::lib::LIBRARY_TYPE), buildType(axl::math::lib::BUILD_TYPE));
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
	axl::gl::Context::Config context_configs[] = {
		axl::gl::Context::Config(1, 0, 0, axl::gl::Context::Config::GLP_COMPATIBLITY)
	};
	Assertv(view.context.create(false, &view, context_configs, sizeof(context_configs)/sizeof(axl::gl::Context::Config)), verbose);
	Assertv(view.context.isValid(), verbose);
	printf("context.config.id: %d\n", view.context.config.id);
	Assertv(view.context.makeCurrent(), verbose);
	{
		using namespace axl::glw::gl;
		glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	Assertv(view.swap(), verbose);
	view.show(GameView::SM_SHOW);

	static std::clock_t update_clock = std::clock();
	float angular_speed = 69.0f, theta = 0.0f, delta_time = 0.0f;

	while(!axl::gl::Application::IsQuitting)
	{
		if(axl::gl::Application::pollEvent()) continue;
		if(view.isValid() && !view.is_paused && view.context.makeCurrent())
		{
			using namespace axl::glw::gl;
			delta_time = (double)(std::clock() - update_clock) / (double)CLOCKS_PER_SEC;
			update_clock = std::clock();
			theta += angular_speed * delta_time;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glRotatef(theta, 0.0f, 0.0f, 1.0f);
			glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glColor4ub(32,128,255,255);
			glBegin(GL_TRIANGLES);
				glVertex2d(-0.5,-0.5);
				glVertex2d( 0.5,-0.5);
				glVertex2d( 0.0, 0.5);
			glEnd();
			view.swap();
		}
	}
	axl::gl::Application::pollEvents();
	puts("----------------------------------------");
	printf("# %d Failed!\n", Assert::_num_failed_tests);
	return Assert::_num_failed_tests;
}