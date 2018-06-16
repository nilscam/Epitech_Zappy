/*
** EPITECH PROJECT, 2018
** clients_remove
** File description:
** clients_remove
*/

#include "server.h"

static bool	remove_client_it(client_t *client, va_list *args)
{
	int	fd = va_arg(*args, int);
	bool	delete_it = va_arg(*args, int);

	if (fd == client->_fd) {
		if (delete_it) {
			client_delete(client);
		}
		return true;
	}
	return false;
}

void	remove_client_from_list(t_server *server,
	client_t *client, bool delete_it)
{
	list_t *list = NULL;

	if (client->type == CLIENT_PLAYER)
		list = server->players_clients;
	if (client->type == CLIENT_ANONYMOUS)
		list = server->anonymous_clients;
	if (client->type == CLIENT_SPECTATOR)
		list = server->spectators_clients;
	if (list) {
		list_it_remove(list,
			(list_it_fct_remove_t)remove_client_it,
			client->_fd, delete_it);
	}
}

void	stop_server(t_server *this)
{
	DEBUG("stop_server");
	if (this->_fd_server >= 0) {
		close(this->_fd_server);
		this->_fd_server = -1;
	}
}