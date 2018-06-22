/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Math.hpp
*/

#ifndef Math_HPP
#define Math_HPP

#include "Point.hpp"

#include <cstddef>

class Math
{
public:

	Math() = delete;

	static size_t	roundUp(size_t numToRound, size_t multiple);
	static size_t	manhattanDistance(Point const & from, Point const & to);
	static int		randomNumberBetween(int min, int max);
	template <typename T>
	static T	clamp(T const & min, T const & max, T const & value)
	{
		return std::min(max, std::max(min, value));
	}

};

#endif // !Math_HPP
