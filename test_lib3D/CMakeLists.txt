cmake_minimum_required(VERSION 3.9)
project(testgraph)

set(CMAKE_CXX_STANDARD 14)

SET(GCC_COVERAGE_COMPILE_FLAGS "-W -Wall -Wextra -Werror")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(a.out test_zappy.cpp test_zappy.hpp IrrlichtDisplay.cpp IrrlichtDisplay.hpp)
# En 1er nom exécutable puis .cpp/hpp
