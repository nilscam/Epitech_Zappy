cmake_minimum_required(VERSION 3.9)
project(zappy C)

set(CMAKE_C_STANDARD 11)

set(SRCTOOLS src/server/c_modular.c src/server/debug.c src/server/list.c src/server/list_iterator.c src/server/main.c src/server/map.c)

add_executable(zappy ${SRCTOOLS})