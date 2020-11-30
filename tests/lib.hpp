#pragma once
#include <axl.game/lib.hpp>
#include <axl.util/lib.hpp>
#include <axl.math/lib.hpp>
#include <axl.glw/lib.hpp>

const char* libType(axl::game::lib::LibraryType lib_type)
{
	using namespace axl::game::lib;
	switch (lib_type)
	{
		case LT_SHARED: return "SHARED";
		default:
		case LT_STATIC: return "STATIC";
	}
}

const char* buildType(axl::game::lib::BuildType build_type)
{
	using namespace axl::game::lib;
	switch (build_type)
	{
		case BT_DEBUG: return "Debug";
		case BT_RELEASE: return "Release";
		default:
		case BT_OTHER: return "Other";
	}
}

const char* libType(axl::util::lib::LibraryType lib_type)
{
	using namespace axl::util::lib;
	switch (lib_type)
	{
		case LT_SHARED: return "SHARED";
		default:
		case LT_STATIC: return "STATIC";
	}
}

const char* buildType(axl::util::lib::BuildType build_type)
{
	using namespace axl::util::lib;
	switch (build_type)
	{
		case BT_DEBUG: return "Debug";
		case BT_RELEASE: return "Release";
		default:
		case BT_OTHER: return "Other";
	}
}

const char* libType(axl::math::lib::LibraryType lib_type)
{
	using namespace axl::math::lib;
	switch (lib_type)
	{
		case LT_SHARED: return "SHARED";
		default:
		case LT_STATIC: return "STATIC";
	}
}

const char* buildType(axl::math::lib::BuildType build_type)
{
	using namespace axl::math::lib;
	switch (build_type)
	{
		case BT_DEBUG: return "Debug";
		case BT_RELEASE: return "Release";
		default:
		case BT_OTHER: return "Other";
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