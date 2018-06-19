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
			items._food = atoi(infos[i + 3]);
			items._stone1 = atoi(infos[i + 4]);
			items._stone2 = atoi(infos[i + 5]);
			items._stone3 = atoi(infos[i + 6]);
			items._stone4 = atoi(infos[i + 7]);
			items._stone5 = atoi(infos[i + 8]);
			items._stone6 = atoi(infos[i + 9]);
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

	if (y < 0 || y >= static_cast<int>(this->_map.size()))
		return DEFAULT_CASE;
	else if (x < 0 || x >= static_cast<int>(this->_map[y].size()))
		return DEFAULT_CASE;
	return this->_map[y][x];
}

void	Map::setCase(Point const & pos, MapCase items)
{
	if (!this->isInMap(pos)) {
		return;
	}
	_map[pos.y()][pos.x()] = items;
}

std::vector<std::vector<Map::MapCase>>	Map::getMapCase() const
{
	return _map;
}

bool	Map::isInMap(Point pos)
{
	if (0 <= pos.getY() && pos.getY() < static_cast<int>(_map.size())) {
		if (0 <= pos.getX() && pos.getX() < static_cast<int>(_map[pos.getY()].size()))
			return (true);
	}
	return (false);
}

Map::Map(const std::vector<std::vector<Map::MapCase>> &map)
{
	this->_map = map;
}

std::ostream & operator<<(std::ostream & os, Map const & map)
{
	auto mymap = map.getMapCase();
	os << "Map:\n";
	for(size_t i = 0; i < mymap.size(); i++)
	{
		os << "{\n";
		for(size_t j = 0; j < mymap[i].size(); j++)
		{
			os << "\t" << mymap[i][j]._food << "\n";
			os << "\t" << mymap[i][j]._stone1 << "\n";
			os << "\t" << mymap[i][j]._stone2 << "\n";
			os << "\t" << mymap[i][j]._stone3 << "\n";
			os << "\t" << mymap[i][j]._stone4 << "\n";
			os << "\t" << mymap[i][j]._stone5 << "\n";
			os << "\t" << mymap[i][j]._stone6 << "\n";
		}
		os << "}\n";	
	}
	os << "\n";
	return os;
}