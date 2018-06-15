/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client_read.c
*/

#include "client.h"
#include "debug.h"
#include <errno.h>

bool	client_read(client_t *client)
{
	char	buff[4096];
	char	*data;
	int	size_read;

	size_read = read(client->_fd, buff, 4096);
	if (size_read <= 0) {
		DEBUG("client %d left", client->_fd);
		return false;
	}
	data = strndup(buff, size_read);
	if (!data) {
		DEBUG("strndup: %s", strerror(errno));
	} else {
		list_push_back(client->read_buff, data);
	}
	DEBUG("read %lu bytes from %d: '%s'", size_read, client->_fd, data);
	return true;
}
