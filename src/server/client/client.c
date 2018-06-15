/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.c
*/

#include "client.h"

client_t	*client_new(int fd, client_type_t type)
{
	client_t	*client = malloc(sizeof(client_t));

	if (client) {
		client->_fd = fd;
		client->read_buff = NEW(LIST);
		client->write_buff = NEW(LIST);
		if (!client->read_buff || !client->write_buff)
			return NULL;
		client->type = type;
	}
	return client;
}

void	client_delete(client_t *self)
{
	if (self) {
		list_clear(self->read_buff, free);
		list_clear(self->write_buff, free);
		SAFE_DELETE(self->read_buff);
		SAFE_DELETE(self->write_buff);
		if (self->_fd >= 0) {
			close(self->_fd);
			self->_fd = -1;
		}
		free(self);
	}
}
