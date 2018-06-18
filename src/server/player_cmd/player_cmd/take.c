/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** take.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

bool	validate_take(player_cmd_arg_t *args)
{
	char	*obj = args->args[1];
	int	*from_ptrs[7];
	char	*reprs[7];

	fill_inv_reprs((char **)reprs);
	fill_inv_ptrs(&args->player->pos->inventory, (int **)from_ptrs);
	for (size_t i = 0; i < SIZE_ARRAY(reprs); ++i) {
		if (strcmp(obj, reprs[i]) == 0 && *from_ptrs[i] > 0) {
			return true;
		}
	}
	client_callback(CB_KO, args->client);
	return false;
}

void	player_cmd_take(player_cmd_arg_t *args)
{
	char	*obj = args->args[1];
	int	*from_ptrs[7];
	int	*to_ptrs[7];
	char	*reprs[7];

	fill_inv_reprs((char **)reprs);
	fill_inv_ptrs(&args->player->pos->inventory, (int **)from_ptrs);
	fill_inv_ptrs(&args->player->inventory, (int **)to_ptrs);
	for (size_t i = 0; i < SIZE_ARRAY(reprs); ++i) {
		if (strcmp(obj, reprs[i]) == 0 && *from_ptrs[i] > 0) {
			*from_ptrs[i] -= 1;
			*to_ptrs[i] += 1;
			client_callback(CB_OK, args->client);
			clients_callback(CB_RESOURCE_COLLECTING,
				args->server->spectators_clients,
				args->player->id, i);
			return;
		}
	}
	client_callback(CB_KO, args->client);
}
