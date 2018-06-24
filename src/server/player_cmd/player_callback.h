/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_callback.h
*/

#ifndef player_callback_HPP
#define player_callback_HPP

#include "client.h"
#include "list.h"
#include <stdarg.h>
#include <stddef.h>

#define SIZE_ARRAY(x)	(sizeof(x) / sizeof(*x))
#define CB_PLAYER_INV_1 "[food %d, linemate %d, deraumere %d, "
#define CB_PLAYER_INV_2 "sibur %d, mendiane %d, phiras %d, thystame %d]\n"

typedef struct client_callback_s client_callback_t;
typedef void (*pl_callback_fct_t)(
	const client_callback_t *, client_t *, va_list *);

typedef enum
{
	CB_WELCOME,
	CB_WELCOME_PLAYER,
	CB_WELCOME_SPECTATOR,
	CB_INVALID_TEAM_NAME,
	CB_FULL_TEAM,
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
	CB_COMMAND_PARAMETER,
	CB_OK,
	CB_KO,
	CB_NB_UNUSED_SLOTS,
	CB_ELEVATION_UNDERWAY,
	CB_CURRENT_LVL,
	CB_MAP_SIZE,
	CB_CONTENT_TILE,
	CB_CONTENT_MAP,
	CB_NAME_TEAMS,
	CB_PLAYER_POSITION,
	CB_PLAYER_LEVEL,
	CB_PLAYER_INVENTORY,
	CB_TIME_UNIT_REQUEST,
	CB_TIME_UNIT_MODIF,
	CB_EJECT,
	CB_EGG_POSITION,
	CB_TIME
}	callback_type_t;

struct client_callback_s
{
	callback_type_t		type;
	pl_callback_fct_t	fct;
	char			*format;
	char			*prototype;
	char			*description;
};

/* player_callback.c */
void	client_callback(callback_type_t type, client_t *client, ...);
void	clients_callback(callback_type_t type, list_t *clients, ...);

/* player_callback/send_format.c */
void	player_callback_send_format(
	const client_callback_t *cb, client_t *client, va_list *args);

/* player_callback/start_incantation.c */
void	spectate_callback_start_incantation(
	const client_callback_t *cb, client_t *client, va_list *args);

#endif // !player_callback_HPP
