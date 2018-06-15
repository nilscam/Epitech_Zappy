/*
** EPITECH PROJECT, 2018
** init
** File description:
** init
*/

#include "tcp_connection.h"

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

t_server	*init_struct_server(list_t *players, map_t *map)
{
	t_server	*this = malloc(sizeof(t_server));

	if (!this)
		return (NULL);
	this->players = players;
	this->spectators = NEW(LIST);
	this->_fd_server = -1;
	this->map = map;
	init_server_functions(this);
	return (this);
}