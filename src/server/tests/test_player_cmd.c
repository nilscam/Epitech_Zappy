/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_player_cmd.c
*/

#include "player_cmd.h"
#include <stdio.h>

int	test_player_cmd(void)
{
	printf("----\n");
	player_cmd("Forward");
	printf("----\n");
	spectate_cmd("bct");
	printf("----\n");
	spectate_cmd("bct X");
	printf("----\n");
	spectate_cmd("bct X Y");
	printf("----\n");
	return 0;
}
