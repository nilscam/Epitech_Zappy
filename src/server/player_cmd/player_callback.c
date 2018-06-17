/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_callback.c
*/

#include "player_callback.h"
#include "list.h"
#include "list_iterator.h"

static const client_callback_t	ANONYMOUS_CALLBACKS[] = {
	{
		CB_WELCOME, player_callback_send_format,
		"WELCOME\n",
		"",
		"welcome a new anonymous user"
	},
	{
		CB_WELCOME_PLAYER, player_callback_send_format,
		"%d\n%d %d\n",
		"<nb_available_team_clients> <X> <Y>",
		"welcome a new player"
	},
	{
		CB_WELCOME_SPECTATOR, player_callback_send_format,
		"ok\n",
		"",
		"welcome a new spectator"
	},
	{
		CB_INVALID_TEAM_NAME, player_callback_send_format,
		"ko\n",
		"",
		"invalid team name"
	}
};

static const client_callback_t	CLIENT_CALLBACKS[] = {
	{
		CB_DEATH_PLAYER, player_callback_send_format,
		"dead\n",
		"",
		"death of a player"
	},
	{
		CB_OK, player_callback_send_format,
		"ok\n",
		"",
		"ok"
	},
	{
		CB_KO, player_callback_send_format,
		"ko\n",
		"",
		"ko"
	},
	{
		CB_NB_UNUSED_SLOTS, player_callback_send_format,
		"%d\n",
		"<nb_unused_slots>",
		"number of team unused slots"
	},
	{
		CB_ELEVATION_UNDERWAY, player_callback_send_format,
		"Elevation underway\n",
		"",
		"Elevation underway"
	},
	{
		CB_CURRENT_LVL, player_callback_send_format,
		"Current level: %d\n",
		"<lvl>",
		"Current level: k"
	},
	{
		CB_BROADCAST, player_callback_send_format,
		"message %d, %s\n",
		"<direction> <message>",
		"broadcast"
	},
	{
		CB_PLAYER_INVENTORY, player_callback_send_format,
		CB_PLAYER_INV_1 CB_PLAYER_INV_2,
		"<food> <6 stones>",
		"Inventory"
	}
};

static const client_callback_t	SPECTATOR_CALLBACKS[] = {
	{
		CB_MAP_SIZE, player_callback_send_format,
		"msz %d %d\n",
		"<X> <Y>",
		"map size"
	},
	{
		CB_CONTENT_TILE, player_callback_send_format,
		"bct %d %d %d %d %d %d %d %d %d\n",
		"<X> <Y> <q0> <q1> <q2> <q3> <q4> <q5> <q6>",
		"content of a tile"
	},
	{
		CB_NAME_TEAMS, player_callback_send_format,
		"tna %s\n",
		"<team>",
		"name of all the teams"
	},
	{
		CB_NEW_PLAYER, player_callback_send_format,
		"pnw %d %d %d %d %d %s\n",
		"<player_nb> <X> <Y> <1(N),2(E),3(S),4(W)> <lvl> <team>",
		"connection of a new player"
	},
	{
		CB_PLAYER_POSITION, player_callback_send_format,
		"ppo %d %d %d %d\n",
		"<n> <X> <Y> <O>\n",
		"player's position"
	},
	{
		CB_PLAYER_LEVEL, player_callback_send_format,
		"plv %d %d\n",
		"plv n L\n",
		"player's level"
	},
	{
		CB_PLAYER_INVENTORY, player_callback_send_format,
		"pin %d %d %d %d %d %d %d %d %d %d\n",
		"<n> <X> <Y> <q0> <q1> <q2> <q3> <q4> <q5> <q6>\n",
		"player's inventory"
	},
	{
		CB_EXPLUSION, player_callback_send_format,
		"pex %d\n",
		"<player_nb>",
		"explusion"
	},
	{
		CB_BROADCAST, player_callback_send_format,
		"pbc %d %s\n",
		"<player_nb> <message>",
		"broadcast"
	},
	{
		CB_START_INCANTATION, spectate_callback_start_incantation,
		"pic X Y L n n ...\n",
		"//todo special",
		"start of an incantation (by the first player)"
	},
	{
		CB_END_INCANTATION, player_callback_send_format,
		"pie %d %d %s\n",
		"<X> <Y> <invantation_result>",
		"end of an incantation"
	},
	{
		CB_EGG_LAYING, player_callback_send_format,
		"pfk %d\n",
		"<player>",
		"egg laying by the player"
	},
	{
		CB_RESOURCE_DROPPING, player_callback_send_format,
		"pdr %d %d\n",
		"<player_nb> <ressource_nb>",
		"resource dropping"
	},
	{
		CB_RESOURCE_COLLECTING, player_callback_send_format,
		"pgt %d %d\n",
		"<player_nb> <ressource_nb>",
		"resource collecting"
	},
	{
		CB_DEATH_PLAYER, player_callback_send_format,
		"pdi %d\n",
		"<player_nb>",
		"death of a player"
	},
	{
		CB_EGG_LAID_BY_PLAYER, player_callback_send_format,
		"enw %d %d %d %d\n",
		"<egg_nb> <player_nb> <X> <Y>",
		"an egg was laid by a player"
	},
	{
		CB_EGG_HATCHING, player_callback_send_format,
		"eht %d\n",
		"<egg_nb>",
		"egg hatching"
	},
	{
		CB_PLAYER_CONNECTION_EGG, player_callback_send_format,
		"ebo %d\n",
		"<egg_nb>",
		"player connection for an egg"
	},
	{
		CB_TIME_UNIT_REQUEST, player_callback_send_format,
		"sgt %d\n",
		"<time_unit>",
		"time unit request"
	},
	{
		CB_TIME_UNIT_MODIF, player_callback_send_format,
		"sst %d\n",
		"<time_unit>",
		"time unit modification"
	},
	{
		CB_END_OF_GAME, player_callback_send_format,
		"seg %s\n",
		"<team>",
		"end of game"
	},
	{
		CB_MESSAGE_FROM_SERVER, player_callback_send_format,
		"smg %s\n",
		"<msg>",
		"message from the server"
	},
	{
		CB_UNKNOWN_COMMAND, player_callback_send_format,
		"suc\n",
		"",
		"unknown command"
	},
	{
		CB_COMMAND_PARAMETER, player_callback_send_format,
		"sbp\n",
		"",
		"command parameter"
	}
};

static const size_t	MAX_ANONYMOUS_CB = SIZE_ARRAY(ANONYMOUS_CALLBACKS);
static const size_t	MAX_CLIENT_CB = SIZE_ARRAY(CLIENT_CALLBACKS);
static const size_t	MAX_SPECTATOR_CB = SIZE_ARRAY(SPECTATOR_CALLBACKS);

static const client_callback_t	*get_callback(callback_type_t type,
	const client_callback_t *cbs, int max_el)
{
	for (int i = 0; i < max_el; ++i) {
		if (type == cbs[i].type)
			return cbs + i;
	}
	return NULL;
}

static const client_callback_t	*get_client_callback(
	callback_type_t type, client_t *client)
{
	if (client->type == CLIENT_ANONYMOUS)
		return get_callback(type,
			ANONYMOUS_CALLBACKS, MAX_ANONYMOUS_CB);
	if (client->type == CLIENT_PLAYER)
		return get_callback(type,
			CLIENT_CALLBACKS, MAX_CLIENT_CB);
	if (client->type == CLIENT_SPECTATOR)
		return get_callback(type,
			SPECTATOR_CALLBACKS, MAX_SPECTATOR_CB);
	return NULL;
}

void	client_callback(callback_type_t type, client_t *client, ...)
{
	va_list	args;
	const client_callback_t	*c = get_client_callback(type, client);

	va_start(args, client);
	if (c) {
		c->fct(c, client, &args);
	}
	va_end(args);
}

void	clients_callback(callback_type_t type, list_t *clients, ...)
{
	const client_callback_t	*c;
	list_iterator_t it;
	client_t *client;
	va_list	args;
	va_list	cp_args;

	if (!INIT(LIST_IT, it, clients))
		return;
	va_start(args, clients);
	while (list_it_can_iterate(&it)) {
		client = list_it_get(&it);
		c = get_client_callback(type, client);
		if (c) {
			va_copy(cp_args, args);
			c->fct(c, client, &cp_args);
			va_end(cp_args);
		}
		list_it_iterate(&it);
	}
	va_end(args);
}
