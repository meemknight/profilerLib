cmake_minimum_required(VERSION 3.13)
project(profilerLib)


add_library(profilerLib INTERFACE)
target_include_directories(profilerLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")


#Define MY_SOURCES to be a list of all the source files for my game 
file(GLOB_RECURSE PROFILER_LIB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(profilerLib_demo)
target_sources(profilerLib_demo PRIVATE ${PROFILER_LIB_SOURCES} )
target_link_libraries(profilerLib_demo PUBLIC profilerLib)

