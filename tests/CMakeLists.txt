cmake_minimum_required( VERSION 3.17 )

link_libraries( axl.gl )

add_executable( lib "lib.cpp" )
add_executable( application "Application.cpp" )
add_executable( view "View.cpp" )
add_executable( context "Context.cpp" )