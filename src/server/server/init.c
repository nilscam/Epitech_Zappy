/*
** EPITECH PROJECT, 2018
** init
** File description:
** init
*/

#include "server.h"

void		init_server_functions(t_server *this)
{
	this->init = &init_server;
	this->select = &prepare_select;
	this->can_read = &can_read;
	this->can_write = &can_write;
	this->can_err = &can_err;
	this->add_client = &add_client;
	this->write = &put_server;
	this->stop = &stop_server;
}

t_server	*init_struct_server(map_t *map, double f)
{
	t_server	*this = malloc(sizeof(t_server));

	if (!this || !map || !INIT(ZCLOCK, this->zclock))
		return (NULL);
	this->_fd_server = -1;
	this->map = map;
	this->f = f;
	this->anonymous_clients = NEW(LIST);
	this->players_clients = NEW(LIST);
	this->spectators_clients = NEW(LIST);
	this->teams = NEW(LIST);
	if (!this->anonymous_clients
		|| !this->players_clients
		|| !this->spectators_clients
		|| !this->teams)
		return (NULL);
	init_server_functions(this);
	return (this);
}
