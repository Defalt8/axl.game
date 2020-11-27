# library
set( LIBAXLGL_OUTPUT_NAME axl.gl )
add_library( axl.gl ${LIBAXLGL_TYPE}
	"lib.cpp"
	"Application.cpp"
	"KeyMap.cpp"
	"View.cpp"
	"Context.cpp"
)
target_compile_definitions( axl.gl
	PRIVATE LIBAXLGL_BUILD
	PUBLIC LIBAXLGL_VERSION_MAJOR=${axl.gl_VERSION_MAJOR}
	PUBLIC LIBAXLGL_VERSION_MINOR=${axl.gl_VERSION_MINOR}
	PUBLIC LIBAXLGL_VERSION_PATCH=${axl.gl_VERSION_PATCH}
)
if( "${LIBAXLGL_TYPE}" MATCHES "^[Ss][Tt][Aa][Tt][Ii][Cc]$" )
	set( LIBAXLGL_SUFFIX s )
	target_compile_definitions( axl.gl
		PUBLIC LIBAXLGL_STATIC
	)
	if( INSTALL_ARCHIVES )
		install( TARGETS axl.gl
			ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/${ARCHIVES_INSTALL_DIR}"
		)
	endif()
elseif( "${LIBAXLGL_TYPE}" MATCHES "^[Ss][Hh][Aa][Rr][Ee][Dd]$" )
	target_compile_definitions( axl.gl
		PUBLIC LIBAXLGL_SHARED
	)
	if( INSTALL_ARCHIVES )
		install( TARGETS axl.gl
			ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/${ARCHIVES_INSTALL_DIR}"
		)
	endif()
	if( INSTALL_BINARIES )
		install( TARGETS axl.gl
			RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${BINARY_INSTALL_DIR}"
		)
	endif()
else()
	set( LIBAXLGL_SUFFIX l )
endif()

if( "${CMAKE_BUILD_TYPE}" MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
	set( LIBAXLGL_SUFFIX "${LIBAXLGL_SUFFIX}d" )
endif()

set_target_properties( axl.gl PROPERTIES
	OUTPUT_NAME "${LIBAXLGL_OUTPUT_NAME}${LIBAXLGL_SUFFIX}"
	ARCHIVE_OUTPUT_NAME "${LIBAXLGL_OUTPUT_NAME}${LIBAXLGL_SUFFIX}"
	LIBRARY_OUTPUT_NAME "${LIBAXLGL_OUTPUT_NAME}${LIBAXLGL_SUFFIX}"
	RUNTIME_OUTPUT_NAME "${LIBAXLGL_OUTPUT_NAME}${LIBAXLGL_SUFFIX}"
	LIBRARY_OUTPUT_DIRECTORY "${LIBAXLGL_EXPORT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${LIBAXLGL_EXPORT_DIR}"
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

add_subdirectory( "${LIBAXLUTIL_DIR}" "axl.util" )
add_subdirectory( "${LIBAXLMATH_DIR}" "axl.math" )
add_subdirectory( "${LIBAXLGLW_DIR}" "axl.glw" )
target_include_directories( axl.gl
	PUBLIC "${LIBAXLUTIL_DIR}/include"
	PUBLIC "${LIBAXLMATH_DIR}/include"
	PUBLIC "${LIBAXLGLW_DIR}/include"
)

target_link_libraries( axl.gl
	PUBLIC axl.util
	PUBLIC axl.glw
	PUBLIC ${LIBUSER32}
	PUBLIC ${LIBGDI32}
	PUBLIC ${LIBOPENGL32}
)
