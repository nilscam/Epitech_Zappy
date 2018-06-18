/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** BUFFER.hpp
*/

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

class Buffer
{
public:
	Buffer(int size);
	~Buffer();
	void	Put(const char *str);
	char	*Get(void);
	bool	isEndOfCommand(void);
private:
	char	*_buffer;
	int		_wr;
	int		_rd;
	int		_size;
};

#endif // !BUFFER_HPP
