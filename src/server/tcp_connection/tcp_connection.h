/*
** EPITECH PROJECT, 2018
** tcp_connection
** File description:
** tcp_connection
*/

#ifndef TCP_CONNECTION_H_
# define TCP_CONNECTION_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

# define MAX_CLIENT		4096

//			select define
# define READ_FDS	0
# define WRITE_FDS	1
# define ERR_FDS	2

//			circular buffer size
# define SIZE_BUFF		512

typedef struct	s_buffer		t_buffer;
typedef struct	s_client		t_client;
typedef struct	s_server		t_server;

struct			s_buffer
{
	char	*buffer;
	int		wr;
	int		rd;
	int		size;
};

struct			s_client
{
	int			_fd;
	t_buffer	_cbuf;
	t_client	*next;
};

struct			s_server
{
	int			(*init)(t_server *this, int port, char *protocol);
	int			(*select)(t_server *this, int timeout);
	int			(*can_read)(t_server *this, int fd);
	int			(*can_write)(t_server *this, int fd);
	int			(*can_err)(t_server *this, int fd);
	void		(*add_client)(t_server *this);
	void		(*write)(int fd, char *str);
	t_client	*(*close_client)(t_server *this, int fd);
	void		(*stop)(t_server *this);
	int			_fd_server;
	fd_set		_fds[3];
	t_client	*_clients;
};

//				circular_buffer.c
int	buff_put(t_buffer *cbuf, char *str);
char	*buff_get(t_buffer *cbuf);
int	buff_init(t_buffer *cbuf, int size);

//				server.c
int	create_socket(char *protocol);
int	bind_socket(int fd, int port);
int	listen_socket(int fd, int max_client);
int	init_server(t_server *this, int port, char *protocol);

//				init.c
void		init_server_functions(t_server *this);
t_server	*init_struct_server(void);

//				clients_add.c
void	new_client(t_server *this, int fd);
void	add_client(t_server *this);

//				clients_remove.c
t_client	*remove_exist_client(t_server *this,
								t_client *tmp_a, t_client *tmp_b);
t_client	*remove_client(t_server *this, int fd);
t_client	*close_client(t_server *this, int fd);
void	stop_server(t_server *this);

//				select.c
void	fill_fds(t_server *this);
int		get_max_fd(t_server *this);
int		prepare_select(t_server *this, int timeout);

//				select_is_set.c
int		can_read(t_server *this, int fd);
int		can_write(t_server *this, int fd);
int		can_err(t_server *this, int fd);

//				write.c
void	put_server(int fd, char *str);

#endif /* TCP_CONNECTION_H_ */