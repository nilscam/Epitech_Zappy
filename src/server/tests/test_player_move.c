/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_player_move.c
*/

#include "player.h"
#include "map.h"
#include <string.h>
#include <stdio.h>

static void	test_player_moving(player_t *player, direction_t dir, int inc)
{
	char	*repr = direction_repr(dir);
	player_move_toward(player, DIR_RIGHT, 1);
	printf("move %d %s: ", inc, repr);
	player_print(player);
	SAFE_FREE(&repr);
}

static void	test_player_turn(player_t *player, bool turn_left)
{
	char	*before = direction_repr(player->dir);
	char	*after;
	if (turn_left)
		player_turn_left(player);
	else
		player_turn_right(player);
	after = direction_repr(player->dir);
	printf("turn %s: %s --> %s\n", turn_left ? "Left" : "Right",
		before, after);
	SAFE_FREE(&before);
	SAFE_FREE(&after);
}

static void	test_player_moves(player_t *player)
{
	test_player_moving(player, DIR_RIGHT, 1);
	test_player_moving(player, DIR_RIGHT, 2);
	test_player_moving(player, DIR_RIGHT, 3);
	test_player_moving(player, DIR_DOWN, 1);
	test_player_moving(player, DIR_UP, 1);
	test_player_moving(player, DIR_LEFT, 1);
	test_player_moving(player, DIR_LEFT | DIR_UP, 1);
}

static void	test_player_turns(player_t *player)
{
	test_player_turn(player, true);
	test_player_turn(player, true);
	test_player_turn(player, true);
	test_player_turn(player, true);
	test_player_turn(player, true);
	test_player_turn(player, false);
	test_player_turn(player, false);
	test_player_turn(player, false);
	test_player_turn(player, false);
	test_player_turn(player, false);
}

void	test_player_move(player_t *player)
{
	test_player_moves(player);
	test_player_turns(player);
	player_print(player);
	player_move(player);
	player_print(player);
	player_turn_left(player);
	player_move(player);
	player_print(player);
}
