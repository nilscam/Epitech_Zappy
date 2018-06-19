/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Point.hpp
*/

#ifndef Point_HPP
#define Point_HPP

#include <iostream>
#include <array>

class Direction;

class Point
{
public:

	Point();
	Point(int x, int y);
	virtual ~Point() = default;
	Point(Point const & rhs) = default;
	Point(Point && rhs) = default;
	Point & operator=(Point const & rhs) = default;
	Point & operator=(Point && rhs) = default;

	bool	operator<(Point const & rhs) const noexcept;
	bool	operator>(Point const & rhs) const noexcept;
	bool	operator<=(Point const & rhs) const noexcept;
	bool	operator>=(Point const & rhs) const noexcept;
	bool	operator==(Point const & rhs) const noexcept;
	bool	operator!=(Point const & rhs) const noexcept;
	Point	operator+(Point const & rhs) const noexcept;
	Point	operator-(Point const & rhs) const noexcept;
	Point	operator*(Point const & rhs) const noexcept;
	Point	operator/(Point const & rhs) const noexcept;
	Point &	operator+=(Point const & rhs) noexcept;
	Point &	operator-=(Point const & rhs) noexcept;
	Point &	operator*=(Point const & rhs) noexcept;
	Point &	operator/=(Point const & rhs) noexcept;

	std::array<int, 2>	operator*() const noexcept;

	std::array<int, 2>	getArray() const noexcept;
	int		x(void) const noexcept;
	int		y(void) const noexcept;
	int		getX(void) const noexcept;
	int		getY(void) const noexcept;
	void	setX(int x) noexcept;
	void	setY(int y) noexcept;
	void	incX(int inc) noexcept;
	void	incY(int inc) noexcept;
	Point	moveAt(Direction const & dir) const noexcept;
	Point	moveAt(Direction const & dir, int inc) const noexcept;
	void	move(Direction const & dir) noexcept;
	void	move(Direction const & dir, int inc) noexcept;
	size_t	getLength() const noexcept;

	friend std::ostream & operator<<(std::ostream & os, Point const & point);

private:

	int		_x;
	int		_y;

};

#endif // !Point_HPP
