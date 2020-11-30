#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <axl.game/Application.hpp>
#include <axl.game/KeyMap.hpp>

namespace axl {
namespace game {
using namespace axl::math;

DisplaySetting::DisplaySetting(int bits_per_pixel, int width, int height, int frequency, Rotation rotation) :
	bits_per_pixel(bits_per_pixel), width(width), height(height), frequency(frequency), rotation(rotation)
{}

Vec2<int> Application::getCurrentDisplaySize()
{
	return Vec2<int>(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

Vec2<int> Application::getCurrentDesktopSize()
{
	return Vec2<int>(GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));
}

Vec2<int> Application::getCursorPosition()
{
	POINT cpos = {-1,-1};
	GetCursorPos(&cpos);
	return Vec2<int>(cpos.x, cpos.y);
}

bool Application::enumDisplaySettings(DisplaySetting* display_setting, int i)
{
	if(!display_setting || i < -1) return false;
	DEVMODEW devmode, prev_devmode;
	ZeroMemory(&devmode, sizeof(DEVMODEW));
	devmode.dmSize = sizeof(DEVMODEW);
	if(i == DisplaySetting::IP_CURRENT || i == DisplaySetting::IP_DEFAULT)
	{
		if(EnumDisplaySettingsW(NULL, (i == DisplaySetting::IP_DEFAULT ? ENUM_REGISTRY_SETTINGS : ENUM_CURRENT_SETTINGS), &devmode))
		{
			display_setting->bits_per_pixel = (int)devmode.dmBitsPerPel;
			display_setting->width = (int)devmode.dmPelsWidth;
			display_setting->height = (int)devmode.dmPelsHeight;
			display_setting->frequency = (int)devmode.dmDisplayFrequency;
			switch(devmode.dmDisplayOrientation)
			{
				default:
				case DMDO_DEFAULT: display_setting->rotation = DisplaySetting::ROT_DEFAULT; break;
				case DMDO_90: display_setting->rotation = DisplaySetting::ROT_CCW_90; break;
				case DMDO_180: display_setting->rotation = DisplaySetting::ROT_CCW_180; break;
				case DMDO_270: display_setting->rotation = DisplaySetting::ROT_CCW_270; break;
			}
			return true;
		}
		return false;
	}
	DWORD index = 0, true_index = 0;
	while(EnumDisplaySettingsW(NULL, index, &devmode))
	{
		if(	devmode.dmBitsPerPel != prev_devmode.dmBitsPerPel ||
			devmode.dmPelsWidth != prev_devmode.dmPelsWidth ||
			devmode.dmPelsHeight != prev_devmode.dmPelsHeight ||
			devmode.dmDisplayFrequency != prev_devmode.dmDisplayFrequency ||
			devmode.dmDisplayOrientation != prev_devmode.dmDisplayOrientation )
		{
			if(i == true_index)
			{
				display_setting->bits_per_pixel = (int)devmode.dmBitsPerPel;
				display_setting->width = (int)devmode.dmPelsWidth;
				display_setting->height = (int)devmode.dmPelsHeight;
				display_setting->frequency = (int)devmode.dmDisplayFrequency;
				switch(devmode.dmDisplayOrientation)
				{
					default:
					case DMDO_DEFAULT: display_setting->rotation = DisplaySetting::ROT_DEFAULT; break;
					case DMDO_90: display_setting->rotation = DisplaySetting::ROT_CCW_90; break;
					case DMDO_180: display_setting->rotation = DisplaySetting::ROT_CCW_180; break;
					case DMDO_270: display_setting->rotation = DisplaySetting::ROT_CCW_270; break;
				}
				return true;
			}
			++true_index;
		}
		++index;
		prev_devmode = devmode;
	}
	return false;
}

bool Application::setDisplaySettings(const DisplaySetting& display_setting, bool test)
{
	DEVMODEW devmode;
	ZeroMemory(&devmode, sizeof(DEVMODEW));
	devmode.dmSize = sizeof(DEVMODEW);
	devmode.dmBitsPerPel = (DWORD)display_setting.bits_per_pixel;
	devmode.dmPelsWidth = (DWORD)display_setting.width;
	devmode.dmPelsHeight = (DWORD)display_setting.height;
	devmode.dmDisplayFrequency = (DWORD)display_setting.frequency;
	switch (display_setting.rotation)
	{
		default:
		case DisplaySetting::ROT_DEFAULT: devmode.dmDisplayOrientation = DMDO_DEFAULT; break;
		case DisplaySetting::ROT_CCW_90: devmode.dmDisplayOrientation = DMDO_90; break;
		case DisplaySetting::ROT_CCW_180: devmode.dmDisplayOrientation = DMDO_180; break;
		case DisplaySetting::ROT_CCW_270: devmode.dmDisplayOrientation = DMDO_270; break;
	}
	devmode.dmFields = (display_setting.bits_per_pixel >= 0 ? DM_BITSPERPEL : 0) |
		(display_setting.width >= 0 ? DM_PELSWIDTH : 0) |
		(display_setting.height >= 0 ? DM_PELSHEIGHT : 0) |
		(display_setting.frequency >= 0 ? DM_DISPLAYFREQUENCY : 0) |
		(display_setting.rotation >= 0 ? DM_DISPLAYORIENTATION : 0);
	return DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettingsW(&devmode, (test ? CDS_TEST : 0));
}

bool Application::restoreDisplaySettings()
{
	axl::game::DisplaySetting Default;
	if(	axl::game::Application::enumDisplaySettings(&Default, axl::game::DisplaySetting::IP_DEFAULT) &&
		axl::game::Application::setDisplaySettings(Default) )
		return true;
	// last resort display size restore
	axl::math::Vec2<int> display_size = axl::game::Application::getCurrentDisplaySize();
	Default.width = display_size.x;
	Default.height = display_size.y;
	return axl::game::Application::setDisplaySettings(Default);
}

bool Application::setCursorPosition(int x, int y)
{
	return SetCursorPos(x, y) != FALSE;
}

bool Application::setCursorPosition(const Vec2<int>& cur_pos)
{
	return SetCursorPos(cur_pos.x, cur_pos.y) != FALSE;
}

bool Application::isKeyDown(KeyCode key_code)
{
	return GetAsyncKeyState(MapKeyCode(key_code));
}

void Application::quit(int exit_code)
{
	IsQuitting = true;
	PostQuitMessage(exit_code);
}

bool Application::pollEvent()
{
	MSG message;
	if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
		return true;
	}
	return false;
}

void Application::pollEvents()
{
	MSG message;
	while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void Application::loopEvents()
{
	MSG message;
	while(GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void Application::sleep(int millis)
{
	Sleep((DWORD)millis);
}

bool Application::IsQuitting = false;

} // namespace axl.game
} // namespace axl