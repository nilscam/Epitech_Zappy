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

	enum MapSqt
	{
		None = 0x0,
		Food = 0x1,
		Stone1 = 0x2,
		Stone2 = 0x4,
		Stone3 = 0x8,
		Stone4 = 0x10,
		Stone5 = 0x20,
		Stone6 = 0x40
	};

	Map() = default;
	Map(const std::vector<std::vector<MapSqt>> &map);
	virtual ~Map() = default;
	Map(Map const & rhs) = default;
	Map(Map && rhs) = default;
	Map & operator=(Map const & rhs) = default;
	Map & operator=(Map && rhs) = default;

	void	createMap(int width, int height);
	void	updateMap(char **infos);
	MapSqt	getSqt(Point const & pos) const;
	std::vector<Point>	getSqtPoints(MapSqt sqt) const;
	std::vector<std::vector<MapSqt>>	getMapSqt() const;
	bool				isInMap(Point pos);

	friend std::ostream & operator<<(std::ostream & os, Map const & map);

private:

	std::vector<std::vector<MapSqt>>	_map;
};

#endif // !Map_HPP
