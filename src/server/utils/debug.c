/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** debug.c
*/

#include "debug.h"

void	debug(const int fd, const char *format, ...)
{
	char		buff[4096];
	va_list		args;
	int		wrote = 0;

	va_start(args, format);
	if (ACTIVATE_DEBUG) {
		wrote = vsprintf(buff, format, args);
		if (wrote > 0)
			write(fd, buff, wrote);
	}
	va_end(args);
}
