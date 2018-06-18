/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Select.hpp
*/

#ifndef Select_HPP
#define Select_HPP

#include <vector>
#include <string>
#include <exception>

#include <sys/select.h>
#include <cstring>
#include <errno.h>

class Select
{
public:

	struct ExceptSelect : public std::exception
	{
		std::string s;
		ExceptSelect(std::string const & ss) : s(ss) {}
		~ExceptSelect() throw () {}
		char const * what() const throw() { return s.c_str(); }
	};

	Select() = default;
	virtual ~Select() = default;
	Select(Select const & rhs) = default;
	Select(Select && rhs) = default;
	Select & operator=(Select const & rhs) = default;
	Select & operator=(Select && rhs) = default;

	void	addFd(int fd) noexcept;
	void	select(int timeOut);
	bool	canRead(int fd) noexcept;
	bool	canWrite(int fd) noexcept;
	bool	canError(int fd) noexcept;

private:

	int		getNfds(void) const noexcept;
	void	fillFds(void) noexcept;

	std::vector<int>	_fds;
	fd_set				_rFd;
	fd_set				_wFd;
	fd_set				_eFd;

};

#endif // !Select_HPP
