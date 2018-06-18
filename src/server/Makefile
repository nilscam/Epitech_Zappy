##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	=	zappy_server
MAIN	=	main.c
SRC	=	big_buff/big_buff.c					\
		buffer/circular_buffer.c				\
		class/class.c						\
		class/class_utils.c					\
		client/client_read.c					\
		client/client_write.c					\
		client/client.c						\
		egg/egg_hatch.c						\
		egg/egg.c						\
		list/list_extract.c					\
		list/list_get.c						\
		list/list_pop.c						\
		list/list_push.c					\
		list/list_utils.c					\
		list/list.c						\
		list_iterator/list_iterator_it.c			\
		list_iterator/list_iterator_move.c			\
		list_iterator/list_iterator_ops.c			\
		list_iterator/list_iterator.c				\
		map/elevation.c						\
		map/inventory.c						\
		map/map_egg.c						\
		map/map_init.c						\
		map/map_it.c						\
		map/map_move.c						\
		map/map_remove.c					\
		map/map_sound.c						\
		map/map_utils.c						\
		map/map.c						\
		map/stat.c						\
		map/vision.c						\
		parsing/help.c						\
		parsing/parsing.c					\
		parsing/get_infos.c					\
		player/player_elevation.c				\
		player/player_food.c					\
		player/player_move.c					\
		player/player_time.c					\
		player/player_turn.c					\
		player/player_utils.c					\
		player/player.c						\
		player_cmd/player_callback/send_format.c		\
		player_cmd/player_callback/start_incantation.c		\
		player_cmd/player_cmd/anonymous_cmd.c			\
		player_cmd/player_cmd/broadcast.c			\
		player_cmd/player_cmd/connect_nbr.c			\
		player_cmd/player_cmd/content_map.c			\
		player_cmd/player_cmd/eject.c				\
		player_cmd/player_cmd/error.c				\
		player_cmd/player_cmd/fork.c				\
		player_cmd/player_cmd/forward.c				\
		player_cmd/player_cmd/incantation.c			\
		player_cmd/player_cmd/inventory.c			\
		player_cmd/player_cmd/left.c				\
		player_cmd/player_cmd/look.c				\
		player_cmd/player_cmd/map_content_tile.c		\
		player_cmd/player_cmd/map_size.c			\
		player_cmd/player_cmd/name_teams.c			\
		player_cmd/player_cmd/player_inventory.c		\
		player_cmd/player_cmd/player_level.c			\
		player_cmd/player_cmd/player_pos.c			\
		player_cmd/player_cmd/right.c				\
		player_cmd/player_cmd/set_obj_down.c			\
		player_cmd/player_cmd/take.c				\
		player_cmd/player_cmd/time_unit_mod.c			\
		player_cmd/player_cmd/time_unit.c			\
		player_cmd/player_callback.c				\
		player_cmd/player_cmd.c					\
		save_signal/save_signal.c				\
		server/add_team.c					\
		server/clients_add.c					\
		server/clients_remove.c					\
		server/deinit.c						\
		server/handle_eggs.c					\
		server/handle_players.c					\
		server/handle_tcp_clients.c				\
		server/handle_tcp_server.c				\
		server/init.c						\
		server/select_is_set.c					\
		server/select.c						\
		server/server.c						\
		server/write.c						\
		team/team_find.c					\
		team/team_utils.c					\
		team/team.c						\
		tests/test_big_buff.c					\
		tests/test_list_extract.c				\
		tests/test_list.c					\
		tests/test_map_it.c					\
		tests/test_map_sound.c					\
		tests/test_map.c					\
		tests/test_parsing.c					\
		tests/test_player_move.c				\
		tests/test_player.c					\
		tests/test_tcp_connection.c				\
		tests/test_unique_id.c					\
		tests/test_vision.c					\
		tests/test_zclock.c					\
		tests/tests.c						\
		unique_id/unique_id.c					\
		utils/debug.c						\
		utils/direction_to_int.c				\
		utils/direction.c					\
		utils/math_utils.c					\
		utils/point.c						\
		utils/str_concat.c					\
		utils/str_to_tab.c					\
		zclock/zclock_mark.c					\
		zclock/zclock_wait.c					\
		zclock/zclock.c

INC	=	-I .			\
		-I big_buff		\
		-I buffer		\
		-I class		\
		-I client		\
		-I egg			\
		-I list			\
		-I list_iterator	\
		-I map			\
		-I parsing		\
		-I player		\
		-I player_cmd		\
		-I save_signal		\
		-I server		\
		-I team			\
		-I tests		\
		-I unique_id		\
		-I utils		\
		-I zclock
F	=	-W -Wall -Werror -Wextra

LIB	=	-lm

NAM_OBJ	=	$(MAIN:.c=.o)
OBJ	=	$(SRC:.c=.o)

GCC	=	gcc -g3 -o

all:		$(NAME)

$(NAME):	$(NAM_OBJ) $(OBJ)
		$(GCC) $@ $^ $(LIB)

%.o:		%.c
		$(GCC) $@ $(F) $(FF) $(INC) -c $<

clean:
		rm -f $(NAM_OBJ) $(OBJ) $(NAME)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
