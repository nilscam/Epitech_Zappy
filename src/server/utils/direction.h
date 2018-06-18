/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** direction.h
*/

#ifndef direction_HPP
#define direction_HPP

#define SIZE_ARRAY(x)	(sizeof(x) / sizeof(*x))

typedef enum
{
	DIR_NONE,
	DIR_LEFT = 0x1,
	DIR_RIGHT = 0x2,
	DIR_UP = 0x4,
	DIR_DOWN = 0x8
}	direction_t;

struct circle_direction_s
{
	double		min;
	double		max;
	direction_t	dir;
};

/* direction.c */
char		*direction_repr(direction_t dir);
direction_t	direction_turn_left(direction_t dir);
direction_t	direction_turn_right(direction_t dir);
direction_t	direction_from_angle(double degrees);

/* direction_to_int.c */
int		direction_to_int(direction_t dir);
int		direction_to_int_spec(direction_t dir);

#endif // !direction_HPP
