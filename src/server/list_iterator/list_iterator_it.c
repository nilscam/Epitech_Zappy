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
