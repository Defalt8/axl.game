cmake_minimum_required( VERSION 3.17 )

project( axl.game VERSION 0.9.31 DESCRIPTION "A simple C++ OpenGL graphics library." )

# Configure
set( LIBAXLGAME_SUFFIX "" )
set( LIBAXLUTIL_DIR "${CMAKE_SOURCE_DIR}/../axl.util" CACHE PATH "axl.util library source code root directory.")
set( LIBAXLMATH_DIR "${CMAKE_SOURCE_DIR}/../axl.math" CACHE PATH "axl.math library source code root directory.")
set( LIBAXLGLW_DIR "${CMAKE_SOURCE_DIR}/../axl.glw" CACHE PATH "axl.glw library source code root directory.")
set( CMAKE_CXX_STANDARD 11 CACHE STRING "C++ compiler standard.")
set( LIBAXLGAME_TYPE STATIC CACHE STRING "Library type." )
set( HEADERS_INSTALL_DIR "include" CACHE PATH "Relative path for header files to install." )
set( ARCHIVES_INSTALL_DIR "lib" CACHE PATH "Relative path for library archives to install." )
set( BINARY_INSTALL_DIR "bin" CACHE PATH "Relative path for runtime binaries to install." )
set( LIBAXLGAME_EXPORT_DIR "${PROJECT_BINARY_DIR}/tests" CACHE PATH "Binary directory relative path for runtime binaries to build to." )
set( INSTALL_HEADERS ON CACHE BOOL "" )
set( INSTALL_ARCHIVES ON CACHE BOOL "" )
set( INSTALL_BINARIES ON CACHE BOOL "" )
set( BUILD_TESTS OFF CACHE BOOL "" )
set( LIBAXLGAME_INSTALL_HEADERS ON CACHE BOOL "" )
set( LIBAXLGAME_INSTALL_ARCHIVES ON CACHE BOOL "" )
set( LIBAXLGAME_INSTALL_BINARIES ON CACHE BOOL "" )
set( LIBAXLGAME_BUILD_TESTS ON CACHE BOOL "" )
set( LIBAXLGAME_PRINT_CONFIGS OFF CACHE BOOL "" )
# dependencies configurations
set( LIBAXLUTIL_BUILD_TESTS OFF CACHE BOOL "")
set( LIBAXLUTIL_INSTALL_HEADERS OFF CACHE BOOL "")
set( LIBAXLUTIL_INSTALL_ARCHIVES OFF CACHE BOOL "")
set( LIBAXLUTIL_INSTALL_BINARIES OFF CACHE BOOL "")
set( LIBAXLMATH_BUILD_TESTS OFF CACHE BOOL "")
set( LIBAXLMATH_INSTALL_HEADERS OFF CACHE BOOL "")
set( LIBAXLMATH_INSTALL_ARCHIVES OFF CACHE BOOL "")
set( LIBAXLMATH_INSTALL_BINARIES OFF CACHE BOOL "")
set( LIBAXLGLW_BUILD_TESTS OFF CACHE BOOL "")
set( LIBAXLGLW_INSTALL_HEADERS OFF CACHE BOOL "")
set( LIBAXLGLW_INSTALL_ARCHIVES OFF CACHE BOOL "")
set( LIBAXLGLW_INSTALL_BINARIES OFF CACHE BOOL "")

if( LIBAXLGAME_PRINT_CONFIGS )
	message( NOTICE "LIBAXLUTIL_DIR:= ${LIBAXLUTIL_DIR}" )
	message( NOTICE "LIBAXLMATH_DIR:= ${LIBAXLMATH_DIR}" )
	message( NOTICE "LIBAXLGLW_DIR:= ${LIBAXLGLW_DIR}" )
	message( NOTICE "CMAKE_CXX_STANDARD:= ${CMAKE_CXX_STANDARD}" )
	message( NOTICE "LIBAXLGAME_TYPE:= ${LIBAXLGAME_TYPE}" )
	message( NOTICE "CMAKE_BUILD_TYPE:= ${CMAKE_BUILD_TYPE}" )
	message( NOTICE "HEADERS_INSTALL_DIR:= ${HEADERS_INSTALL_DIR}" )
	message( NOTICE "ARCHIVES_INSTALL_DIR:= ${ARCHIVES_INSTALL_DIR}" )
	message( NOTICE "BINARY_INSTALL_DIR:= ${BINARY_INSTALL_DIR}" )
	message( NOTICE "CMAKE_INSTALL_PREFIX:= ${CMAKE_INSTALL_PREFIX}" )
	message( NOTICE "LIBAXLGAME_EXPORT_DIR:= ${LIBAXLGAME_EXPORT_DIR}" )
	message( NOTICE "INSTALL_HEADERS:= ${INSTALL_HEADERS}" )
	message( NOTICE "INSTALL_ARCHIVES:= ${INSTALL_ARCHIVES}" )
	message( NOTICE "INSTALL_BINARIES:= ${INSTALL_BINARIES}" )
	message( NOTICE "BUILD_TESTS:= ${LIBAXLGAME_BUILD_TESTS}" )
	message( NOTICE "LIBAXLGAME_INSTALL_HEADERS:= ${LIBAXLGAME_INSTALL_HEADERS}" )
	message( NOTICE "LIBAXLGAME_INSTALL_ARCHIVES:= ${LIBAXLGAME_INSTALL_ARCHIVES}" )
	message( NOTICE "LIBAXLGAME_INSTALL_BINARIES:= ${LIBAXLGAME_INSTALL_BINARIES}" )
	message( NOTICE "LIBAXLGAME_BUILD_TESTS:= ${LIBAXLGAME_BUILD_TESTS}" )
endif()

if( "${CMAKE_BUILD_TYPE}" MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
	add_compile_definitions( DEBUG )
elseif( "${CMAKE_BUILD_TYPE}" MATCHES "[Rr][Ee][Ll]" )
	add_compile_definitions( NDEBUG )
endif()

include_directories( include )

add_subdirectory( src "axl.game" )
if( BUILD_TESTS AND LIBAXLGAME_BUILD_TESTS )
	add_subdirectory( tests "tests" )
endif()

# install headers
if( INSTALL_HEADERS AND LIBAXLGAME_INSTALL_HEADERS )
	install( FILES
		"include/axl.game/lib.hpp"
		"include/axl.game/Application.hpp"
		"include/axl.game/KeyCodes.hpp"
		"include/axl.game/KeyMap.hpp"
		"include/axl.game/View.hpp"
		"include/axl.game/Context.hpp"
		DESTINATION "${HEADERS_INSTALL_DIR}/axl.game"
	)
endif()
