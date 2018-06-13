/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** c_modular.h
*/

#ifndef C_MODULAR_H_
#define C_MODULAR_H_

#define NEW(x, ...)	new_class(x, ##__VA_ARGS__)
#define DELETE(x)	delete_class((object_t *)x)
#define SAFE_FREE(x)	safe_free((void **)(&x))
#define SAFE_DELETE(x)	safe_delete_class((void **)(&x))

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void object_t;
typedef	bool (*object_cst_t)(object_t *self, va_list *args);
typedef	void (*object_dst_t)(object_t *self);

typedef struct
{
	const size_t		__size__;
	const char		*__name__;
	object_cst_t		__init__;
	object_dst_t		__deinit__;
}	class_t;

object_t	*new_class(const class_t *class, ...);
void		delete_class(object_t *ptr);
void		safe_free(void **ptr);
void		safe_delete_class(void **ptr);

#endif /* !C_MODULAR_H_ */
