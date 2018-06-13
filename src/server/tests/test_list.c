/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_list.c
*/

#include "list.h"
#include "list_iterator.h"
#include <stdio.h>

static void	clear_list_handler(void *data)
{
	printf("clear: %s\n", (char *)data);
}

static void	test_list_iterator(list_t *list)
{
	list_iterator_t *it = new(LIST_IT, list);
	char		*str;

	while (it && list_it_can_iterate(it)) {
		str = list_it_get(it);
		printf("--> '%s'\n", str);
		if (strcmp(str, "ccc") == 0) {
			list_it_erase(it, NULL);
		} else if (strcmp(str, "aaa") == 0) {
			list_it_set(it, "hello");
		} else {
			list_it_iterate(it);
		}
	}
	delete(it);
}

int	test_list(void)
{
	list_t *list = new(LIST);
	
	if (!list)
		return 84;
	list_push_back(list, "aaa");
	list_push_back(list, "bbb");
	list_push_back(list, "ccc");
	list_push_front(list, "ddd");
	test_list_iterator(list);
	list_clear(list, clear_list_handler);
	delete(list);
	return 0;
}
