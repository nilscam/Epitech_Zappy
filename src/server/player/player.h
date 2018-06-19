/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player.h
*/

#ifndef player_HPP
#define player_HPP

#include "class.h"
#include "map.h"
#include "server.h"
#include "client.h"
#include "team.h"

#define FOOD_TO_TIME_UNITS	126

typedef void	(*pl_callback_t)(void *);

typedef struct
{
	class_t		__base__;
	map_t		*map;
	map_content_t	*pos;
	inventory_t	inventory;
	team_t		*team;
	char		*name;
	direction_t	dir;
	int		level;
	int		remaining_time_units;
	int		is_busy_time_units;
	pl_callback_t	is_busy_callback;
	void		*is_busy_callback_args;
	client_t	*client;
	long long	id;
	bool		is_elevating;
	bool		is_waiting_to_die;
}	player_t;

typedef struct elevation_tab_s
{
	int		level;
	int		nb_players;
	int		stones[NUMBER_OF_INV_TYPE];
}	elevation_tab_t;

/* player_elevation.c */
bool	elevation_can_elevate(int level, int nb_of_players, int *stones);
void	player_elevate(player_t *self);
elevation_tab_t	*get_elevation_at_level(int level);

/* player_food.c */
bool	player_is_dead_of_hunger(player_t *self);
void	player_consume_food(player_t *self);
void	player_consume_time(player_t *self);

/* player_move.c */
void	player_move(player_t *self);
void	player_move_to(player_t *self, point_t pos);
void	player_move_toward(player_t *self, direction_t dir, int inc);

/* player_time.c */
void	player_wait_for(player_t *self, int time_units);
void	player_set_is_busy_callback(player_t *self,
		pl_callback_t callback, void *args);
void	player_wait(player_t *self);
bool	player_is_busy(player_t *self);

/* player_turn.c */
void	player_turn_left(player_t *self);
void	player_turn_right(player_t *self);

/* player_utils.c */
void	player_print(player_t *self);

/* player.c */
extern const class_t *PLAYER;

#endif // !player_HPP
