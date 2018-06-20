/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main.cpp
*/

#include "ServerHandler.hpp"
#include <iostream>

int	main(void)
{
	ServerHandler handler;
	std::cout << "--------------------------START-----------------------" << std::endl;
	handler.startServer(10, 10, 4242, { "red", "blue" }, 12, 1);
	std::cout << "..." << std::endl;
	sleep(1);
	std::cout << "...AI..." << std::endl;
	handler.addAiAllTeams(2);
	std::cout << "..." << std::endl;
	sleep(3);
	std::cout << "--------------------------STOP-----------------------" << std::endl;
	handler.stopServer();
	// std::string str;
	// while (std::getline(std::cin, str));
	return 0;
}
