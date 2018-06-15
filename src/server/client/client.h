/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.h
*/

#ifndef client_HPP
#define client_HPP

#include "buffer.h"
#include "class.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	int		_fd;
	t_buffer	_cbuf;
	bool		accept_client_callback;
	bool		accept_spectate_callback;
}	client_t;

/* client.c */
client_t	*client_new(int fd, bool is_spectator);
void		client_delete(client_t *self);

#endif // !client_HPP
