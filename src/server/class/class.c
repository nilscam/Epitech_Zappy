/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** c_modular.c
*/

#include "class.h"

static bool	va_new_class(const class_t *class, object_t *obj, va_list *ap)
{
	if (!class || !obj)
		return false;
	memmove(obj, class, class->__size__);
	if (class->__init__ && !class->__init__(obj, ap))
		return false;
	return true;
}

object_t	*new_class(const class_t *class, ...)
{
	object_t	*obj = malloc(class->__size__);
	va_list		args;

	va_start(args, class);
	if (!va_new_class(class, obj, &args)) {
		delete_class(obj);
		obj = NULL;
	} 
	va_end(args);
	return (obj);
}

void	delete_class(object_t *ptr)
{
	if (ptr) {
		deinit_class(ptr);
		free(ptr);
	}
}

bool	init_class(const class_t *class, object_t *obj, ...)
{
	bool	success;
	va_list	args;

	va_start(args, obj);
	success = va_new_class(class, obj, &args);
	if (!success) {
		deinit_class(obj);
	}
	va_end(args);
	return success;
}

void	deinit_class(object_t *ptr)
{
	if (ptr) {
		if (((class_t *)ptr)->__deinit__)
			((class_t *)ptr)->__deinit__(ptr);
	}
 }
