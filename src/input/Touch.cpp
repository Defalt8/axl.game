#include <axl.game/platform.h>

#if PLATFORM==PLATFORM_WINDOWS
#	include "platform/win32/Touch.cxx"
#else
#	error "Unsupported platform"
#endif