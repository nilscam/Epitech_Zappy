/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Math.cpp
*/

#include "Math.hpp"

size_t	Math::roundUp(size_t numToRound, size_t multiple)
{
	return ((numToRound + multiple - 1) / multiple) * multiple;
}

size_t	Math::manhattanDistance(Point const & from, Point const & to)
{
	int x1 = from.getX();
	int x2 = to.getX();
	int y1 = from.getY();
	int y2 = to.getY();
	int absX = x1 > x2 ? x1 - x2 : x2 - x1;
	int absY = y1 > y2 ? y1 - y2 : y2 - y1;
	return absX + absY;
}

int	Math::randomNumberBetween(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
