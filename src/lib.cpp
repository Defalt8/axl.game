#include <axl.gl/lib.hpp>

namespace axl {
namespace gl {
namespace lib {

const Version VERSION = { LIBAXLGL_VERSION_MAJOR, LIBAXLGL_VERSION_MINOR, LIBAXLGL_VERSION_PATCH };

#if defined(AXLGL_SHARED)
const LibraryType LIBRARY_TYPE = LT_SHARED;
#else
const LibraryType LIBRARY_TYPE = LT_STATIC;
#endif

#ifdef DEBUG
const BuildType BUILD_TYPE = BT_DEBUG;
#elif defined(NDEBUG)
const BuildType BUILD_TYPE = BT_RELEASE;
#else
const BuildType BUILD_TYPE = BT_OTHER;
#endif

} // namespace axl.gl.lib	
} // namespace axl.gl	
} // namespace axl
