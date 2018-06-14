/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** direction.h
*/

#ifndef direction_HPP
#define direction_HPP

typedef enum
{
	DIR_NONE,
	DIR_LEFT = 0x1,
	DIR_RIGHT = 0x2,
	DIR_UP = 0x4,
	DIR_DOWN = 0x8
}	direction_t;

/* direction.c */
char	*direction_repr(direction_t dir);
direction_t	direction_turn_left(direction_t dir);
direction_t	direction_turn_right(direction_t dir);

#endif // !direction_HPP
