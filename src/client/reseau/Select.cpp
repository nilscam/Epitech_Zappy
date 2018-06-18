/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Select.cpp
*/

#include "Select.hpp"

void	Select::addFd(int fd) noexcept
{
	_fds.push_back(fd);
}

void	Select::select(int timeOut)
{
	fillFds();
	int nfds = getNfds();
	struct timeval tv = { timeOut, 0 };
	if (::select(nfds, &_rFd, &_wFd, &_eFd, &tv) < 0)
		throw ExceptSelect("select: " + std::string(strerror(errno)));
}

int	Select::getNfds(void) const noexcept
{
	int nfds = -1;
	for (int fd : _fds)
	{
		nfds = std::max(nfds, fd);
	}
	return nfds + 1;
}

void	Select::fillFds(void) noexcept
{
	FD_ZERO(&_rFd);
	FD_ZERO(&_wFd);
	FD_ZERO(&_eFd);
	for (int fd : _fds)
	{
		FD_SET(fd, &_rFd);
		FD_SET(fd, &_wFd);
		FD_SET(fd, &_eFd);
	}
}

bool	Select::canRead(int fd) noexcept
{
	return FD_ISSET(fd, &_rFd);
}

bool	Select::canWrite(int fd) noexcept
{
	return FD_ISSET(fd, &_wFd);
}

bool	Select::canError(int fd) noexcept
{
	return FD_ISSET(fd, &_eFd);
}
