cmake_minimum_required(VERSION 3.9)
project(zappy)

set(CMAKE_CXX STANDARD 14)

include_directories(src/client/Display src/client/Hud src/client/Manager src/client/reseau src/client/Utils)

set(SRCTOOLS
        src/client/main.cpp
        src/client)

add_executable(zappy ${SRCTOOLS})