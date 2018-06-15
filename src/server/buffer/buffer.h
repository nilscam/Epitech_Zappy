/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** buffer.h
*/

#ifndef buffer_HPP
#define buffer_HPP

# define	SIZE_BUFF	512

typedef struct	s_buffer	t_buffer;

struct			s_buffer
{
	char	*buffer;
	int		wr;
	int		rd;
	int		size;
};

//				circular_buffer.c
int	buff_put(t_buffer *cbuf, char *str);
char	*buff_get(t_buffer *cbuf);
int	buff_init(t_buffer *cbuf, int size);

#endif // !buffer_HPP
