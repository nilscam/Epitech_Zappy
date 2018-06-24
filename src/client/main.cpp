/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "Manager.hpp"

int test_hud();

int	main(int ac, char **av)
{
	try {
		if (ac == 3) {
			auto man = std::make_shared<Manager>();
			if (man->init(av[1], atoi(av[2]))) {
				man->spectateGame();
			}
		} else if (ac == 1) {
			auto man = std::make_shared<Manager>();
			man->init();
			if (!man->needToExit()) {
				man->spectateGame();
			}
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (84);
	}
	return (0);
}