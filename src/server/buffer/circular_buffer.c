/*
** EPITECH PROJECT, 2018
** circular_buffer
** File description:
** circular_buffer
*/

#include "server.h"

int	buff_put(t_buffer *cbuf, char *str)
{
	int	ret = -1, i = -1;

	if (cbuf && str) {
		while (str[++i]) {
			cbuf->buffer[cbuf->wr] = str[i];
			cbuf->wr = (cbuf->wr + 1) % cbuf->size;
			cbuf->rd = (cbuf->wr == cbuf->rd ?
			(cbuf->rd + 1) % cbuf->size : cbuf->rd);
		}
		ret = 0;
	}
	return (ret);
}

char	*buff_get(t_buffer *cbuf)
{
	int		size = cbuf->wr - cbuf->rd, i = -1;
	char	*str;

	if (size < 0)
		size = cbuf->size - (cbuf->rd - cbuf->wr);
	str = malloc(size + 4);
	if (!str)
		return (NULL);
	memset(str, 0, size + 3);
	while (++i < size) {
		str[i] = cbuf->buffer[cbuf->rd];
		cbuf->buffer[cbuf->rd] = 0;
		cbuf->rd = (cbuf->rd + 1) % cbuf->size;
	}
	return (str);
}

int	buff_init(t_buffer *cbuf, int size)
{
	if (cbuf) {
		cbuf->buffer = malloc(size + 1);
		memset(cbuf->buffer, 0, size);
		cbuf->size = size;
		cbuf->wr = 0;
		cbuf->rd = 0;
	}
	return (0);
}