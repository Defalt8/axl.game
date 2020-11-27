#include <axl.glw/platform.h>
#if PLATFORM==PLATFORM_WINDOWS
#include "platform/win32/KeyMap.inl"
#else
#error "Unsupported platform"
#endif