/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ChildHandler.hpp
*/

#ifndef ChildHandler_HPP
#define ChildHandler_HPP

#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

class ChildHandler
{
public:

	ChildHandler();
	ChildHandler(int pid);
	virtual ~ChildHandler() = default;
	ChildHandler(ChildHandler const & rhs) = default;
	ChildHandler(ChildHandler && rhs) = default;
	ChildHandler & operator=(ChildHandler const & rhs) = default;
	ChildHandler & operator=(ChildHandler && rhs) = default;

	int		getPid(void) const noexcept;
	void	setPid(int pid) noexcept;
	bool	isRunning(void) const noexcept;
	void	terminate(void) noexcept;

private:

	int		_pid;

};

#endif // !ChildHandler_HPP
