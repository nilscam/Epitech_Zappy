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

# define ACTIVATE_DEBUG	1
# define _DEBUG_FD	1
# define _DEBUG_FORMAT	"Debug: [%s:%d - %s]: "
# define _DEBUG_ARGS	__FILE__, __LINE__, __func__
# define DEBUG(f, ...)	debug(_DEBUG_FD, _DEBUG_FORMAT, _DEBUG_ARGS); \
			debug(_DEBUG_FD, f, ##__VA_ARGS__); \
			debug(_DEBUG_FD, "\n")

/*	debug.c		*/
void	debug(const int fd, const char *format, ...);

#endif // !debug_HPP
