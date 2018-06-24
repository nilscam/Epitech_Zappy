/*
** EPITECH PROJECT, 2018
** tcp_connection
** File description:
** tcp_connection
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "debug.h"
# include "list.h"
# include "map.h"
# include "client.h"
# include "buffer.h"
# include "team.h"
# include "zclock.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

# define	MAX_CLIENT	4096

//			select define
# define	READ_FDS	0
# define	WRITE_FDS	1
# define	ERR_FDS		2
# define	TIMEOUT		1

typedef struct	s_server		t_server;

struct			s_server
{
	int		(*init)(t_server *this, int port, char *protocol);
	int		(*select)(t_server *this, int timeout);
	int		(*can_read)(t_server *this, int fd);
	int		(*can_write)(t_server *this, int fd);
	int		(*can_err)(t_server *this, int fd);
	void		(*add_client)(t_server *this);
	void		(*write)(int fd, char *str);
	void		(*stop)(t_server *this);
	int		_fd_server;
	fd_set		_fds[3];
	map_t		*map;
	list_t		*anonymous_clients;
	list_t		*players_clients;
	list_t		*spectators_clients;
	list_t		*teams;
	double		f;
	team_t		*winner;
	zclock_t	zclock;
	long long	turn;
};

//				server.c
int	create_socket(char *protocol);
int	bind_socket(int fd, int port);
int	listen_socket(int fd, int max_client);
int	init_server(t_server *this, int port, char *protocol);

//				handle_tcp_clients.c
void	handle_tcp_clients(t_server *server);

//				handle_tcp_server.c
void	handle_tcp_server(t_server *server);

//				handle_eggs.c
void	handle_eggs_action(t_server *server);

//				handle_players.c
void	handle_players_action(t_server *server);
bool	can_simulate_game(t_server *server);

//				deinit.c
void	deinit_server(t_server *server);

//				init.c
void		init_server_functions(t_server *this);
t_server	*init_struct_server(map_t *map, double f);

//				clients_add.c
void	add_client(t_server *this);

//				clients_remove.c
void	remove_client_from_list(t_server *, client_t *, bool delete_it);
void	remove_player(t_server *this, void *player);
void	stop_server(t_server *this);

//				select.c
int		prepare_select(t_server *this, int timeout);

//				select_is_set.c
int		can_read(t_server *this, int fd);
int		can_write(t_server *this, int fd);
int		can_err(t_server *this, int fd);

//				write.c
void	put_server(int fd, char *str);

//				add_team.c
void	add_team(t_server *this, const char *name, size_t max_players);

#endif /* SERVER_H_ */