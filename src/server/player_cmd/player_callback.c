/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_callback.c
*/

#include "player_callback.h"

void	player_callback_new_player(va_list *args){(void)args;}
void	player_callback_explusion(va_list *args){(void)args;}
void	player_callback_broadcast(va_list *args){(void)args;}
void	player_callback_start_incantation(va_list *args){(void)args;}
void	player_callback_end_incantation(va_list *args){(void)args;}
void	player_callback_egg_laying(va_list *args){(void)args;}
void	player_callback_resource_dropping(va_list *args){(void)args;}
void	player_callback_resource_collecting(va_list *args){(void)args;}
void	player_callback_death_player(va_list *args){(void)args;}
void	player_callback_egg_laid_by_player(va_list *args){(void)args;}
void	player_callback_egg_hatching(va_list *args){(void)args;}
void	player_callback_player_connection_egg(va_list *args){(void)args;}
void	player_callback_end_of_game(va_list *args){(void)args;}
void	player_callback_message_from_server(va_list *args){(void)args;}
void	player_callback_unknown_command(va_list *args){(void)args;}
void	player_callback_command_paramete(va_list *args){(void)args;}

static const client_callback_t	CLIENT_CALLBACKS[] = {
	{ CB_DEATH_PLAYER, player_callback_death_player,
		"death of a player" },
};

static const client_callback_t	SPECTATOR_CALLBACKS[] = {
	{ CB_NEW_PLAYER, player_callback_new_player,
		"connection of a new player" },
	{ CB_EXPLUSION, player_callback_explusion,
		"explusion" },
	{ CB_BROADCAST, player_callback_broadcast,
		"broadcast" },
	{ CB_START_INCANTATION, player_callback_start_incantation,
		"start of an incantation (by the first player)" },
	{ CB_END_INCANTATION, player_callback_end_incantation,
		"end of an incantation" },
	{ CB_EGG_LAYING, player_callback_egg_laying,
		"egg laying by the player" },
	{ CB_RESOURCE_DROPPING, player_callback_resource_dropping,
		"resource dropping" },
	{ CB_RESOURCE_COLLECTING, player_callback_resource_collecting,
		"resource collecting" },
	{ CB_DEATH_PLAYER, player_callback_death_player,
		"death of a player" },
	{ CB_EGG_LAID_BY_PLAYER, player_callback_egg_laid_by_player,
		"an egg was laid by a player" },
	{ CB_EGG_HATCHING, player_callback_egg_hatching,
		"egg hatching" },
	{ CB_PLAYER_CONNECTION_EGG, player_callback_player_connection_egg,
		"player connection for an egg" },
	{ CB_END_OF_GAME, player_callback_end_of_game,
		"end of game" },
	{ CB_MESSAGE_FROM_SERVER, player_callback_message_from_server,
		"message from the server" },
	{ CB_UNKNOWN_COMMAND, player_callback_unknown_command,
		"unknown command" },
	{ CB_COMMAND_PARAMETER, player_callback_command_paramete,
		"command parameter" }
};

void	player_callback(callback_type_t type, ...)
{
	va_list	vargs;
	const client_callback_t	*c = NULL;
	int max_el = sizeof(CLIENT_CALLBACKS) / sizeof(client_callback_t);

	for (int i = 0; i < max_el; ++i) {
		if (type == CLIENT_CALLBACKS[i].type) {
			c = &CLIENT_CALLBACKS[i];
			break;
		}
	}
	va_start(vargs, type);
	if (c) {
		c->fct(&vargs);
	}
	va_end(vargs);
}

void	spectate_callback(callback_type_t type, ...)
{
	va_list	vargs;
	const client_callback_t	*c = NULL;
	int max_el = sizeof(SPECTATOR_CALLBACKS) / sizeof(client_callback_t);

	for (int i = 0; i < max_el; ++i) {
		if (type == SPECTATOR_CALLBACKS[i].type) {
			c = &SPECTATOR_CALLBACKS[i];
			break;
		}
	}
	va_start(vargs, type);
	if (c) {
		c->fct(&vargs);
	}
	va_end(vargs);
}
