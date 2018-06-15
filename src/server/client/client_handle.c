/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client_handle.c
*/

#include "client.h"
#include "debug.h"

void	client_handle(client_t *client)
{
	char	*cmd;

	do {
		cmd = list_extract(client->read_buff, "\n");
		if (!cmd)
			break;
		if (*cmd) {
			DEBUG("cmd from %d: '%s'", client->_fd, cmd);
		}
		free(cmd);
	} while (cmd);
}
