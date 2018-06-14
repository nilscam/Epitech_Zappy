/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "tcp_connection_client.h"

int		read_data(t_client *client)
{
	char	buff[SIZE_BUFF];

	int ret = read(client->_fd_server, buff, SIZE_BUFF - 1);
	if  (ret <= 0) {
		return (0);
	}
	buff[ret] = 0;
	buff_put(&client->_cbuf, buff);
	if (buff[ret - 1] == '\n') {
		char *str = buff_get(&client->_cbuf);
		printf("[%s]\n", str);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_client	*client = init_struct_client();

	if (!client || ac != 3)
		return (84);
	if (client->init(client, av[1], atoi(av[2]), "TCP") == -1)
		return (84);
	while (1) {
		client->select(client, TIMEOUT);
		if (client->can_read(client, client->_fd_server)) {
			if (!read_data(client))
				break;
		}
		if (client->can_write(client, client->_fd_server)) {
			client->write(client->_fd_server, "Lol\n");
			sleep(1);
		}
		if (client->can_err(client, client->_fd_server)) {}
	}
	client->stop(client);
	return (0);
}