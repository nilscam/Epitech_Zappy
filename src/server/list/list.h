/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list.h
*/

#ifndef list_HPP
#define list_HPP

#include "class.h"

typedef void	(*list_fct_t)(void *);

typedef enum
{
	NODE_UNUSED,
	NODE_USED,
	NODE_EXTRA
}	list_node_type_t;

typedef struct list_node_s
{
	struct list_node_s	*prev;
	struct list_node_s	*next;
	void			*data;
	list_node_type_t	type;
	int			buffers_idx;
}	list_node_t;

typedef struct
{
	class_t		__base__;
	list_node_t	*tail;
	list_node_t	*head;
	size_t		size;
	list_node_t	*buffers;
	int		max_buffers;
	int		last_unused_buffers;
}	list_t;

/* list_node.c */
void	list_node_init(list_node_t *self, list_node_type_t type,
	void *data, int buffers_idx);
void	list_node_reinit(list_node_t *self, list_t *list, void *data);
void	list_node_deinit(list_node_t *self, list_t *list, list_fct_t fct);

/* list_extract.c */
char	*list_extract(list_t *list, const char *delims);

/* list_push.c */
bool	list_push_back(list_t *self, void *data);
bool	list_push_front(list_t *self, void *data);

/* list_utils.c */
void	list_clear(list_t *self, list_fct_t fct);
size_t	list_size(list_t *self);
bool	list_is_empty(list_t *self);

/* list_pop.c */
void	*list_pop_front(list_t *self);
void	*list_pop_back(list_t *self);

/* list_get.c */
void	*list_get_front(list_t *self);
void	*list_get_back(list_t *self);

/* list.c */
extern const class_t *LIST;
extern const class_t *LIST_ALLOC;

#endif // !list_HPP
