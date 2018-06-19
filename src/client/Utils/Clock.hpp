/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Clock.hpp
*/

#ifndef Clock_HPP
#define Clock_HPP

#include <chrono>

class Clock
{
public:

	Clock();
	virtual ~Clock() = default;
	Clock(Clock const & rhs) = default;
	Clock(Clock && rhs) = default;
	Clock & operator=(Clock const & rhs) = default;
	Clock & operator=(Clock && rhs) = default;

	using Clock_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using Time_t = long long;

	void		mark() noexcept;
	Time_t		timeSinceMark() const noexcept;

private:

	Clock_t		_clock;

};

#endif // !Clock_HPP
