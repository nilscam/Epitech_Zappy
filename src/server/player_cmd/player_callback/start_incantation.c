/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** start_incantation.c
*/

#include "player_callback.h"
#include "map.h"
#include "map_it.h"
#include "player.h"

static void	add_player_to_buff(player_t *player, va_list *args)
{
	int	level = va_arg(*args, int);
	int	skip_id = va_arg(*args, int);
	char	**tmp = va_arg(*args, char **);

	if (player->level == level && player->id != skip_id) {
		*tmp += sprintf(*tmp, " %lld", player->id);
	}
}

void	spectate_callback_start_incantation(
	__attribute__((unused))const client_callback_t *cb,
	client_t *client, va_list *args)
{
	int		x = va_arg(*args, int);
	int		y = va_arg(*args, int);
	int		level = va_arg(*args, int);
	int		id = va_arg(*args, int);
	map_t		*map = va_arg(*args, map_t *);
	char		buff[20000];
	char		*tmp = buff;

	printf("start_incantation\n");
	tmp += sprintf(tmp, "pic %d %d %d %d", x, y, level, id);
	map_it_players_at(map, (point_t){ x, y },
		(map_it_pl_t)add_player_to_buff, level, id, &tmp);
	tmp += sprintf(tmp, "\n");
	tmp = strdup(buff);
	if (tmp) {
		list_push_back(client->write_buff, tmp);
	}
}
