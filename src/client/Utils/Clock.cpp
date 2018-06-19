/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Clock.cpp
*/

#include "Clock.hpp"

Clock::Clock()
	:	_clock(std::chrono::high_resolution_clock::now())
{}

void	Clock::mark() noexcept
{
	_clock = std::chrono::high_resolution_clock::now();
}

Clock::Time_t	Clock::timeSinceMark() const noexcept
{
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - _clock);
	return duration.count();
}
