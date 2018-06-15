/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_callback.h
*/

#ifndef player_callback_HPP
#define player_callback_HPP

#include "client.h"
#include <stdarg.h>
#include <stddef.h>

typedef void	(*pl_callback_fct_t)(va_list *);

typedef enum
{
	CB_NEW_PLAYER,
	CB_EXPLUSION,
	CB_BROADCAST,
	CB_START_INCANTATION,
	CB_END_INCANTATION,
	CB_EGG_LAYING,
	CB_RESOURCE_DROPPING,
	CB_RESOURCE_COLLECTING,
	CB_DEATH_PLAYER,
	CB_EGG_LAID_BY_PLAYER,
	CB_EGG_HATCHING,
	CB_PLAYER_CONNECTION_EGG,
	CB_END_OF_GAME,
	CB_MESSAGE_FROM_SERVER,
	CB_UNKNOWN_COMMAND,
	CB_COMMAND_PARAMETER
}	callback_type_t;

typedef struct
{
	callback_type_t		type;
	pl_callback_fct_t	fct;
	char			*description;
}	client_callback_t;

/* player_callback.c */
void	player_callback(callback_type_t type, ...);
void	spectate_callback(callback_type_t type, ...);

#endif // !player_callback_HPP
