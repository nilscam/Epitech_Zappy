/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list.c
*/

#include "list.h"

static bool	new_list(
	__attribute__((unused)) list_t *self,
	__attribute__((unused)) va_list *args)
{
	return true;
}

static void	delete_list(list_t *self)
{
	list_clear(self, NULL);
}

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

void	list_clear(list_t *self, void (*fct)(void *))
{
	list_node_t	*tmp = self->tail;
	list_node_t	*next;

	while (tmp) {
		next = tmp->next;
		if (fct)
			fct(tmp->data);
		free(tmp);
		tmp = next;
	}
	self->tail = NULL;
	self->head = NULL;
	self->size = 0;
}

size_t	list_size(list_t *self)
{
	return self->size;
}

static const list_t	LIST_CLASS = {
	{
		sizeof(list_t),
		"List",
		(object_cst_t) new_list,
		(object_dst_t) delete_list
	},
	NULL,
	NULL,
	0
};

const class_t	*LIST = (class_t *) &LIST_CLASS;
