/*
** EPITECH PROJECT, 2018
** tcp_connection
** File description:
** tcp_connection
*/

#ifndef TCP_CONNECTION_H_
# define TCP_CONNECTION_H_

# include "debug.h"
# include "list.h"
# include "map.h"
# include "client.h"
# include "buffer.h"
# include "team.h"
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
	int			(*init)(t_server *this, int port, char *protocol);
	int			(*select)(t_server *this, int timeout);
	int			(*can_read)(t_server *this, int fd);
	int			(*can_write)(t_server *this, int fd);
	int			(*can_err)(t_server *this, int fd);
	void		(*add_client)(t_server *this);
	void		(*write)(int fd, char *str);
	void		(*stop)(t_server *this);
	int			_fd_server;
	fd_set		_fds[3];
	map_t		*map;
	list_t		*anonymous;
	list_t		*players;
	list_t		*spectators;
	list_t		*teams;
};

//				server.c
int	create_socket(char *protocol);
int	bind_socket(int fd, int port);
int	listen_socket(int fd, int max_client);
int	init_server(t_server *this, int port, char *protocol);

//				deinit.c
void	deinit_server(t_server *server);

//				init.c
void		init_server_functions(t_server *this);
t_server	*init_struct_server(list_t *players, map_t *map);

//				clients_add.c
void	add_client(t_server *this);

//				clients_remove.c
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

#endif /* TCP_CONNECTION_H_ */