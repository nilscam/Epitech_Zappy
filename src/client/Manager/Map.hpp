/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map.hpp
*/

#ifndef Map_HPP
#define Map_HPP

#include "Point.hpp"
#include "Direction.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <map>

class Map
{
public:

	struct ExceptInvalidFile : public std::exception
	{
		std::string s;
		ExceptInvalidFile(std::string const & ss) : s(ss) {}
		~ExceptInvalidFile() throw () {}
		char const * what() const throw() { return s.c_str(); }
	};

	struct	MapCase
	{
		int		_food;
		int		_stone1;
		int		_stone2;
		int		_stone3;
		int		_stone4;
		int		_stone5;
		int		_stone6;
	};

	Map() = default;
	Map(const std::vector<std::vector<MapCase>> &map);
	virtual ~Map() = default;
	Map(Map const & rhs) = default;
	Map(Map && rhs) = default;
	Map & operator=(Map const & rhs) = default;
	Map & operator=(Map && rhs) = default;

	void	createMap(int width, int height);
	void	updateMap(char **infos);
	MapCase	getCase(Point const & pos) const;
	void	setCase(Point const & pos, MapCase items);
	std::vector<std::vector<MapCase>>	getMapCase() const;
	bool				isInMap(Point pos);

	friend std::ostream & operator<<(std::ostream & os, Map const & map);

private:

	std::vector<std::vector<MapCase>>	_map;
};

#endif // !Map_HPP
