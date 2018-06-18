##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	=	zappy_client
MAIN	=	main.cpp
SRC	=		Manager/Buffer.cpp					\
			Manager/Manager.cpp					\
			Manager/parseMe.cpp					\
			reseau/Client.cpp					\
			reseau/Select.cpp

INC	=	-I include		\
		-I Manager		\
		-I reseau
F	=	-W -Wall -Werror -Wextra

NAM_OBJ	=	$(MAIN:.cpp=.o)
OBJ	=	$(SRC:.cpp=.o)

G++	=	g++ -std=c++14 -g3 -o

all:		$(NAME)

$(NAME):	$(NAM_OBJ) $(OBJ)
		$(G++) $@ $^ $(LIB)

%.o:		%.cpp
		$(G++) $@ $(F) $(FF) $(INC) -c $<

clean:
		rm -f $(NAM_OBJ) $(OBJ) $(NAME)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
