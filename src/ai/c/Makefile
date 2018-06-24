##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	=	zappy_ai
MAIN	=	main.c
SRC	=

INC	=	-I include
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
