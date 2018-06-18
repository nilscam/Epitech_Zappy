cmake_minimum_required(VERSION 3.9)
project(zappy C)

set(CMAKE_C_STANDARD 11)

include_directories(src/server src/server/player src/server/map src/server/utils src/server/list src/server/list_iterator src/server/big_buff)

set(SRCTOOLS
        src/server/list/list.c
        src/server/list/list_push.c
        src/server/list/list_utils.c
        src/server/list_iterator/list_iterator.c
        src/server/list_iterator/list_iterator_move.c
        src/server/list_iterator/list_iterator_ops.c
        src/server/main.c
        src/server/map/map.c
        src/server/map/inventory.c
        src/server/map/map_init.c
        src/server/map/map_it.c
        src/server/map/map_move.c
        src/server/map/map_utils.c
        src/server/map/vision.c
        src/server/player/player.c
        src/server/player/player_elevation.c
        src/server/player/player_food.c
        src/server/player/player_move.c
        src/server/player/player_time.c
        src/server/player/player_turn.c
        src/server/player/player_utils.c
        src/server/utils/debug.c
        src/server/utils/direction.c
        src/server/utils/point.c
        src/server/tests/test_vision.c)

add_executable(zappy ${SRCTOOLS})