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
		if (ac == 2) {
			auto man = std::make_shared<Manager>();
			if (man->init(std::string("127.0.0.1").c_str(), atoi(av[1]))) {
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