##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	=	zappy_client
MAIN	=	main.cpp
SRC	=	Display/IrrlichtDisplay.cpp			\
		Display/IrrlichtDisplayPlayer.cpp		\
		Hud/Button.cpp					\
		Hud/ButtonManager.cpp				\
		Hud/EditBox.cpp					\
		Hud/GUI.cpp					\
		Hud/Image.cpp					\
		Hud/ImageManager.cpp				\
		Hud/ListBox.cpp					\
		Hud/Menu.cpp					\
		Hud/Rectangle.cpp				\
		Hud/ScrollBar.cpp				\
		Hud/ServPanel.cpp				\
		Hud/SrvClient.cpp				\
		Hud/Table.cpp					\
		Hud/utils.cpp					\
		Hud/SoundManager.cpp				\
		Manager/Buffer.cpp				\
		Manager/Manager.cpp				\
		Manager/Map.cpp					\
		Manager/Player.cpp				\
		Manager/parseMe.cpp				\
		Manager/Egg.cpp					\
		reseau/Client.cpp				\
		reseau/Select.cpp				\
		ServerHandler/ChildHandler.cpp			\
		ServerHandler/ServerHandler.cpp			\
		Utils/Clock.cpp					\
		Utils/Debug.cpp					\
		Utils/Direction.cpp				\
		Utils/Math.cpp					\
		Utils/Point.cpp

INC	=	-I include			\
		-I Display			\
		-I Hud				\
		-I Manager			\
		-I reseau			\
		-I ServerHandler	\
		-I Utils		\
		-I lib/include
F	=	-W -Wall -Werror -Wextra

NAM_OBJ	=	$(MAIN:.cpp=.o)
OBJ	=	$(SRC:.cpp=.o)

LIB		= -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -L lib -lIrrKlang lib/libIrrKlang.so

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
