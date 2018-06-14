/*
** EPITECH PROJECT, 2018
** write
** File description:
** write
*/

#include "tcp_connection.h"

void	put_server(int fd, char *str)
{
	int	i = -1;

	while (str[++i]) {
		write(fd, &str[i], 1);
	}
}