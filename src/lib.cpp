#include <axl.gl/lib.hpp>

namespace axl {
namespace gl {
namespace lib {

const Version version = { 0, 4, 0 };

#if defined(AXLGL_MODULE)
const LibraryType type = LT_MODULE;
#elif defined(AXLGL_SHARED)
const LibraryType type = LT_SHARED;
#else
const LibraryType type = LT_STATIC;
#endif

#ifdef DEBUG
const bool Debug = true;
#else
const bool Debug = false;
#endif

} // namespace axl.gl.lib	
} // namespace axl.gl	
} // namespace axl
