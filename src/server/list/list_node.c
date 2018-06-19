/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_node.c
*/

#include "list.h"

void	list_node_init(list_node_t *self, list_node_type_t type,
	void *data, int buffers_idx)
{
	self->prev = NULL;
	self->next = NULL;
	self->data = data;
	self->type = type;
	self->buffers_idx = buffers_idx;
}

void	list_node_reinit(list_node_t *self, list_t *list, void *data)
{
	self->prev = NULL;
	self->next = NULL;
	self->data = data;
	self->type = NODE_USED;
	if (self->buffers_idx == list->last_unused_buffers) {
		list->last_unused_buffers = self->buffers_idx + 1;
	}
}

void	list_node_deinit(list_node_t *self, list_t *list, list_fct_t fct)
{
	if (fct && self->data) {
		fct(self->data);
	}
	if (self->type == NODE_EXTRA) {
		free(self);
	} else {
		self->type = NODE_UNUSED;
		if (self->buffers_idx < list->last_unused_buffers) {
			list->last_unused_buffers = self->buffers_idx;
		}
	}
}
