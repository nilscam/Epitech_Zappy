/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.h
*/

#ifndef client_HPP
#define client_HPP

#include "list.h"
#include "class.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_NEWLINE	10

typedef enum
{
	CLIENT_ANONYMOUS,
	CLIENT_PLAYER,
	CLIENT_SPECTATOR
}	client_type_t;

typedef struct
{
	int		_fd;
	list_t		*read_buff;
	size_t		nb_newline;
	bool		block_until_newline;
	list_t		*write_buff;
	client_type_t	type;
	bool		kill_me;
}	client_t;

/* client.c */
client_t	*client_new(int fd, client_type_t type);
void		client_delete(client_t *self);

/* client_read.c */
bool	client_read(client_t *client);
char	*client_extract_cmd(client_t *client);

/* client_write.c */
bool	client_write(client_t *client);

#endif // !client_HPP
