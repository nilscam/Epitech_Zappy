/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** send_format.c
*/

#include "player_callback.h"
#include <stdio.h>

void	player_callback_send_format(
	const client_callback_t *cb, client_t *client, va_list *args)
{
	char	buff[20000];
	char	*str;

	printf("send_format '%s'\n", cb->description);
	vsprintf(buff, cb->format, *args);
	str = strdup(buff);
	if (str) {
		list_push_back(client->write_buff, str);
	}
}