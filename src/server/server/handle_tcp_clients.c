/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_tcp_clients.c
*/

#include "server.h"
#include "player.h"
#include "player_cmd.h"

static bool	check_client_to_kill(t_server *server,
	client_t *client, player_t *player)
{
	if (client->kill_me && list_is_empty(client->write_buff)) {
		if (client->type == CLIENT_PLAYER) {
			remove_player(server, player);
		} else {
			client_delete(client);
		}
		return true;
	}
	return false;
}

static bool	client_handle(t_server *server,
	client_t *client, player_t *player)
{
	char		*cmd;
	client_type_t	type;
	bool		remove_it = false;

	cmd = client_extract_cmd(client);
	if (cmd && *cmd) {
		DEBUG("cmd from fd %d: '%s'", client->_fd, cmd);
		type = client->type;
		client_cmd(server, client, cmd, player);
		if (type != client->type) {
			remove_it = true;
		}
	}
	SAFE_FREE(cmd);
	return remove_it;
}

static bool	check_tcp_client(client_t *client, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);

	if (server->can_read(server, client->_fd)) {
		if (!client_read(client)) {
			client_delete(client);
			return true;
		}
	}
	if (server->can_write(server, client->_fd)) {
		client_write(client);
	}
	return client_handle(server, client, NULL)
		|| check_client_to_kill(server, client, NULL);
}

static bool	check_tcp_player(player_t *pl, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);
	bool		handle = false;

	if (server->can_read(server, pl->client->_fd)) {
		if (!client_read(pl->client)) {
			remove_player(server, pl);
			return true;
		}
	}
	if (server->can_write(server, pl->client->_fd)) {
		client_write(pl->client);
	}
	if (!player_is_busy(pl)) {
		handle = client_handle(server, pl->client, pl);
	}
	if (!handle) {
		handle = check_client_to_kill(server, pl->client, pl);
	}
	return handle;
}

void	handle_tcp_clients(t_server *server)
{
	list_it_fct_remove_t cfct = (list_it_fct_remove_t)check_tcp_client;
	list_it_fct_remove_t pfct = (list_it_fct_remove_t)check_tcp_player;

	list_it_remove(server->spectators_clients, cfct, server);
	list_it_remove(server->map->players, pfct, server);
	list_it_remove(server->anonymous_clients, cfct, server);
}
