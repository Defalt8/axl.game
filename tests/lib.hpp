#pragma once
#include <axl.gl/lib.hpp>
#include <axl.glw/lib.hpp>

#if defined(DEBUG)
#	define DEBUG_REL "Debug"
#else
#	define DEBUG_REL "Release"
#endif

#if defined(AXLGL_MODULE)
#	define LIB_TYPE "MODULE"
#elif defined(AXLGL_SHARED)
#	define LIB_TYPE "SHARED"
#elif defined(AXLGL_STATIC)
#	define LIB_TYPE "STATIC"
#else
#	define LIB_TYPE ""
#endif

const char* axlglwLibraryType()
{
	switch(axl::glw::lib::type)
	{
		case axl::glw::lib::LT_MODULE: return "MODULE";
		case axl::glw::lib::LT_SHARED: return "SHARED";
		case axl::glw::lib::LT_STATIC: return "STATIC";
		default: return "-";
	}
}