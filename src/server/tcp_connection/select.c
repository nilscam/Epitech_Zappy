/*
** EPITECH PROJECT, 2018
** select
** File description:
** select
*/

#include "tcp_connection.h"
#include "player.h"
#include "map_it.h"

static void	set_player_fd_set(player_t *player, va_list *args)
{
	fd_set	*fds = va_arg(*args, fd_set *);

	FD_SET(player->client->_fd, &fds[READ_FDS]);
	FD_SET(player->client->_fd, &fds[WRITE_FDS]);
	FD_SET(player->client->_fd, &fds[ERR_FDS]);
}

void	fill_fds(t_server *this, map_t *map)
{
	FD_ZERO(&this->_fds[READ_FDS]);
	FD_ZERO(&this->_fds[WRITE_FDS]);
	FD_ZERO(&this->_fds[ERR_FDS]);
	FD_SET(this->_fd_server, &this->_fds[READ_FDS]);
	FD_SET(this->_fd_server, &this->_fds[WRITE_FDS]);
	FD_SET(this->_fd_server, &this->_fds[ERR_FDS]);
	map_it_players(map, (map_it_pl_t)set_player_fd_set, this->_fds);
}

int		get_max_fd(t_server *this)
{
	list_iterator_t it;
	player_t	*player;
	int		max_fd = this->_fd_server;

	if (!INIT(LIST_IT, it, this->players))
		return max_fd;
	while (list_it_can_iterate(&it)) {
		player = list_it_get(&it);
		if (max_fd < player->client->_fd)
			max_fd = player->client->_fd;
		list_it_iterate(&it);
	}
	DEINIT(it);
	return (max_fd + 1);
}

int		prepare_select(t_server *this, map_t *map, int timeout)
{
	int	max_fd = get_max_fd(this);

	fill_fds(this, map);
	struct timeval tv = {timeout, 0};
	return (select(max_fd, &this->_fds[READ_FDS], &this->_fds[WRITE_FDS],
			&this->_fds[ERR_FDS], &tv));
}