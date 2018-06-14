/*
** EPITECH PROJECT, 2018
** init
** File description:
** init
*/

#include "tcp_connection_client.h"

void		init_client_functions(t_client *this)
{
	this->init = &init_client;
	this->select = &prepare_select;
	this->can_read = &can_read;
	this->can_write = &can_write;
	this->can_err = &can_err;
	this->write = &put_client;
	this->stop = &stop_client;
}

t_client	*init_struct_client(void)
{
	t_client	*this = malloc(sizeof(t_client));

	if (!this)
		return (NULL);
	this->_fd_server = -1;
	buff_init(&this->_cbuf, SIZE_BUFF);
	init_client_functions(this);
	return (this);
}