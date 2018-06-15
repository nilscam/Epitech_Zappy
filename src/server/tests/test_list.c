/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_list.c
*/

#include "list.h"
#include "list_iterator.h"
#include <stdio.h>

static void	list_handler(void *data)
{
	printf("list_handler: %s\n", (char *)data);
}

static void	test_list_iterator(list_t *list)
{
	list_iterator_t *it = NEW(LIST_IT, list);
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
	SAFE_DELETE(it);
}

static void	test_list_iterator_stack(list_t *list)
{
	list_iterator_t it;
	char		*str;

	if (!INIT(LIST_IT, it, list))
		return;
	while (list_it_can_iterate(&it)) {
		str = list_it_get(&it);
		printf("--> '%s'\n", str);
		if (strcmp(str, "ccc") == 0) {
			list_it_erase(&it, NULL);
		} else if (strcmp(str, "aaa") == 0) {
			list_it_set(&it, "hello");
		} else {
			list_it_iterate(&it);
		}
	}
	DEINIT(it);
}

int	test_list(void)
{
	list_t *list = NEW(LIST);

	if (!list)
		return 84;
	list_push_back(list, "aaa");
	list_push_back(list, "bbb");
	list_push_back(list, "ccc");
	list_push_front(list, "ddd");
	list_push_back(list, "delete me");
	list_push_front(list, "delete me too");
	printf("----- it_0 (show front & back)\n");
	printf("front: '%s'\n", list_get_front(list));
	printf("back: '%s'\n", list_get_back(list));
	printf("----- it_1 (pop front & back)\n");
	printf("front: '%s'\n", list_pop_front(list));
	printf("back: '%s'\n", list_pop_back(list));
	printf("----- it_2 (show all)\n");
	list_it_all(list, (list_it_fct_t)list_handler);
	printf("----- it_3 (remove ccc and add hello if aaa)\n");
	test_list_iterator(list);
	printf("----- it_4 (remove ccc and add hello if aaa)\n");
	test_list_iterator_stack(list);
	printf("----- it_5 (clear list)\n");
	list_clear(list, list_handler);
	printf("----- it_6 (show all)\n");
	list_it_all(list, (list_it_fct_t)list_handler);
	SAFE_DELETE(list);
	return 0;
}
