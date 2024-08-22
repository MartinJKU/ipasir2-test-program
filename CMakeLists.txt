cmake_minimum_required(VERSION 3.19)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT DEFINED SAT_SOLVER_LIB_DIR)
  message(FATAL_ERROR "SAT_SOLVER_LIB_DIR not defined")
endif()

include_directories(${SAT_SOLVER_LIB_DIR}/../include)

add_subdirectory(deps/ipasir2-cpp)

add_executable(MyExecutable testsat.cpp)

file(GLOB SAT_SOLVER_LIBS "${SAT_SOLVER_LIB_DIR}/*.so")
target_link_libraries(MyExecutable PRIVATE ipasir2cpp ${SAT_SOLVER_LIBS})
message(STATUS "Linked SAT solver libraries: ${SAT_SOLVER_LIBS}")

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
