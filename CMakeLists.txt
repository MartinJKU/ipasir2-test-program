cmake_minimum_required(VERSION 3.19)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(deps/ipasir2-cpp)

add_executable(MyExecutable testsat.cpp)

target_link_libraries(MyExecutable PRIVATE ipasir2cpp $ENV{SAT_SOLVER_LIB})
message(STATUS "Linked SAT solver libraries: $ENV{SAT_SOLVER_LIB}")

if (NOT WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_link_libraries(MyExecutable PRIVATE atomic)
endif()

if (MSVC)
  target_compile_options(MyExecutable PRIVATE
    /DNOMINMAX
    /permissive-
    /W4
    /wd4267
    /wd4244
  )
else()
  target_compile_options(MyExecutable PRIVATE
    -Wall
    -Wextra
    -Wunused
    -Warray-bounds
    -pedantic
  )
endif()
