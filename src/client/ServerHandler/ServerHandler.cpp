/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ServerHandler.cpp
*/

#include "ServerHandler.hpp"
#include "Clock.hpp"

ServerHandler::~ServerHandler()
{
	for (auto it = _childs.begin(); it != _childs.end();)
	{
		auto & child = *it;
		child.terminate();
		it = _childs.erase(it);
	}
	stopServer();
}

bool	ServerHandler::startServer(
	int width, int height, unsigned short port,
	std::vector<std::string> const & teams,
	int playerPerTeam, double freq
)
{
	bool success = false;
	_server.terminate();
	_port = port;
	_teams = teams;
	int pid = fork();
	if (pid > 0)
	{
		Clock timeout;
		int k = -1;
		do {
			k = kill(pid, 0);
		} while (k != 0 && timeout.timeSinceMark() > 2000);
		success = k == 0;
		if (success)
		{
			_server.setPid(pid);
		}
	}
	else if (pid == 0)
	{
		char const ** argv = (char const **)malloc(sizeof(char *) * (13 + teams.size()));
		if (!argv)
		{
			exit(1);
		}
		size_t i = 0;
		argv[i++] = std::string("./zappy_server").c_str();
		argv[i++] = std::string("-p").c_str();
		argv[i++] = std::to_string(port).c_str();
		argv[i++] = std::string("-x").c_str();
		argv[i++] = std::to_string(width).c_str();
		argv[i++] = std::string("-y").c_str();
		argv[i++] = std::to_string(height).c_str();
		argv[i++] = std::string("-n").c_str();
		for (auto const & team : teams)
		{
			argv[i++] = team.c_str();
		}
		argv[i++] = std::string("-c").c_str();
		argv[i++] = std::to_string(playerPerTeam).c_str();
		argv[i++] = std::string("-f").c_str();
		argv[i++] = std::to_string(freq).c_str();
		argv[i++] = NULL;
		execvp(argv[0], (char * const *)argv);
		free(argv);
		exit(0);
	}
	return success;
}

void	ServerHandler::stopServer(void) noexcept
{
	_server.terminate();
}

void	ServerHandler::addAi(std::string const & team, int nb)
{
	for (int i = 0; i < nb; ++i)
	{
		addAi(team);
	}
}

void	ServerHandler::addAi(std::string const & team)
{
	int pid = fork();
	if (pid == -1)
	{
		throw ExceptFork("fork: " + std::string(strerror(errno)));
	}
	else if (pid > 0)
	{
		_childs.emplace_back(pid);
	}
	else
	{
		char const ** argv = (char const **)malloc(sizeof(char *) * 8);
		if (!argv)
		{
			exit(1);
		}
		size_t i = 0;
		// zappy ai
		argv[i++] = std::string("./zappy_ai").c_str();
		argv[i++] = std::string("-p").c_str();
		argv[i++] = std::to_string(_port).c_str();
		argv[i++] = std::string("-n").c_str();
		argv[i++] = team.c_str();
		argv[i++] = std::string("-h").c_str();
		argv[i++] = std::string("127.0.0.1").c_str();
		argv[i++] = NULL;
		execvp(argv[0], (char * const *)argv);
		free(argv);
		exit(0);
	}
}

void	ServerHandler::addAiAllTeams(int nb) noexcept
{
	for (auto const & team : _teams)
	{
		addAi(team, nb);
	}
}
