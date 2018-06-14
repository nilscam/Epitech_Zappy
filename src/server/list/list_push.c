/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_push.c
*/

#include "list.h"

static list_node_t	*new_list_node(void *data)
{
	list_node_t	*node = malloc(sizeof(list_node_t));

	if (!node)
		return NULL;
	node->prev = NULL;
	node->next = NULL;
	node->data = data;
	return node;
}

bool	list_push_back(list_t *self, void *data)
{
	list_node_t	*node = new_list_node(data);

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
	list_node_t	*node = new_list_node(data);

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
