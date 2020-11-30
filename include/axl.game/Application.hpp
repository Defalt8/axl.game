#pragma once
#include <axl.math/Vec2.hpp>
#include "lib.hpp"
#include "KeyCodes.hpp"

namespace axl {
namespace game {

class AXLGAMECXXAPI Application 
{
	public:
		static axl::math::Vec2<int> getCurrentDisplaySize();
		static axl::math::Vec2<int> getCurrentDesktopSize();
		static axl::math::Vec2<int> getCursorPosition();
		static bool setCursorPosition(int x, int y);
		static bool setCursorPosition(const axl::math::Vec2<int>& cur_pos);
		static bool isKeyDown(KeyCode key_code);
		static void quit(int exit_code);
		static bool pollEvent();
		static void pollEvents();
		static void loopEvents();
	public:
		static bool IsQuitting;
	private:
		Application();
		~Application();
};

} // namespace axl.game
} // namespace axl