cmake_minimum_required( VERSION 3.17 )

project( axl.gl VERSION 0.5.13 DESCRIPTION "A simple C++ OpenGL graphics library." )

# Configure
set( LIBAXLGL_SUFFIX "" )
set( LIBAXLUTIL_DIR "${CMAKE_SOURCE_DIR}/../axl.util" CACHE PATH "axl.util library source code root directory.")
set( LIBAXLMATH_DIR "${CMAKE_SOURCE_DIR}/../axl.math" CACHE PATH "axl.math library source code root directory.")
set( LIBAXLGLW_DIR "${CMAKE_SOURCE_DIR}/../axl.glw" CACHE PATH "axl.glw library source code root directory.")
set( CMAKE_CXX_STANDARD 11 CACHE STRING "C++ compiler standard.")
set( LIBAXLGL_TYPE STATIC CACHE STRING "Library type." )
set( HEADERS_INSTALL_DIR "include" CACHE PATH "Relative path for header files to install." )
set( ARCHIVES_INSTALL_DIR "lib" CACHE PATH "Relative path for library archives to install." )
set( BINARY_INSTALL_DIR "bin" CACHE PATH "Relative path for runtime binaries to install." )
set( LIBAXLGL_EXPORT_DIR "${PROJECT_BINARY_DIR}/tests" CACHE PATH "Binary directory relative path for runtime binaries to build to." )
set( INSTALL_HEADERS ON CACHE BOOL "" )
set( INSTALL_ARCHIVES ON CACHE BOOL "" )
set( INSTALL_BINARIES ON CACHE BOOL "" )
set( LIBAXLGL_BUILD_TESTS OFF CACHE BOOL "" )
set( LIBAXLGL_PRINT_CONFIGS OFF CACHE BOOL "" )

if( LIBAXLGL_PRINT_CONFIGS )
	message( NOTICE "LIBAXLUTIL_DIR:= ${LIBAXLUTIL_DIR}" )
	message( NOTICE "LIBAXLMATH_DIR:= ${LIBAXLMATH_DIR}" )
	message( NOTICE "LIBAXLGLW_DIR:= ${LIBAXLGLW_DIR}" )
	message( NOTICE "CMAKE_CXX_STANDARD:= ${CMAKE_CXX_STANDARD}" )
	message( NOTICE "LIBAXLGL_TYPE:= ${LIBAXLGL_TYPE}" )
	message( NOTICE "CMAKE_BUILD_TYPE:= ${CMAKE_BUILD_TYPE}" )
	message( NOTICE "HEADERS_INSTALL_DIR:= ${HEADERS_INSTALL_DIR}" )
	message( NOTICE "ARCHIVES_INSTALL_DIR:= ${ARCHIVES_INSTALL_DIR}" )
	message( NOTICE "BINARY_INSTALL_DIR:= ${BINARY_INSTALL_DIR}" )
	message( NOTICE "CMAKE_INSTALL_PREFIX:= ${CMAKE_INSTALL_PREFIX}" )
	message( NOTICE "LIBAXLGL_EXPORT_DIR:= ${LIBAXLGL_EXPORT_DIR}" )
	message( NOTICE "INSTALL_HEADERS:= ${INSTALL_HEADERS}" )
	message( NOTICE "INSTALL_ARCHIVES:= ${INSTALL_ARCHIVES}" )
	message( NOTICE "INSTALL_BINARIES:= ${INSTALL_BINARIES}" )
	message( NOTICE "LIBAXLGL_BUILD_TESTS:= ${LIBAXLGL_BUILD_TESTS}" )
endif()

if( "${CMAKE_BUILD_TYPE}" MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
	add_compile_definitions( DEBUG )
elseif( "${CMAKE_BUILD_TYPE}" MATCHES "[Rr][Ee][Ll]" )
	add_compile_definitions( NDEBUG )
endif()

include_directories( include )

add_subdirectory( src "axl.gl" )
if( LIBAXLGL_BUILD_TESTS )
	add_subdirectory( tests "tests" )
endif()

# install headers
if( INSTALL_HEADERS )
	install( FILES
		"include/axl.gl/lib.hpp"
		"include/axl.gl/Application.hpp"
		"include/axl.gl/KeyCodes.hpp"
		"include/axl.gl/KeyMap.hpp"
		"include/axl.gl/View.hpp"
		"include/axl.gl/Context.hpp"
		DESTINATION "${INSTALL_INCLUDE_DIR}/axl.gl"
	)
endif()
