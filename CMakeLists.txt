# Lowest CMake version
cmake_minimum_required(VERSION 3.10)
project(raftkvdatabase)

# Define cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# Find and include Boost
set(BOOST_ROOT "D:/CPP_Third_Lib/boost_1_87_0")
find_package(Boost REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Collect source files
file(GLOB SRC_FILES src/*.cpp)

# Add executable and link Boost libraries
add_executable(raftKVcpp main.cpp ${SRC_FILES})
target_link_libraries(raftKVcpp ${Boost_LIBRARIES})
