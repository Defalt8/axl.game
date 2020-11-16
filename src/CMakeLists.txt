cmake_minimum_required( VERSION 3.17 )

# Library
add_library( axl.gl ${LIB_TYPE}
	"lib.cpp"
)
# Target compile definitions
if( "${LIB_TYPE}" STREQUAL "SHARED" )
	target_compile_definitions( axl.gl PRIVATE BUILD_SHARED )
elseif( "${LIB_TYPE}" STREQUAL "MODULE" )
	target_compile_definitions( axl.gl PRIVATE BUILD_MODULE )
endif()
# Target properties
set_target_properties( axl.gl PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)
if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
	set_target_properties( axl.gl PROPERTIES
		ARCHIVE_OUTPUT_NAME axl.gld
		LIBRARY_OUTPUT_NAME axl.gld
		RUNTIME_OUTPUT_NAME axl.glrd
	)
else()
	set_target_properties( axl.gl PROPERTIES
		ARCHIVE_OUTPUT_NAME axl.gl
		LIBRARY_OUTPUT_NAME axl.gl
		RUNTIME_OUTPUT_NAME axl.glr
	)
endif()