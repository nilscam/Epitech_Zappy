/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_list_alloc.c
*/

#include "list.h"
#include "list_iterator.h"
#include <stdio.h>

static void	show_list(char *str)
{
	printf("--> '%s'\n", str);
}

int	test_list_alloc(void)
{
	list_t	*list = NEW(LIST_ALLOC, 3);
	list_push_back(list, "bbb");
	list_push_back(list, "ccc");
	list_push_back(list, "ddd");
	list_it_all(list, (list_it_fct_t)show_list);
	printf("removing ccc at 1\n");
	list_erase_at(list, NULL, 1);
	list_it_all(list, (list_it_fct_t)show_list);
	list_push_back(list, "eee");
	DELETE(list);
	return 0;
}
