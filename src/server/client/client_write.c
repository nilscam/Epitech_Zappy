/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client_write.c
*/

#include "client.h"
#include "debug.h"

bool	client_write(client_t *client)
{
	char	*data;
	int	wrote;
	int	to_write;

	data = list_pop_front(client->write_buff);
	to_write = data ? strlen(data) : 0;
	if (data && *data && to_write > 0) {
		wrote = write(client->_fd, data, to_write);
		DEBUG("write %lu bytes to fd %d:", wrote, client->_fd,
			wrote);
		if (wrote < 0) {
			return false;
		} else if (wrote < to_write) {
			list_push_front(client->write_buff,
				strdup(data + wrote));
		}
	}
	if (data)
		free(data);
	return true;
}
