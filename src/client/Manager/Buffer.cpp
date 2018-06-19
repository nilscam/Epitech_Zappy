/*
** EPITECH PROJECT, 2018
** Buffer
** File description:
** Buffer
*/

#include "Buffer.hpp"

Buffer::Buffer(int size)
{
	_buffer = (char *)malloc(size + 1);
	memset(_buffer, 0, size);
	_size = size;
	_wr = 0;
	_rd = 0;
}

Buffer::~Buffer()
{
	if (_buffer) {
		free(_buffer);
	}
}

void	Buffer::Put(const char *str)
{
	int	i = -1;

	if (str) {
		while (str[++i]) {
			_buffer[_wr] = str[i];
			_wr = (_wr + 1) % _size;
			_rd = (_wr == _rd ?
			(_rd + 1) % _size : _rd);
		}
	}
}

char	*Buffer::Get(void)
{
	int		size = _wr - _rd, i = -1;
	char	*str;

	if (size < 0)
		size = _size - (_rd - _wr);
	str = (char *)malloc(size + 4);
	if (!str || !size)
		return (NULL);
	memset(str, 0, size + 3);
	while (++i < size) {
		str[i] = _buffer[_rd];
		_buffer[_rd] = 0;
		_rd = (_rd + 1) % _size;
	}
	return (str);
}
bool	Buffer::isEndOfCommand(void)
{
	return (_wr && _buffer[_wr - 1] == '\n');
}