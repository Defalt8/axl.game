cmake_minimum_required( VERSION 3.17 )

# Library
add_library( axl.gl ${LIB_TYPE}
	"lib.cpp"
	"Application.cpp"
	"KeyMap.cpp"
	"View.cpp"
	"Context.cpp"
)
# Target link libraries
if( ${MSVC} )
	set( LIBGDI32 gdi32.lib )
	set( LIBOPENGL32 opengl32.lib )
elseif( ${WIN32} )
	set( LIBGDI32 -lgdi32 )
	set( LIBOPENGL32 -lopengl32 )
else()
	set( LIBOPENGL32 -lopengl32 )
endif()
set( AXLGLW_LIB_SUFFIX "" )
if( ${AXLGLW_LIB_DEBUG} )
	set( AXLGLW_LIB_SUFFIX d )
endif()
if( "${AXLGLW_LIB_TYPE}" STREQUAL "MODULE" )
	set( LIBAXLGLW -laxl.glw${AXLGLW_LIB_SUFFIX} )
elseif( "${AXLGLW_LIB_TYPE}" STREQUAL "SHARED" )
	set( LIBAXLGLW -laxl.glwr${AXLGLW_LIB_SUFFIX} )
else()
	set( LIBAXLGLW -laxl.glws${AXLGLW_LIB_SUFFIX} )
endif()
if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
	target_link_libraries( axl.gl -laxl.utilsd ${LIBAXLGLW} ${LIBGDI32} ${LIBOPENGL32} )
else()
	target_link_libraries( axl.gl -laxl.utils ${LIBAXLGLW} ${LIBGDI32} ${LIBOPENGL32} )
endif()
# Target compile definitions
target_compile_definitions( axl.gl PUBLIC ${LIB_TYPE} AXLGLW_${AXLGLW_LIB_TYPE} )
target_compile_definitions( axl.gl PRIVATE AXLGL_BUILD )
# Target properties
set_target_properties( axl.gl PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)
set_target_properties( axl.gl PROPERTIES
	ARCHIVE_OUTPUT_NAME axl.gl${LIB_SUFFIX}
	RUNTIME_OUTPUT_NAME axl.gl${LIB_SUFFIX}
	LIBRARY_OUTPUT_NAME axl.gl${LIB_SUFFIX}
)