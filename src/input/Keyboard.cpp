#include <axl.game/platform.h>

#if PLATFORM==PLATFORM_WINDOWS
#	include "platform/win32/Keyboard.cxx"
#else
#	error "Unsupported platform"
#endif