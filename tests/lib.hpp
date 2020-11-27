#pragma once
#include <axl.gl/lib.hpp>
#include <axl.glw/lib.hpp>

const char* libType(axl::gl::lib::LibraryType lib_type)
{
	using namespace axl::gl::lib;
	switch (lib_type)
	{
		case LT_SHARED: return "SHARED";
		default:
		case LT_STATIC: return "STATIC";
	}
}

const char* libType(axl::glw::lib::LibraryType lib_type)
{
	using namespace axl::glw::lib;
	switch (lib_type)
	{
		case LT_SHARED: return "SHARED";
		default:
		case LT_STATIC: return "STATIC";
	}
}

const char* buildType(axl::gl::lib::BuildType build_type)
{
	using namespace axl::gl::lib;
	switch (build_type)
	{
		case BT_DEBUG: return "Debug";
		case BT_RELEASE: return "Release";
		default:
		case BT_OTHER: return "Other";
	}
}

const char* buildType(axl::glw::lib::BuildType build_type)
{
	using namespace axl::glw::lib;
	switch (build_type)
	{
		case BT_DEBUG: return "Debug";
		case BT_RELEASE: return "Release";
		default:
		case BT_OTHER: return "Other";
	}
}