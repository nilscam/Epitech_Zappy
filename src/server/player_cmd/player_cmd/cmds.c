/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** cmds.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"

void	anonymous_cmd_anonymous(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{
	(void)args;(void)server;(void)client;DEBUG("%s", __func__);
}

void	anonymous_cmd_spectator(
	__attribute__((unused))player_cmd_arg_t *args,
	client_t *client, t_server *server)
{
	client_callback(CB_WELCOME_SPECTATOR, client);
	client->type = CLIENT_SPECTATOR;
	list_push_back(server->spectators, client);
}

void	player_cmd_error(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_forward(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_right(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_left(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_look(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_inventory(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_broadcast(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_connect_nbr(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_fork(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_eject(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_take(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_set_obj_down(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	player_cmd_incantation(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_map_size(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_map_content_time(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_content_map(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_name_teams(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_player_pos(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_player_level(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_player_inventory(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_time_unit(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
void	spectate_cmd_time_unit_mod(player_cmd_arg_t *args,
	client_t *client, t_server *server)
{(void)args;(void)server;(void)client;DEBUG("%s", __func__);}
