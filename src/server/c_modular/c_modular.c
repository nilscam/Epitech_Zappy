/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** c_modular.c
*/

#include "c_modular.h"

static object_t	*va_new(const class_t *class , va_list *ap)
{
	object_t	*obj;

	if (!class)
		return (NULL);
	obj = malloc(class->__size__);
	if (obj == NULL)
		return (NULL);
	memmove(obj, class, class->__size__);
	if (class->__init__ && !class->__init__(obj, ap)) {
		delete(obj);
		return (NULL);
	}
	return (obj);
}

object_t	*new(const class_t *class, ...)
{
	object_t	*obj;
	va_list		args;

	va_start(args, class);
	obj = va_new(class, &args);
	va_end(args);
	return (obj);
}

void	delete(object_t *ptr)
{
	if (ptr) {
		if (((class_t*)ptr)->__deinit__)
			((class_t*)ptr)->__deinit__(ptr);
		free(ptr);
	}
}

void	safe_free(void **ptr)
{
	if (ptr && *ptr) {
		free(*ptr);
		*ptr = NULL;
	}
}

void	safe_delete(void **ptr)
{
	if (ptr && *ptr) {
		delete(*ptr);
		*ptr = NULL;
	}
}