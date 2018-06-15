/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_extract.c
*/

#include "list.h"
#include "list_iterator.h"
#include "str_concat.h"

static bool	has_cmd_in_buff(list_t *list, const char *delims,
	size_t *iteration, size_t *cmd_size)
{
	list_iterator_t	it;
	char		*data;
	size_t		dpos = 0;

	INIT(LIST_IT, it, list);
	(*iteration) = 0;
	(*cmd_size) = 0;
	do {
		data = list_it_get(&it);
		for (size_t i = 0; data && data[i]; ++i) {
			++(*cmd_size);
			dpos += (data[i] == delims[dpos] ? 1 : -dpos);
			if (delims[dpos] == '\0')
				return (true);
		}
		list_it_iterate(&it);
	} while (data && ++(*iteration));
	DEINIT(it);
	return (false);
}

static void	add_rest_cmd_to_buff(list_t *list, char *rest)
{
	if (!rest || !(*rest))
		return;
	rest = strdup(rest);
	if (!rest) {
		list_clear(list, (void (*)(void *))free);
	} else {
		list_push_front(list, rest);
	}
}

char	*list_extract(list_t *list, const char *delims)
{
	list_iterator_t	it;
	char		*data;
	char		*cmd = NULL;
	size_t		cmd_size = 0;
	size_t		iteration = 0;

	if (!has_cmd_in_buff(list, delims, &iteration, &cmd_size))
		return (NULL);
	INIT(LIST_IT, it, list);
	for (size_t i = 0; i <= iteration; ++i) {
		data = list_it_get(&it);
		list_it_erase(&it, NULL);
		cmd = str_concat_free(cmd, data);
	}
	if (!cmd)
		return NULL;
	cmd[cmd_size - strlen(delims)] = 0;
	add_rest_cmd_to_buff(list, cmd + cmd_size);
	DEINIT(it);
	return (cmd);
}
