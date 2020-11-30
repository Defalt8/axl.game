#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <axl.game/Application.hpp>
#include <axl.game/KeyMap.hpp>

namespace axl {
namespace game {
using namespace axl::math;

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

bool Application::IsQuitting = false;

} // namespace axl.game
} // namespace axl