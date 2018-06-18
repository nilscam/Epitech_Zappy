/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ChildHandler.cpp
*/

#include "ChildHandler.hpp"

ChildHandler::ChildHandler()
	:	ChildHandler(-1)
{}

ChildHandler::ChildHandler(int pid)
	:	_pid(pid)
{}

int	ChildHandler::getPid(void) const noexcept
{
	return _pid;
}

void	ChildHandler::setPid(int pid) noexcept
{
	_pid = pid;
}

bool	ChildHandler::isRunning(void) const noexcept
{
	if (_pid < 0)
	{
		return false;
	}
	while (waitpid(-1, NULL, WNOHANG) > 0);
	return (kill(_pid, 0) == 0);
}

void	ChildHandler::terminate(void) noexcept
{
	if (isRunning())
	{
		kill(_pid, SIGINT);
		waitpid(_pid, NULL, 0);
		_pid = -1;
	}
}
