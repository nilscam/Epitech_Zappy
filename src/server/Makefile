##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	=	zappy_server
MAIN	=	main.c
SRC	=	c_modular/c_modular.c					\
		list/list_push.c					\
		list/list_utils.c					\
		list/list.c						\
		list_iterator/list_iterator_move.c			\
		list_iterator/list_iterator_ops.c			\
		list_iterator/list_iterator.c				\
		map/inventory.c						\
		map/map_init.c						\
		map/map.c						\
		player/player_utils.c					\
		player/player.c						\
		tests/test_list.c					\
		tests/test_map.c					\
		tests/test_player.c					\
		utils/debug.c						\
		main.c

INC	=	-I .			\
		-I c_modular		\
		-I list			\
		-I list_iterator	\
		-I map			\
		-I player		\
		-I tests		\
		-I utils
F	=	-W -Wall -Werror -Wextra

NAM_OBJ	=	$(MAIN:.c=.o)
OBJ	=	$(SRC:.c=.o)

GCC	=	gcc -o

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
