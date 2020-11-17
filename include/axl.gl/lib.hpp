#pragma once

#if defined(AXLGL_MODULE)
#	ifdef WIN32
#		ifdef AXLGL_BUILD
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
#elif defined(AXLGL_SHARED)
#	ifdef WIN32
#		ifdef AXLGL_BUILD
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
#	ifndef AXLGL_STATIC
#		define AXLGL_STATIC
#	endif
#	define AXLGLAPI extern
#	define AXLGLCXXAPI
#endif

namespace axl {
namespace gl {
namespace lib {

enum LibraryType {
	LT_STATIC,
	LT_SHARED,
	LT_MODULE
};
typedef enum LibraryType LibraryType;

struct Version
{
	short major;
	short minor;
	short patch;
};
typedef struct Version Version;

AXLGLAPI const Version version;
AXLGLAPI const LibraryType type;
AXLGLAPI const bool debug;

} // namespace axl.gl.lib	
} // namespace axl.gl	
} // namespace axl
