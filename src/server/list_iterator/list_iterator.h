/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator.h
*/

#ifndef list_iterator_HPP
#define list_iterator_HPP

#include "list.h"

typedef struct
{
	class_t		__base__;
	list_t		*list;
	list_node_t	*node;
}	list_iterator_t;

/* list_iterator_move.c */
bool	list_it_can_iterate(list_iterator_t *self);
void	list_it_iterate(list_iterator_t *self);

/* list_iterator_ops.c */
void	list_it_erase(list_iterator_t *self, void (*fct)(void *));
void	*list_it_get(list_iterator_t *self);
void	list_it_set(list_iterator_t *self, void *data);

/* list_iterator.c */
extern const class_t *LIST_IT;

#endif // !list_iterator_HPP
