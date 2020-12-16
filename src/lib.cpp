#include <axl.game/lib.hpp>

namespace axl {
namespace game {
namespace lib {

const Version VERSION = { LIBAXLGAME_VERSION_MAJOR, LIBAXLGAME_VERSION_MINOR, LIBAXLGAME_VERSION_PATCH };

#if defined(LIBAXLGAME_SHARED)
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

} // namespace axl.game.lib	
} // namespace axl.game	
} // namespace axl
