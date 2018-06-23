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

void	ChildHandler::terminate(void) noexcept
{
	if (_pid >= 0)
	{
		kill(_pid, SIGINT);
		waitpid(_pid, NULL, 0);
		_pid = -1;
	}
}
