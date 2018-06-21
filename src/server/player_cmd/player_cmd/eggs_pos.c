/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eggs_pos.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include <egg.h>

static void	show_egg(egg_t *egg, va_list *args)
{
	client_t	*spectator = va_arg(*args, client_t *);

	client_callback(CB_EGG_POSITION, spectator,
		egg->id,
		egg->pos->pos.x,
		egg->pos->pos.y);
}

void	spectate_cmd_eggs_pos(player_cmd_arg_t *args)
{
	list_it_all(args->server->map->eggs,
		(list_it_fct_t)show_egg, args->client);
}
