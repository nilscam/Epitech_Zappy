/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator.h
*/

#ifndef list_iterator_HPP
#define list_iterator_HPP

#include "list.h"

typedef void	(*list_it_fct_t)(void *, va_list *);
typedef bool	(*list_it_fct_bool_t)(void *, va_list *);
typedef list_it_fct_bool_t	list_it_fct_remove_t;
typedef list_it_fct_bool_t	list_it_fct_find_t;

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

/* list_iterator_it.c */
bool	list_it_all(list_t *list, list_it_fct_t fct, ...);
bool	list_it_remove(list_t *list, list_it_fct_remove_t fct_remove, ...);
void	*list_it_find(list_t *list, list_it_fct_find_t fct_find, ...);

/* list_iterator.c */
extern const class_t *LIST_IT;

#endif // !list_iterator_HPP
