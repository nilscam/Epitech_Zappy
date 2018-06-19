/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map.cpp
*/

#include "Map.hpp"

void	Map::createMap(int width, int height)
{
	std::vector<MapCase>	v;
	struct	MapCase m;
	m._food = 0;
	m._stone1 = 0;
	m._stone2 = 0;
	m._stone3 = 0;
	m._stone4 = 0;
	m._stone5 = 0;
	m._stone6 = 0;
	for(int i = 0; i < width; i++) {
		v.push_back(m);
	}
	for(int i = 0; i < height; i++){
		_map.push_back(v);
	}
}

void	Map::updateMap(char **infos)
{
	int	i = 0;

	while (infos[i]) {
		if (!infos[i + 1] || !infos[i + 2] || !infos[i + 3]
		|| !infos[i + 4] || !infos[i + 5] || !infos[i + 6]
		|| !infos[i + 7] || !infos[i + 8] || !infos[i + 9])
			break;
		Point point(atoi(infos[i + 1]), atoi(infos[i + 2]));
		if (this->isInMap(point)) {
			struct MapCase items;
			items._food = atoi(_args[i + 3]);
			items._stone1 = atoi(_args[i + 4]);
			items._stone2 = atoi(_args[i + 5]);
			items._stone3 = atoi(_args[i + 6]);
			items._stone4 = atoi(_args[i + 7]);
			items._stone5 = atoi(_args[i + 8]);
			items._stone6 = atoi(_args[i + 9]);
			_map[point.y()][point.x()] = items;
		}
		i += 10;
	}
}

Map::MapCase	Map::getCase(Point const & pos) const
{
	MapCase DEFAULT_CASE;
	DEFAULT_CASE._food = 0;
	DEFAULT_CASE._stone1 = 0;
	DEFAULT_CASE._stone2 = 0;
	DEFAULT_CASE._stone3 = 0;
	DEFAULT_CASE._stone4 = 0;
	DEFAULT_CASE._stone5 = 0;
	DEFAULT_CASE._stone6 = 0;
	int x = pos.getX();
	int y = pos.getY();

	if (y < 0 || y >= this->map.size())
		return DEFAULT_SQT;
	else if (x < 0 || x >= this->map[y].size())
		return DEFAULT_SQT;
	return this->map[y][x];
}

void	setCase(Point const & pos, MapCase items)
{
	if (!this->isInMap(pos)) {
		return;
	}
	_map[pos.y()][pos.x()] = items;
}

std::vector<std::vector<Map::MapCase>>	Map::getMapCase() const
{
	return map;
}

bool	Map::isInMap(Point pos)
{
	if (0 <= pos.getY() && pos.getY() < map.size()) {
		if (0 <= pos.getX() && pos.getX() < map[pos.getY()].size())
			return (true);
	}
	return (false);
}

Map::Map(const std::vector<std::vector<Map::MapCase>> &map)
{
	this->map = map;
}

std::ostream & operator<<(std::ostream & os, Map const & map)
{
	(void)os; (void)map;
	return os;
}