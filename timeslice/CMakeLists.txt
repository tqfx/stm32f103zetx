if(${CMAKE_TOOLCHAIN_FILE})
  include(${CMAKE_TOOLCHAIN_FILE})
endif()
cmake_minimum_required(VERSION 3.10)

project(all)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_VERBOSE_MAKEFILE OFF)

include(cmake/check.cmake OPTIONAL)
include(cmake/output.cmake OPTIONAL)
include(cmake/standard.cmake OPTIONAL)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  if(UNIX)
    include(cmake/sanitizer.cmake OPTIONAL)
  endif()
endif()

add_subdirectory(src)
add_subdirectory(test)
