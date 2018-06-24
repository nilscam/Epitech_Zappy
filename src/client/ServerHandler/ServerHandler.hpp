/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ServerHandler.hpp
*/

#ifndef ServerHandler_HPP
#define ServerHandler_HPP

#include "IServerHandler.hpp"
#include "ChildHandler.hpp"

#include <unistd.h>
#include <string.h>

class ServerHandler : public IServerHandler
{
public:

	struct ExceptFork : public std::exception
	{
		std::string s;
		ExceptFork(std::string const & ss) : s(ss) {}
		~ExceptFork() throw () {}
		char const * what() const throw() { return s.c_str(); }
	};

	ServerHandler() = default;
	~ServerHandler() override;
	ServerHandler(ServerHandler const & rhs) = delete;
	ServerHandler(ServerHandler && rhs) = delete;
	ServerHandler & operator=(ServerHandler const & rhs) = delete;
	ServerHandler & operator=(ServerHandler && rhs) = delete;

	bool	startServer(
		int width, int height, unsigned short port,
		std::vector<std::string> const & teams,
		int playerPerTeam, double freq
	) override;
	void	stopServer(void) noexcept override;
	void	addAi(std::string const & team, int nb) override;
	void	addAi(std::string const & team) override;
	void	addAiAllTeams(int nb) noexcept override;

private:

	std::vector<std::string>	_teams;
	std::vector<ChildHandler>	_childs;
	ChildHandler				_server;
	unsigned short				_port;

};

#endif // !ServerHandler_HPP
