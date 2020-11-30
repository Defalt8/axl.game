#pragma once

#if defined(LIBAXLGAME_SHARED)
#	ifdef WIN32
#		ifdef LIBAXLGAME_BUILD
#			define AXLGAMEAPI extern __declspec(dllexport)
#			define AXLGAMECXXAPI __declspec(dllexport)
#		else
#			define AXLGAMEAPI extern __declspec(dllimport)
#			define AXLGAMECXXAPI __declspec(dllimport)
#		endif
#	else
#		define AXLGAMEAPI extern
#		define AXLGAMECXXAPI
#	endif
#else
#	define AXLGAMEAPI extern
#	define AXLGAMECXXAPI
#endif

namespace axl {
namespace game {
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

AXLGAMEAPI const Version VERSION;
AXLGAMEAPI const LibraryType LIBRARY_TYPE;
AXLGAMEAPI const BuildType BUILD_TYPE;

} // namespace axl.game.lib	
} // namespace axl.game	
} // namespace axl
