/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** save_signal.h
*/

#ifndef save_signal_HPP
#define save_signal_HPP

#include "server.h"
#include "map.h"
#include "player.h"
#include <signal.h>

typedef struct
{
	bool		saved;
	t_server	*server;
}	signal_save_t;

/* save_signal.c */
void	setup_signals(t_server *server);

#endif // !save_signal_HPP
