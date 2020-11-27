#include <axl.glw/platform.h>
#if PLATFORM==PLATFORM_WINDOWS
#include "platform/win32/View.inl"
#else
#error "Unsupported platform"
#endif