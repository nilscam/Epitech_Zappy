/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list.h
*/

#ifndef list_HPP
#define list_HPP

#include "class.h"

typedef struct list_node_s
{
	struct list_node_s	*prev;
	struct list_node_s	*next;
	void			*data;
}	list_node_t;

typedef struct
{
	class_t		__base__;
	list_node_t	*tail;
	list_node_t	*head;
	size_t		size;
}	list_t;

/* list_extract.c */
char	*list_extract(list_t *list, const char *delims);

/* list_push.c */
bool	list_push_back(list_t *self, void *data);
bool	list_push_front(list_t *self, void *data);

/* list_utils.c */
void	list_clear(list_t *self, void (*fct)(void *));
size_t	list_size(list_t *self);

/* list_pop.c */
void	*list_pop_front(list_t *self);
void	*list_pop_back(list_t *self);

/* list_get.c */
void	*list_get_front(list_t *self);
void	*list_get_back(list_t *self);

/* list.c */
extern const class_t *LIST;

#endif // !list_HPP
