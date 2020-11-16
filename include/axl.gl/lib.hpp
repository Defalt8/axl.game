#pragma once

#if defined(MODULE)
	#ifdef WIN32
		#ifdef BUILD_MODULE
			#define AXLGLAPI extern __declspec(dllexport)
		#else
			#define AXLGLAPI extern __declspec(dllimport)
		#endif
	#else
		#define AXLGLAPI extern
	#endif
#elif defined(SHARED)
	#ifdef WIN32
		#ifdef BUILD_SHARED
			#define AXLGLAPI extern __declspec(dllexport)
		#else
			#define AXLGLAPI extern __declspec(dllimport)
		#endif
	#else
		#define AXLGLAPI extern
	#endif
#else
	#define AXLGLAPI extern
#endif

namespace axl {
namespace gl {
namespace lib {

struct Version
{
	short major;
	short minor;
	short patch;
};

AXLGLAPI Version version;

} // namespace axl.gl.lib	
} // namespace axl.gl	
} // namespace axl
