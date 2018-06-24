/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** debug.h
*/

#ifndef debug_HPP
#define debug_HPP

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

# define ACTIVATE_DEBUG	0
# define _DEBUG_FD	1
# define _DEBUG_FORMAT	"Debug: [%s:%d - %s]: "
# define _DEBUG_ARGS	__FILE__, __LINE__, __func__
# define DEBUG(f, ...)	do { debug(1, _DEBUG_FORMAT, _DEBUG_ARGS); \
			debug(1, f, ##__VA_ARGS__); \
			debug(1, "\n"); \
			} while (0)
# define DEBUGW(f, s)	do { debug(1, _DEBUG_FORMAT, _DEBUG_ARGS); \
			write(1, f, s); \
			debug(1, "\n"); \
			} while (0)

/*	debug.c		*/
void	debug(const int fd, const char *format, ...);

#endif // !debug_HPP
