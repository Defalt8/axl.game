#include <axl.glw/platform.hpp>
#if PLATFORM==PLATFORM_WINDOWS
#include "platform/win32/Context.inl"
#else
#error "Unsupported platform"
#endif