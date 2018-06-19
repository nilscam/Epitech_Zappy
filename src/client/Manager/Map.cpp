/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map.cpp
*/

#include "Map.hpp"

void	Map::createMap(int width, int height)
{
	std::vector<MapSqt>	v;
	for(int i = 0; i < width; i++) {
		v.push_back(None);
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
			MapSqt items = None;
			if (infos[i + 3][0] == '0') {
				items |= Food;
			} if (infos[i + 4][0] == '0') {
				items |= Stone1;
			} if (infos[i + 5][0] == '0') {
				items |= Stone2;
			} if (infos[i + 6][0] == '0') {
				items |= Stone3;
			} if (infos[i + 7][0] == '0') {
				items |= Stone4;
			} if (infos[i + 8][0] == '0') {
				items |= Stone5;
			} if (infos[i + 9][0] == '0') {
				items |= Stone6;
			}
			_map[point.y()][point.x()] = items;
		}
		i += 10;
	}
}

std::vector<Point>	Map::getSqtPoints(MapSqt sqt) const
{
	std::vector<Point> points;
	int y = 0;
	for (auto const & l : this->map) {
		int x = 0;
		for (auto const & c : l) {
			if (c & sqt) {
				points.push_back({ x, y });
			}
			++x;
		}
		++y;
	}
	return points;
}

Map::MapSqt	Map::getSqt(Point const & pos) const
{
	const MapSqt DEFAULT_SQT = HardWall;
	int x = pos.getX();
	int y = pos.getY();

	if (y < 0 || y >= this->map.size())
		return DEFAULT_SQT;
	else if (x < 0 || x >= this->map[y].size())
		return DEFAULT_SQT;
	return this->map[y][x];
}

std::vector<std::vector<Map::MapSqt>>	Map::getMapSqt() const
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

Map::Map(const std::vector<std::vector<Map::MapSqt>> &map)
{
	this->map = map;
}

std::ostream & operator<<(std::ostream & os, Map const & map)
{
	auto sqtPoints = map.getMapSqt();
	for (int y = 0; y < sqtPoints.size(); ++y)
	{
		for (int x = 0; x < sqtPoints[y].size(); ++x)
		{
			char repr = ' ';
			if (sqtPoints[y][x] & Map::SoftWall)
				repr = '.';
			else if (sqtPoints[y][x] & Map::HardWall)
				repr = '#';
			os << (char)repr;
		}
		os << std::endl;
	}
	return os;
}