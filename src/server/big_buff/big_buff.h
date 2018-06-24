/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** big_buff.h
*/

#ifndef big_buff_HPP
#define big_buff_HPP

#include "list.h"
#include "list_iterator.h"
#include "str_concat.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define BIG_BUFF_SIZE	10000

typedef struct
{
	list_t	list;
	char	buff[BIG_BUFF_SIZE];
	int	pos;
}	big_buff_t;

/* big_buff.c */
void	big_buff_init(big_buff_t *buff);
bool	big_buff_add_data(big_buff_t *buff, char *data, size_t size_data);
bool	bb_add(big_buff_t *buff, char *format, ...);
char	*big_buff_cpy_data(big_buff_t *buff);
void	big_buff_deinit(big_buff_t *buff);

#endif // !big_buff_HPP
