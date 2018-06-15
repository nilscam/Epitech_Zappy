/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.c
*/

#include "client.h"

client_t	*client_new(int fd, bool is_spectator)
{
	client_t	*client = malloc(sizeof(client_t));

	if (client) {
		client->_fd = fd;
		buff_init(&client->_cbuf, SIZE_BUFF);
		client->accept_client_callback = !is_spectator;
		client->accept_spectate_callback = is_spectator;
	}
	return client;
}

void	client_delete(client_t *self)
{
	if (self) {
		SAFE_FREE(self->_cbuf.buffer);
		if (self->_fd >= 0) {
			close(self->_fd);
			self->_fd = -1;
		}
		free(self);
	}
}
