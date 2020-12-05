#include <axl.glw/platform.h>
#if PLATFORM==PLATFORM_WINDOWS
#include "platform/win32/View.cxx"
#else
#error "Unsupported platform"
#endif