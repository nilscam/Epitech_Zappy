/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client_read.c
*/

#include "client.h"
#include "debug.h"
#include <errno.h>

static void	read_data_loop(client_t *c, char **buff, int *size_read)
{
	char	*buff_start = *buff;
	int	to_read = 0;

	for (int i = 0; i < *size_read; ++i) {
		if ((*buff)[i] == '\n' && c->nb_newline < MAX_NEWLINE) {
			if (!c->block_until_newline) {
				++c->nb_newline;
				++to_read;
			} else {
				buff_start = (*buff) + i + 0;
				to_read = 0;
			}
			c->block_until_newline = false;
		} else if ((*buff)[i] != '\n' && !c->block_until_newline
			&& c->nb_newline < MAX_NEWLINE) {
			++to_read;
		}
	}
	*size_read = to_read;
	*buff = buff_start;
}

static char	*read_data(client_t *client, char *buff, int size_read)
{
	bool	last_char_is_newline = buff[size_read - 1] == '\n';

	read_data_loop(client, &buff, &size_read);
	client->block_until_newline = false;
	if (client->nb_newline >= MAX_NEWLINE) {
		client->block_until_newline = !last_char_is_newline;
	}
	return size_read > 0 ? strndup(buff, size_read) : NULL;
}

char	*client_extract_cmd(client_t *client)
{
	char	*str = list_extract(client->read_buff, "\n");

	if (client->nb_newline > 0) {
		--client->nb_newline;
	}
	return str;
}

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
	DEBUG("read %lu bytes from %d", size_read, client->_fd, size_read);
	data = read_data(client, buff, size_read);
	if (data) {
		list_push_back(client->read_buff, data);
	}
	return true;
}
