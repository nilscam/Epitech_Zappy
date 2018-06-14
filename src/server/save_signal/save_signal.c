/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** save_signal.c
*/

#include "save_signal.h"

static signal_save_t	*global_signal(void *start, ...)
{
	static signal_save_t	save = { false, NULL, NULL };
	va_list		args;

	if (!save.saved) {
		va_start(args, start);
		save = va_arg(args, signal_save_t);
		va_end(args);
	}
	return (&save);
}

static void	signal_handler(int signum)
{
	signal_save_t	*save = global_signal(NULL);

	if (signum == SIGINT) {
		DEBUG("Stopping server..");
		save->saved = false;
		save->server->stop(save->server);
		DELETE(save->map);
		exit(0);
	}
}

void	setup_signals(t_server *server, map_t *map)
{
	global_signal(NULL, (signal_save_t){ true, server, map });
	signal(SIGINT, signal_handler);
}
