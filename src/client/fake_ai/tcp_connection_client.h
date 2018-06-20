/*
** EPITECH PROJECT, 2018
** tcp_connection_client
** File description:
** tcp_connection_client
*/

#ifndef TCP_CONNECTION_CLIENT_H_
# define TCP_CONNECTION_CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

//			select define
# define READ_FDS	0
# define WRITE_FDS	1
# define ERR_FDS	2
# define TIMEOUT	1

//			circular buffer size
# define	SIZE_BUFF	512

typedef struct	s_buffer	t_buffer;
typedef struct	s_client	t_client;

struct			s_buffer
{
	char	*buffer;
	int		wr;
	int		rd;
	int		size;
};

struct			s_client
{
	int			(*init)(t_client *this, char *ip, int port, char *protocol);
	int			(*select)(t_client *this, int timeout);
	int			(*can_read)(t_client *this, int fd);
	int			(*can_write)(t_client *this, int fd);
	int			(*can_err)(t_client *this, int fd);
	void		(*write)(int fd, char *str);
	void		(*stop)(t_client *this);
	int			_fd_server;
	fd_set		_fds[3];
	t_buffer	_cbuf;
};

//				circular_buffer.c
int	buff_put(t_buffer *cbuf, char *str);
char	*buff_get(t_buffer *cbuf);
int	buff_init(t_buffer *cbuf, int size);

//				init_client.c
int		create_socket(char *protocol);
int		connect_socket(char *ip, int port, int fd);
int	init_client(t_client *this, char *ip, int port, char *protocol);

//				init.c
void		init_client_functions(t_client *this);
t_client	*init_struct_client(void);

//				select.c
void	fill_fds(t_client *this);
int		get_max_fd(t_client *this);
int		prepare_select(t_client *this, int timeout);

//				select_is_set.c
int		can_read(t_client *this, int fd);
int		can_write(t_client *this, int fd);
int		can_err(t_client *this, int fd);

//				write.c
void	put_client(int fd, char *str);

//				stop_client.c
void	stop_client(t_client *this);

#endif	/* TCP_CONNECTION_CLIENT_H_ */