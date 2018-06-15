/*
** EPITECH PROJECT, 2018
** help
** File description:
** help
*/

#include "parsing.h"

int	help(void)
{
	printf("USAGE: ./zappy_server -p port -x width -y ");
	printf("height -n name1 name2 ... -c clientsNb -f freq\n");
	printf("port\t\tis the port number\n");
	printf("width\t\tis the width of the world\n");
	printf("height\t\tis the height of the world\n");
	printf("nameX\t\tis the name of the team X\n");
	printf("clientsNb\tis the number of authorized clients per team\n");
	printf("freq\t\tis the reciprocal of time unit ");
	printf("for execution of actions\n");
	return (0);
}