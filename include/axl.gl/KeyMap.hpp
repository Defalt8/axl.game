#pragma once
#include "lib.hpp"
#include "KeyCodes.hpp"

namespace axl {
namespace gl {

AXLGLAPI KeyCode MapPlatformKeyCode(int platform_key_code);
AXLGLAPI int MapKeyCode(KeyCode key_code);

} // namespace axl.gl
} // namespace axl