/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** big_buff.h
*/

#ifndef big_buff_HPP
#define big_buff_HPP

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define BIG_BUFF_SIZE	10000

typedef struct
{
	char	buff[BIG_BUFF_SIZE];
	int	pos;
}	big_buff_t;

/* big_buff.c */
void	big_buff_reset(big_buff_t *buff);
bool	big_buff_can_add_data(big_buff_t *buff, size_t size_data);
void	big_buff_add_data(big_buff_t *buff, char *data, size_t size_data);
char	*big_buff_strdup(big_buff_t *buff);

#endif // !big_buff_HPP
