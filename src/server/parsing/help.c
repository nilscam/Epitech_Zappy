/*
** EPITECH PROJECT, 2018
** help
** File description:
** help
*/

#include "parsing.h"

int	help(char *self)
{
	printf("USAGE: %s -p port -x width -y ", self);
	printf("height -n name1 name2 ... -c clientsNb -f freq\n");
	printf("\tport\t\tis the port number\n");
	printf("\twidth\t\tis the width of the world\n");
	printf("\theight\t\tis the height of the world\n");
	printf("\tnameX\t\tis the name of the team X\n");
	printf("\tclientsNb\tis the number of authorized clients");
	printf(" per team\n\tfreq\t\tis the reciprocal of time unit ");
	printf("for execution of actions\n");
	return (0);
}
