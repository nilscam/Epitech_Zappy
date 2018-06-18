/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** big_buff.c
*/

#include "big_buff.h"

void	big_buff_init(big_buff_t *self)
{
	INIT(LIST, self->list);
	self->pos = 0;
}

bool	big_buff_add_data(big_buff_t *self, char *data, size_t size_data)
{
	if (size_data > BIG_BUFF_SIZE) {
		data = strndup(data, size_data);
		return data ? list_push_back(&self->list, data) : false;
	} else if (self->pos + size_data <= BIG_BUFF_SIZE) {
		memcpy(self->buff + self->pos, data, size_data);
		self->pos += size_data;
		return true;
	} else {
		list_push_back(&self->list, strndup(self->buff, self->pos));
		self->pos = 0;
		return big_buff_add_data(self, data, size_data);
	}
}

bool	big_buff_add_format(big_buff_t *self, char *format, ...)
{
	char	data[10000];
	size_t	size_data = 0;
	va_list	args;

	va_start(args, format);
	size_data = vsprintf(data, format, args);
	va_end(args);
	return big_buff_add_data(self, data, size_data);
}

char	*big_buff_cpy_data(big_buff_t *self)
{
	list_iterator_t	it;
	char		*res = NULL;

	if (self->pos > 0) {
		list_push_back(&self->list, strndup(self->buff, self->pos));
		self->pos = 0;
	}
	if (!INIT(LIST_IT, it, &self->list))
		return NULL;
	while (list_it_can_iterate(&it)) {
		res = str_concat_free(res, list_it_get(&it));
		list_it_erase(&it, NULL);
	}
	DEINIT(it);
	return res;
}

void	big_buff_deinit(big_buff_t *self)
{
	self->pos = 0;
	list_clear(&self->list, free);
}
