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

typedef enum
{
	CLIENT_ANONYMOUS,
	CLIENT_PLAYER,
	CLIENT_SPECTATOR
}	client_type_t;

typedef struct
{
	int		_fd;
	t_buffer	_cbuf;
	client_type_t	type;
}	client_t;

/* client.c */
client_t	*client_new(int fd, client_type_t type);
void		client_delete(client_t *self);

#endif // !client_HPP
