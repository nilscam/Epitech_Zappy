/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** class_utils.c
*/

#include "class.h"

void	safe_free(void **ptr)
{
	if (ptr && *ptr) {
		free(*ptr);
		*ptr = NULL;
	}
}

void	safe_delete_class(void **ptr)
{
	if (ptr && *ptr) {
		delete_class(*ptr);
		*ptr = NULL;
	}
}
