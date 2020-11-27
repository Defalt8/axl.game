#pragma once
#include <axl.math/Vec2.hpp>
#include <axl.util/WString.hpp>
#include "lib.hpp"
#include "KeyCodes.hpp"
#include "Context.hpp"

namespace axl {
namespace gl {

/**
 * A window in Desktop platforms and NativeActivity in Android platforms.
 * Is responsible for creating and initializing a View with an OpenGL context.
 */
class AXLGLCXXAPI View
{
	public:
		constexpr static int MAX_TOUCHES = 10;
		constexpr static int MAX_POINTERS = MAX_TOUCHES + 2;
		// A mouse or other pointer's buttons.
		enum PointerIndex { PI_RIGHT_BUTTON = 0, PI_MIDDLE_BUTTON = 1, PI_LEFT_BUTTON = 2, PI_TOUCH = 2 };
		// View visiblity states.
		enum VisiblityState { VS_SHOWN, VS_HIDDEN, VS_FULLSCREEN };
		// View show modes.
		enum ShowMode { SM_SHOW, SM_HIDE, SM_FULLSCREEN };
		// View cursor type. Implementation varies through platforms.
		enum Cursor { CUR_NONE, CUR_CUSTOM, CUR_ARROW, CUR_HAND, CUR_CROSS, CUR_WAIT, CUR_HELP, CUR_IBEAM, CUR_NO };
		/**
		 * OpenGL view pixel-format configuration info.
		 */
		class AXLGLCXXAPI Config
		{
			public:
				enum PixelType { PT_RGB, PT_RGBA, PT_RGBA_FLOAT, PT_COLORINDEX };
			public:
				Config();
				Config(long id, PixelType pixel_type, char bits_color, char bits_red, char bits_green, char bits_blue, char bits_alpha, char bits_depth, char bits_stencil, char bits_accum, char bits_red_accum, char bits_green_accum, char bits_blue_accum, char bits_alpha_accum, char samples, bool double_buffered, bool stereo);
				Config(const Config& config);
				bool operator==(const Config& config) const;
				bool operator!=(const Config& config) const;
			public:
				long id;
				PixelType pixel_type;
				char bits_color;
				char bits_red;
				char bits_green;
				char bits_blue;
				char bits_alpha;
				char bits_depth;
				char bits_stencil;
				char bits_accum;
				char bits_red_accum;
				char bits_green_accum;
				char bits_blue_accum;
				char bits_alpha_accum;
				char samples;
				bool double_buffered; 
				bool stereo;
			public:
				// The default View configuration to be set at the creation of a new Config by default.
				// You can modify it to your liking before creating configurations. 
				static Config Default;
				// A Null value representaion of the Config class.
				static const Config Null;
		};
	public:
		View(const axl::util::WString& title, const axl::math::Vec2<int>& position, const axl::math::Vec2<int>& size, const Cursor& cursor = View::DefaultCursor);
		virtual ~View();
		bool isValid() const;
		bool create(bool recreate = false, const Config* configs = (const Config*)0, int configs_count = 0);
		void destroy();
		static void cleanup();
		bool setPosition(const axl::math::Vec2<int>& position);
		bool setSize(const axl::math::Vec2<int>& size);
		bool setTitle(const axl::util::WString& title);
		bool setCursor(const Cursor& cursor);
		bool setCursorFromResource(int res_id);
		bool setIcon(const axl::util::WString& icon_file);
		bool setIconFromResource(int res_id);
		bool isPointerCaptured() const;
		bool capturePointer(bool capture) const;
		bool show(ShowMode show_mode);
		bool setCursorPosition(const axl::math::Vec2<int>& cursor_position);
		bool swap() const;
	public: // Event callback methods
		virtual bool onCreate();
		virtual void onDestroy();
		virtual void onMove(int x, int y);
		virtual void onSize(int w, int h);
		virtual void onPause();
		virtual void onResume();
		virtual void onKey(KeyCode key_code, bool is_down);
		virtual void onChar(char char_code);
		virtual void onPointer(int index, int x, int y, bool is_down);
		virtual void onPointerMove(int index, int x, int y);
	public:
		const axl::math::Vec2<int>& position;
		const axl::math::Vec2<int>& size;
		const axl::util::WString& title;
		const View::Config& config;
		const View::Cursor& cursor;
		const VisiblityState& visiblity;
		const bool& is_paused;
		const bool*const pointers;
		void *const& reserved;
	private:
		axl::math::Vec2<int> m_position;
		axl::math::Vec2<int> m_size;
		axl::util::WString m_title;
		View::Config m_config;
		View::Cursor m_cursor;
		VisiblityState m_visiblity;
		bool m_is_paused;
		bool m_pointers[MAX_POINTERS];
		void *m_reserved;
	public:
		static View::Cursor DefaultCursor;
	private:
		View(const View& view);
		View(View& view);
		View& operator=(const View& view);
		View& operator=(View& view);
		View& operator=(View view);
		friend class axl::gl::Context;
}; // class View

} // namespace axl.gl
} // namespace axl