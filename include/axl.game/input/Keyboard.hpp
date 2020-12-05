#pragma once
#include "../lib.hpp"
#include "KeyCodes.hpp"

namespace axl {
namespace game {
namespace input {

class AXLGAMECXXAPI Keyboard 
{
	public:
		static bool isPresent();
		static bool isKeyDown(KeyCode key_code);
		static KeyCode mapPlatformKeyCode(int platform_key_code);
		static int mapKeyCode(KeyCode key_code);
	public:
		class AXLGAMECXXAPI Listener
		{
			public:
				static bool init();
				static void release();
				static bool isValid();
			public:
				static void (*onKey)(KeyCode key_code, bool is_down);
				static const void*const reserved;
			private:
				static void* m_reserved;
			private:
				Listener();
				~Listener();
		};
	private:
		Keyboard();
		~Keyboard();
};

} // namespace axl.game.input
} // namespace axl.game
} // namespace axl