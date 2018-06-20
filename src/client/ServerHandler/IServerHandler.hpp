/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** IServerHandler.hpp
*/

#ifndef IServerHandler_HPP
#define IServerHandler_HPP

#include <vector>
#include <iostream>

class IServerHandler
{
public:

	virtual ~IServerHandler() = default;

	virtual void	startServer(
		int width, int height, unsigned short port,
		std::vector<std::string> const & teams,
		int playerPerTeam, double freq
	) = 0;
	virtual void	stopServer(void) noexcept = 0;
	virtual void	addAi(std::string const & team, int nb) = 0;
	virtual void	addAi(std::string const & team) noexcept = 0;
	virtual void	addAiAllTeams(int nb) noexcept = 0;

};

#endif // !IServerHandler_HPP
