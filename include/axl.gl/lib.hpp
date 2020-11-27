#pragma once

#if defined(LIBAXLGL_SHARED)
#	ifdef WIN32
#		ifdef LIBAXLGL_BUILD
#			define AXLGLAPI extern __declspec(dllexport)
#			define AXLGLCXXAPI __declspec(dllexport)
#		else
#			define AXLGLAPI extern __declspec(dllimport)
#			define AXLGLCXXAPI __declspec(dllimport)
#		endif
#	else
#		define AXLGLAPI extern
#		define AXLGLCXXAPI
#	endif
#else
#	define AXLGLAPI extern
#	define AXLGLCXXAPI
#endif

namespace axl {
namespace gl {
namespace lib {

typedef enum LibraryType {
	LT_STATIC,
	LT_SHARED
} LibraryType;

typedef enum BuildType {
	BT_DEBUG,
	BT_RELEASE,
	BT_OTHER
} BuildType;

typedef struct Version
{
	unsigned short major;
	unsigned short minor;
	unsigned short patch;
} Version;

AXLGLAPI const Version VERSION;
AXLGLAPI const LibraryType LIBRARY_TYPE;
AXLGLAPI const BuildType BUILD_TYPE;

} // namespace axl.gl.lib	
} // namespace axl.gl	
} // namespace axl
