# library
set( LIBAXLGAME_OUTPUT_NAME axl.game )
add_library( axl.game ${LIBAXLGAME_TYPE}
	"lib.cpp"
	"Application.cpp"
	"View.cpp"
	"Context.cpp"
	"input/Keyboard.cpp"
	"input/Mouse.cpp"
	"input/Touch.cpp"
)
target_compile_definitions( axl.game
	PRIVATE LIBAXLGAME_BUILD
	PUBLIC LIBAXLGAME_VERSION_MAJOR=${axl.game_VERSION_MAJOR}
	PUBLIC LIBAXLGAME_VERSION_MINOR=${axl.game_VERSION_MINOR}
	PUBLIC LIBAXLGAME_VERSION_PATCH=${axl.game_VERSION_PATCH}
)
if( "${LIBAXLGAME_TYPE}" MATCHES "^[Ss][Tt][Aa][Tt][Ii][Cc]$" )
	set( LIBAXLGAME_SUFFIX s )
	target_compile_definitions( axl.game
		PUBLIC LIBAXLGAME_STATIC
	)
	if( INSTALL_ARCHIVES AND LIBAXLGAME_INSTALL_ARCHIVES )
		install( TARGETS axl.game
			ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/${ARCHIVES_INSTALL_DIR}"
		)
	endif()
elseif( "${LIBAXLGAME_TYPE}" MATCHES "^[Ss][Hh][Aa][Rr][Ee][Dd]$" )
	target_compile_definitions( axl.game
		PUBLIC LIBAXLGAME_SHARED
	)
	if( INSTALL_ARCHIVES AND LIBAXLGAME_INSTALL_ARCHIVES )
		install( TARGETS axl.game
			ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/${ARCHIVES_INSTALL_DIR}"
		)
	endif()
	if( INSTALL_BINARIES AND LIBAXLGAME_INSTALL_BINARIES )
		install( TARGETS axl.game
			RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${BINARY_INSTALL_DIR}"
		)
	endif()
else()
	set( LIBAXLGAME_SUFFIX l )
endif()

if( "${CMAKE_BUILD_TYPE}" MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
	set( LIBAXLGAME_SUFFIX "${LIBAXLGAME_SUFFIX}d" )
endif()

set_target_properties( axl.game PROPERTIES
	OUTPUT_NAME "${LIBAXLGAME_OUTPUT_NAME}${LIBAXLGAME_SUFFIX}"
	ARCHIVE_OUTPUT_NAME "${LIBAXLGAME_OUTPUT_NAME}${LIBAXLGAME_SUFFIX}"
	LIBRARY_OUTPUT_NAME "${LIBAXLGAME_OUTPUT_NAME}${LIBAXLGAME_SUFFIX}"
	RUNTIME_OUTPUT_NAME "${LIBAXLGAME_OUTPUT_NAME}${LIBAXLGAME_SUFFIX}"
	LIBRARY_OUTPUT_DIRECTORY "${LIBAXLGAME_EXPORT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${LIBAXLGAME_EXPORT_DIR}"
)

# Target link libraries
if( ${WIN32} )
	if( ${MSVC} )
		set( LIBUSER32 User32.lib )
		set( LIBGDI32 gdi32.lib )
		set( LIBOPENGL32 opengl32.lib )
	else()
		set( LIBUSER32 -luser32 )
		set( LIBGDI32 -lgdi32 )
		set( LIBOPENGL32 -lopengl32 )
	endif()
else()
	set( LIBOPENGL32 -lopengl32 )
endif()

set( LIBAXLUTIL_EXPORT_DIR "${axl.game_BINARY_DIR}/tests" CACHE PATH "Binary files building path" )
set( LIBAXLMATH_EXPORT_DIR "${axl.game_BINARY_DIR}/tests" CACHE PATH "Binary files building path" )
set( LIBAXLGLW_EXPORT_DIR "${axl.game_BINARY_DIR}/tests" CACHE PATH "Binary files building path" )
add_subdirectory( "${LIBAXLUTIL_DIR}" "axl.util" )
add_subdirectory( "${LIBAXLMATH_DIR}" "axl.math" )
add_subdirectory( "${LIBAXLGLW_DIR}" "axl.glw" )
target_include_directories( axl.game
	PUBLIC "${LIBAXLUTIL_DIR}/include"
	PUBLIC "${LIBAXLMATH_DIR}/include"
	PUBLIC "${LIBAXLGLW_DIR}/include"
)

target_link_libraries( axl.game
	PUBLIC axl.util
	PUBLIC axl.math
	PUBLIC axl.glw
	PUBLIC ${LIBUSER32}
	PUBLIC ${LIBGDI32}
	PUBLIC ${LIBOPENGL32}
)
