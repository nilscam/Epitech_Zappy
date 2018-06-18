/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** big_buff.c
*/

#include "big_buff.h"

void	big_buff_reset(big_buff_t *buff)
{
	buff->pos = 0;
}

bool	big_buff_can_add_data(big_buff_t *buff, size_t size_data)
{
	return (buff->pos + size_data < BIG_BUFF_SIZE);
}

void	big_buff_add_data(big_buff_t *buff, char *data, size_t size_data)
{
	memcpy(buff->buff + buff->pos, data, size_data);
	buff->pos += size_data;
}

char	*big_buff_strdup(big_buff_t *buff)
{
	return strndup(buff->buff, buff->pos);
}
