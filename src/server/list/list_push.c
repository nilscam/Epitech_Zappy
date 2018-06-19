/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_push.c
*/

#include "list.h"

static list_node_t	*new_list_node(list_t *self, void *data)
{
	list_node_t	*node = NULL;
	int		i = self->last_unused_buffers;

	for (; i >= 0 && i < self->max_buffers; ++i) {
		if (self->buffers[i].type == NODE_UNUSED) {
			node = self->buffers + i;
			break;
		}
	}
	if (!node) {
		node = malloc(sizeof(list_node_t));
		if (!node)
			return NULL;
		list_node_init(node, NODE_EXTRA, data, -1);
	} else {
		list_node_reinit(node, self, data);
	}
	return node;
}

bool	list_push_back(list_t *self, void *data)
{
	list_node_t	*node = new_list_node(self, data);

	if (!node) {
		return false;
	} else if (!self->tail || !self->head) {
		self->tail = node;
		self->head = node;
	} else {
		node->prev = self->head;
		self->head->next = node;
		self->head = node;
	}
	++self->size;
	return true;
}

bool	list_push_front(list_t *self, void *data)
{
	list_node_t	*node = new_list_node(self, data);

	if (!node) {
		return false;
	} else if (!self->tail || !self->head) {
		self->tail = node;
		self->head = node;
	} else {
		node->next = self->tail;
		self->tail->prev = node;
		self->tail = node;
	}
	++self->size;
	return true;
}
