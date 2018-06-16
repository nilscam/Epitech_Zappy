/*
** EPITECH PROJECT, 2018
** write
** File description:
** write
*/

#include "server.h"

void	put_server(int fd, char *str)
{
	int	i = -1;

	while (str[++i]) {
		write(fd, &str[i], 1);
	}
}