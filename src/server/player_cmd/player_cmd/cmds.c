/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** cmds.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_error(player_cmd_arg_t *args)
{(void)args;DEBUG("%s", __func__);}

void	player_cmd_forward(player_cmd_arg_t *args)
{
	player_move(args->player);
	client_callback(CB_OK, args->client);
}

void	player_cmd_right(player_cmd_arg_t *args)
{
	player_turn_right(args->player);
	client_callback(CB_OK, args->client);
}

void	player_cmd_left(player_cmd_arg_t *args)
{
	player_turn_left(args->player);
	client_callback(CB_OK, args->client);
}

void	player_cmd_look(player_cmd_arg_t *args)
{
	(void)args;DEBUG("%s", __func__);
	//todo_alex
}

void	player_cmd_inventory(player_cmd_arg_t *args)
{
	(void)args;DEBUG("%s", __func__);
	//todo inv
}

void	player_cmd_broadcast(player_cmd_arg_t *args)
{
	//todo broadcast
	client_callback(CB_OK, args->client);
}

void	player_cmd_connect_nbr(player_cmd_arg_t *args)
{
	client_callback(CB_NB_UNUSED_SLOTS, args->client,
		team_available_players((team_t *)args->player->team));
}

void	player_cmd_fork(player_cmd_arg_t *args)
{
	//todo fork
	client_callback(CB_OK, args->client);
}

void	player_cmd_eject(player_cmd_arg_t *args)
{
	//todo eject
	client_callback(CB_OK, args->client);
}

void	player_cmd_take(player_cmd_arg_t *args)
{
	//todo take object
	client_callback(CB_OK, args->client);
}

void	player_cmd_set_obj_down(player_cmd_arg_t *args)
{
	//todo set obj down
	client_callback(CB_OK, args->client);
}

void	player_cmd_incantation(player_cmd_arg_t *args)
{
	client_callback(CB_ELEVATION_UNDERWAY, args->client);
}

void	spectate_cmd_map_size(player_cmd_arg_t *args)
{
	client_callback(CB_MAP_SIZE, args->client,
		args->server->map->size.x, args->server->map->size.y);
}

void	spectate_cmd_map_content_tile(player_cmd_arg_t *args)
{
	point_t	point = { atoi(args->args[0]), atoi(args->args[1]) };
	map_content_t *c = map_content_at(args->server->map, point);

	client_callback(CB_CONTENT_TILE, args->client,
		point.x, point.y,
		c->inventory.food,
		c->inventory.stones[LINEMATE],
		c->inventory.stones[DERAUMERE],
		c->inventory.stones[SIBUR],
		c->inventory.stones[MENDIANE],
		c->inventory.stones[PHIRAS],
		c->inventory.stones[THYSTAME]);
}

void	spectate_cmd_content_map(player_cmd_arg_t *args)
{
	//todo content map
	(void)args;DEBUG("%s", __func__);
}

void	spectate_cmd_name_teams(player_cmd_arg_t *args)
{
	//todo name teams
	(void)args;DEBUG("%s", __func__);
}

void	spectate_cmd_player_pos(player_cmd_arg_t *args)
{
	//todo player pos
	(void)args;DEBUG("%s", __func__);
}

void	spectate_cmd_player_level(player_cmd_arg_t *args)
{
	//todo player level
	(void)args;DEBUG("%s", __func__);
}

void	spectate_cmd_player_inventory(player_cmd_arg_t *args)
{
	//todo player inv
	(void)args;DEBUG("%s", __func__);
}

void	spectate_cmd_time_unit(player_cmd_arg_t *args)
{
	//todo replace time unit
	client_callback(CB_TIME_UNIT_REQUEST, args->client, 1);
}

void	spectate_cmd_time_unit_mod(player_cmd_arg_t *args)
{
	//todo replace time unit + change time unit
	client_callback(CB_TIME_UNIT_REQUEST, args->client, 1);
}
