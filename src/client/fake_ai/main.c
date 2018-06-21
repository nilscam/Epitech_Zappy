/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "tcp_connection_client.h"
#include <stdbool.h>
#include <time.h>

int		read_data(t_client *client)
{
	static bool chooseTeam = false;
	char	buff[SIZE_BUFF];

	int ret = read(client->_fd_server, buff, SIZE_BUFF - 1);
	if  (ret <= 0) {
		return (0);
	}
	buff[ret] = 0;
	buff_put(&client->_cbuf, buff);
	if (buff[ret - 1] == '\n') {
		char *str = buff_get(&client->_cbuf);
		printf("GOT : [%s]\n", str);
		if (!chooseTeam) {
			chooseTeam = true;
		}
		if (chooseTeam) {
			char buff[10000];
			char *action = "Forward";
			int random = rand();
			int moveFwd = random & 2;
			if (moveFwd) {
				action = "Forward";
			} else {
				int turnLeft = random & 3;
				if (turnLeft) {
					action = "Left";
				} else {
					action = "Right";
				}
			}
			printf("SENDING : '%s'\n", action);
			sprintf(buff, "%s\n", action);
			client->write(client->_fd_server, buff);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_client	*client = init_struct_client();

	if (!client || ac != 4) {
		dprintf(2, "USAGE: %s IP PORT TEAM\n", av[0]);
		return (84);
	}
	printf("%s %s %s\n", av[1], av[2], av[3]);
	if (client->init(client, av[1], atoi(av[2]), "TCP") == -1)
		return (84);
	srand(time(NULL));
	bool sentChooseTeam = false;
	while (1) {
		client->select(client, TIMEOUT);
		if (client->can_read(client, client->_fd_server)) {
			if (!read_data(client))
				break;
		}
		if (client->can_write(client, client->_fd_server)) {
			// client->write(client->_fd_server, "Lol\n");
			if (!sentChooseTeam) {
				sentChooseTeam = true;
				char buff[10000];
				sprintf(buff, "%s\n", av[3]);
				client->write(client->_fd_server, buff);
			}
			sleep(1);
		}
		if (client->can_err(client, client->_fd_server)) {}
	}
	client->stop(client);
	return (0);
}