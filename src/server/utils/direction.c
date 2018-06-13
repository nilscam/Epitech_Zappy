/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** direction.c
*/

#include "direction.h"
#include <stdio.h>
#include <string.h>

char	*direction_repr(direction_t dir)
{
	char	buff[255];
	char	*tmp = buff;

	if (dir & DIR_LEFT)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Left");
	if (dir & DIR_RIGHT)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Right");
	if (dir & DIR_UP)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Up");
	if (dir & DIR_DOWN)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Down");
	if (tmp <= buff)
		tmp += sprintf(tmp, "%s", "None");
	return tmp <= buff ? NULL : strdup(buff);
}
