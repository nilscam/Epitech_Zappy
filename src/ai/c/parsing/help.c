/*
** EPITECH PROJECT, 2018
** help
** File description:
** help
*/

#include "parsing.h"

int	help(void)
{
	printf("USAGE: ./zappy_ai -p port -n name -h machine\n");
	printf("\tport\t\tis the port number\n");
	printf("\tname\t\tis the name of the team\n");
	printf("\tmachine\tis the name of the machine; localhost by default\n");
	return (0);
}