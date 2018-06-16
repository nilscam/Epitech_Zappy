/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator_it.c
*/

#include "list_iterator.h"

static void	call_fct(list_it_fct_t fct, void *data, va_list *args)
{
	va_list	cp_args;

	if (fct) {
		va_copy(cp_args, *args);
		fct(data, &cp_args);
		va_end(cp_args);
	}
}

static bool	call_fct_bool(list_it_fct_bool_t fct, void *data, va_list *args)
{
	bool	res = false;
	va_list	cp_args;

	if (fct) {
		va_copy(cp_args, *args);
		res = fct(data, &cp_args);
		va_end(cp_args);
	}
	return res;
}

bool	list_it_all(list_t *list, list_it_fct_t fct, ...)
{
	list_iterator_t	it;
	va_list		args;
	bool		has_it = false;

	if (!INIT(LIST_IT, it, list))
		return false;
	va_start(args, fct);
	while (list_it_can_iterate(&it)) {
		has_it = true;
		call_fct(fct, list_it_get(&it), &args);
		list_it_iterate(&it);
	}
	va_end(args);
	DEINIT(it);
	return has_it;
}

bool	list_it_remove(list_t *list, list_it_fct_remove_t fct_remove, ...)
{
	list_iterator_t	it;
	va_list		args;
	bool		has_it = false;

	if (!INIT(LIST_IT, it, list))
		return false;
	va_start(args, fct_remove);
	while (list_it_can_iterate(&it)) {
		has_it = true;
		if (call_fct_bool(fct_remove, list_it_get(&it), &args))
			list_it_erase(&it, NULL);
		else
			list_it_iterate(&it);
	}
	va_end(args);
	DEINIT(it);
	return has_it;
}

void	*list_it_find(list_t *list, list_it_fct_find_t fct_find, ...)
{
	list_iterator_t	it;
	va_list		args;
	void		*data = NULL;

	if (!INIT(LIST_IT, it, list))
		return false;
	va_start(args, fct_find);
	while (list_it_can_iterate(&it)) {
		data = list_it_get(&it);
		if (call_fct_bool(fct_find, data, &args))
			break;
		list_it_iterate(&it);
		data = NULL;
	}
	va_end(args);
	DEINIT(it);
	return data;
}
