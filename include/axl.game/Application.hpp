#pragma once
#include <axl.math/Vec2.hpp>
#include "lib.hpp"
#include "KeyCodes.hpp"

namespace axl {
namespace game {

typedef struct DisplaySetting
{
	typedef enum IndexParam { IP_CURRENT = -2, IP_DEFAULT = -1 } IndexParam;
	typedef enum Rotation { ROT_DEFAULT = 0, ROT_CCW_0 = 0, ROT_CCW_90 = 1, ROT_CCW_180 = 2, ROT_CCW_270 = 3 } Rotation;
	DisplaySetting(int bits_per_pixel = -1, int width = -1, int height = -1, int frequency = -1, Rotation rotation = ROT_DEFAULT);
	int bits_per_pixel;
	int width;
	int height;
	int frequency;
	Rotation rotation;
} DisplaySetting;

class AXLGAMECXXAPI Application 
{
	public:
		static axl::math::Vec2<int> getCurrentDisplaySize();
		static axl::math::Vec2<int> getCurrentDesktopSize();
		static axl::math::Vec2<int> getCursorPosition();
		// Enumerate and return the <i>th supported display setting.
		// Pass i=IP_DEFAULT for the default settings and i=IP_CURRENT for the current settings.
		static bool enumDisplaySettings(DisplaySetting* display_setting, int i = 0);
		// Sets the display setting.
		// Set DisplaySetting member values to -1 to ignore them.
		static bool setDisplaySettings(const DisplaySetting& display_setting, bool test = false);
		// Restores the default display settings
		static bool restoreDisplaySettings();
		static bool setCursorPosition(int x, int y);
		static bool setCursorPosition(const axl::math::Vec2<int>& cur_pos);
		static bool isKeyDown(KeyCode key_code);
		static void quit(int exit_code);
		static bool pollEvent();
		static void pollEvents();
		static void loopEvents();
		static void sleep(int millis);
	public:
		static bool IsQuitting;
	private:
		Application();
		~Application();
};

} // namespace axl.game
} // namespace axl