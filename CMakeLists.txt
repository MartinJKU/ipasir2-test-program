cmake_minimum_required(VERSION 3.19)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_MINISAT "Use Minisat solver" OFF)
option(USE_LINGELING "Use Lingeling solver" OFF)

if (USE_MINISAT)
  set(SAT_SOLVER "minisat-lib-static")
elseif (USE_LINGELING)
  set(SAT_SOLVER "lingeling-static")
endif()

add_subdirectory(deps)

add_executable(MyExecutable testsat.cpp)

target_link_libraries(MyExecutable PRIVATE ipasir2cpp ${SAT_SOLVER})

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

