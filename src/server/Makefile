##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	=	zappy_server
MAIN	=	main.c
SRC	=	buffer/circular_buffer.c				\
		class/class.c						\
		class/class_utils.c					\
		client/client_read.c					\
		client/client_write.c					\
		client/client.c						\
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
		map/inventory.c						\
		map/map_init.c						\
		map/map_it.c						\
		map/map_move.c						\
		map/map_remove.c					\
		map/map_sound.c						\
		map/map_utils.c						\
		map/map.c						\
		map/vision.c						\
		parsing/help.c						\
		parsing/main.c						\
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
		player_cmd/player_cmd/cmds.c				\
		player_cmd/player_callback.c				\
		player_cmd/player_cmd.c					\
		save_signal/save_signal.c				\
		tcp_connection/add_team.c				\
		tcp_connection/clients_add.c				\
		tcp_connection/clients_remove.c				\
		tcp_connection/deinit.c					\
		tcp_connection/init.c					\
		tcp_connection/main.c					\
		tcp_connection/select_is_set.c				\
		tcp_connection/select.c					\
		tcp_connection/server.c					\
		tcp_connection/write.c					\
		team/team.c						\
		tests/test_list_extract.c				\
		tests/test_list.c					\
		tests/test_map_it.c					\
		tests/test_map_sound.c					\
		tests/test_map.c					\
		tests/test_player_move.c				\
		tests/test_player.c					\
		tests/test_vision.c					\
		utils/debug.c						\
		utils/direction.c					\
		utils/math_utils.c					\
		utils/point.c						\
		utils/str_concat.c					\
		utils/str_to_tab.c

INC	=	-I .			\
		-I buffer		\
		-I class		\
		-I client		\
		-I list			\
		-I list_iterator	\
		-I map			\
		-I parsing		\
		-I player		\
		-I player_cmd		\
		-I save_signal		\
		-I tcp_connection	\
		-I team			\
		-I tests		\
		-I utils
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
