
##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME_SERVER	=	zappy_server
NAME_AI		=	zappy_ai
NAME_CLIENT	=	zappy_client

ROOT_SERVER	=	./src/server
ROOT_AI		=	./src/ai
ROOT_CLIENT	=	./src/client

ROOT_BIN	=	.

ARGS		=

all:			$(NAME_SERVER) $(NAME_AI) $(NAME_CLIENT)

$(NAME_SERVER):
			$(MAKE) -C $(ROOT_SERVER) $(ARGS)
ifeq ($(ARGS),)
			cp $(ROOT_SERVER)/$@ $(ROOT_BIN) || true
endif

$(NAME_AI):
			$(MAKE) -C $(ROOT_AI) $(ARGS)
ifeq ($(ARGS),)
			cp $(ROOT_AI)/$@ $(ROOT_BIN) || true
endif

$(NAME_CLIENT):
			$(MAKE) -C $(ROOT_CLIENT) $(ARGS)
ifeq ($(ARGS),)
			cp $(ROOT_CLIENT)/$@ $(ROOT_BIN) || true
endif

clean:			clean_bin
			@$(MAKE) -C . ARGS='$@'

fclean:			clean_bin
			@$(MAKE) -C . ARGS='$@'

re:			fclean all

clean_bin:
			rm -f $(ROOT_BIN)/$(NAME_SERVER) $(ROOT_BIN)/$(NAME_AI) $(ROOT_BIN)/$(NAME_CLIENT)

.PHONY:			all clean fclean re clean_bin $(NAME_SERVER) $(NAME_AI) $(NAME_CLIENT)
