#pragma once
#include "lib.hpp"
#include "KeyCodes.hpp"

namespace axl {
namespace game {

AXLGAMEAPI KeyCode MapPlatformKeyCode(int platform_key_code);
AXLGAMEAPI int MapKeyCode(KeyCode key_code);

} // namespace axl.game
} // namespace axl