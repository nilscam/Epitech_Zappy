/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_big_buffer.c
*/

#include "big_buff.h"

int	test_big_buff(void)
{
	big_buff_t buff;
	big_buff_init(&buff);
	big_buff_add_data(&buff, "12345", 5);
	big_buff_add_data(&buff, "67890", 5);
	big_buff_add_format(&buff, "%s %d", "aaaaaa", 42);
	big_buff_add_format(&buff, "%s %d", "bbbbbb", 42);
	big_buff_add_format(&buff, "%s %d", "cccccc", 42);
	big_buff_add_format(&buff, "%s %d", "dddddddddddddddddddd", 42);
	big_buff_add_format(&buff, "%s %d", "eeeeee", 42);
	char * res = big_buff_cpy_data(&buff);
	printf("--> '%s'\n", res);
	SAFE_FREE(res);
	big_buff_deinit(&buff);
	return 0;
}
