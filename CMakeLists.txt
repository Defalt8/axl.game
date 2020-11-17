cmake_minimum_required( VERSION 3.17 )

project( axl.gl )

# Configure
option( BUILD_TESTS OFF )
if( "${LIBRARY_TYPE}" STREQUAL "" )
	set( LIBRARY_TYPE "STATIC" )
endif()
if( "${CMAKE_BUILD_TYPE}" STREQUAL "" )
	set( CMAKE_BUILD_TYPE "Debug" )
endif()
if( "${AXL_LIB_DIR}" STREQUAL "" )
	set( AXL_LIB_DIR "lib" )
endif()
if( "${AXL_INC_DIR}" STREQUAL "" )
	set( AXL_INC_DIR "include" )
endif()

# Configure build type
set( LIB_SUFFIX "" )
if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
	add_compile_definitions( DEBUG )
	set( LIB_SUFFIX d )
	if( ${MSVC} )
		add_compile_options( /DEBUG /Od )
	else()
		add_compile_options( -g -Og )
	endif()
elseif( "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
	add_compile_definitions( NDEBUG )
	if( ${MSVC} )
		add_compile_options( /Ot )
	else()
		add_compile_options( -O3 )
	endif()
endif()

# Configure library type
if( (NOT "${LIB_TYPE}" STREQUAL "MODULE" ) AND (NOT "${LIB_TYPE}" STREQUAL "SHARED" ) )
	set( LIB_TYPE STATIC )
endif()
set( LIBRARY_TYPE ${LIB_TYPE} )

# Configure axl::glw library type and debug
if( (NOT "${AXLGLW_LIB_TYPE}" STREQUAL "MODULE") AND (NOT "${AXLGLW_LIB_TYPE}" STREQUAL "SHARED") )
	set( AXLGLW_LIB_TYPE STATIC )
endif()
set( AXLGLW_LIBRARY_TYPE ${AXLGLW_LIB_TYPE} )
option( AXLGLW_LIB_DEBUG OFF )

# Configure install dirs
if( "${CMAKE_INSTALL_INCDIR}" STREQUAL "" )
set( CMAKE_INSTALL_INCDIR include )
endif()
if( "${CMAKE_INSTALL_LIBDIR}" STREQUAL "" )
	set( CMAKE_INSTALL_LIBDIR lib )
endif()
if( "${CMAKE_INSTALL_BINDIR}" STREQUAL "" )
	set( CMAKE_INSTALL_BINDIR bin )
endif()

set( CMAKE_CXX_STANDARD 11 )

# Print configurations
message( "Project: ${PROJECT_NAME}" )
message( "LIB_TYPE= ${LIB_TYPE}" )
message( "AXL_INC_DIR= ${AXL_INC_DIR}" )
message( "AXL_LIB_DIR= ${AXL_LIB_DIR}" )
message( "AXLGLW_LIB_TYPE= ${AXLGLW_LIB_TYPE}" )
message( "AXLGLW_LIB_DEBUG= ${AXLGLW_LIB_DEBUG}" )
message( "CMAKE_BUILD_TYPE= ${CMAKE_BUILD_TYPE}" )
message( "CMAKE_CXX_STANDARD= ${CMAKE_CXX_STANDARD}" )
message( "CMAKE_INSTALL_PREFIX= ${CMAKE_INSTALL_PREFIX}" )
message( "CMAKE_INSTALL_INCDIR= ${CMAKE_INSTALL_INCDIR}" )
message( "CMAKE_INSTALL_LIBDIR= ${CMAKE_INSTALL_LIBDIR}" )
message( "CMAKE_INSTALL_BINDIR= ${CMAKE_INSTALL_BINDIR}" )
message( "BUILD_TESTS= ${BUILD_TESTS}" )
message( "------------------------------------------" )

include_directories( include "${AXL_INC_DIR}" )
link_directories( . lib "${AXL_LIB_DIR}" )
add_subdirectory( src )
if( ${BUILD_TESTS} )
	add_subdirectory( tests )
endif()

# Install
install( FILES
	"include/axl.gl/lib.hpp"
	DESTINATION "${CMAKE_INSTALL_INCDIR}/axl.gl"
)
install( TARGETS
	axl.gl
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	CONFIGURATIONS "" Debug Release
)