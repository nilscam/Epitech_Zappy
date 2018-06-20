##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	=	zappy_client
MAIN	=	main.c
SRC	=	circular_buffer.c		\
		init_client.c			\
		init.c			\
		select_is_set.c		\
		select.c			\
		stop_client.c			\
		write.c

INC	=	-I .
F	=	-W -Wall -Werror -Wextra

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