/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_list_extract.c
*/

#include "list.h"
#include "list_iterator.h"
#include <stdio.h>

static void	list_handler(void *data)
{
	printf("list_handler: %s\n", (char *)data);
}

static void	fill_list(list_t *list)
{
	list_push_back(list, strdup("abcd"));
	list_push_back(list, strdup(" "));
	list_push_back(list, strdup("e"));
	list_push_back(list, strdup("fgh"));
	list_push_back(list, strdup("\n"));
	list_push_back(list, strdup("i"));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup("jkl\nmno"));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup("pkrst"));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup(""));
	list_push_back(list, strdup("\n"));
}

int	test_list_extract(void)
{
	list_t *list = NEW(LIST);
	fill_list(list);
	bool ok;
	char *str;
	do {
		str = list_extract(list, "\n");
		ok = str != NULL;
		printf("str = '%s'\n", str);
		SAFE_FREE(str);
	} while (ok);
	list_it_all(list, (list_it_fct_t)list_handler);
	DELETE(list);
	return 0;
}
