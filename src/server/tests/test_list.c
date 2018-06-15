/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_list.c
*/

#include "list.h"
#include "list_iterator.h"
#include <stdio.h>
#include <string.h>

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

static void	test_valid_list_ptr(list_t *list)
{
	list_node_t	*tmp;
	list_node_t	*prev = NULL;

	tmp = list->tail;
	while (tmp) {
		if (prev && prev->next->data != tmp->data) {
			dprintf(2, "error ptr\n");
			exit(1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	printf("%s OK\n", __func__);
}

static bool	list_hello_handler(void *data)
{
	printf("list_hello_handler: %s\n", (char *)data);
	return (strcmp((char*)data, "hello") == 0);
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
	test_valid_list_ptr(list);
	printf("----- it_0 (show front & back)\n");
	printf("front: '%s'\n", (char*)list_get_front(list));
	printf("back: '%s'\n", (char*)list_get_back(list));
	test_valid_list_ptr(list);
	printf("----- it_1 (pop front & back)\n");
	printf("front: '%s'\n", (char*)list_pop_front(list));
	printf("back: '%s'\n", (char*)list_pop_back(list));
	test_valid_list_ptr(list);
	printf("----- it_2 (show all)\n");
	list_it_all(list, (list_it_fct_t)list_handler);
	test_valid_list_ptr(list);
	printf("----- it_3 (remove ccc and add hello if aaa)\n");
	test_list_iterator(list);
	test_valid_list_ptr(list);
	printf("----- it_4 (remove ccc and add hello if aaa)\n");
	test_list_iterator_stack(list);
	test_valid_list_ptr(list);
	printf("----- it_5 (remove hello)\n");
	list_it_remove(list, (list_it_fct_remove_t)list_hello_handler);
	printf("----- it_6 (clear list)\n");
	list_clear(list, list_handler);
	test_valid_list_ptr(list);
	printf("----- it_7 (show all)\n");
	list_it_all(list, (list_it_fct_t)list_handler);
	test_valid_list_ptr(list);
	SAFE_DELETE(list);
	return 0;
}
