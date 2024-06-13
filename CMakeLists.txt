cmake_minimum_required(VERSION 3.19)
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)

# Include the ipasir2-cpp library
add_subdirectory(ipasir2-cpp)

# Add your executable or library
add_executable(MyExecutable testsat.cpp)

# Link ipasir2cpp library
target_link_libraries(MyExecutable PRIVATE ipasir2cpp)

# Optionally, set additional compiler options if necessary
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

# Enable testing if needed
enable_testing()
