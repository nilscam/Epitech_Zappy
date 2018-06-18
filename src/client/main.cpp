/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "Manager.hpp"

int	main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << "USAGE: " << av[0] << " IP PORT" << std::endl;
		return (0);
	}
	try {
		Manager manager(av[1], atoi(av[2]));
		manager.spectateGame();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (84);
	}
	return (0);
}