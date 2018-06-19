/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Point.cpp
*/

#include "Point.hpp"
#include "Direction.hpp"

#include <cmath>

Point::Point()
	:	Point(0, 0)
{}

Point::Point(int x, int y)
	:	_x(x), _y(y)
{}

void	Point::serialize(Saver & saver) const
{
	saver.save(_x);
	saver.save(_y);
}

void	Point::deserialize(Loader & loader)
{
	loader.load(_x);
	loader.load(_y);
}

std::array<int, 2>	Point::operator*() const noexcept
{
	return getArray();
}

bool	Point::operator<(Point const & rhs) const noexcept
{
	return _x * _x + _y * _y < rhs._x * rhs._x + rhs._y * rhs._y;
}

bool	Point::operator>(Point const & rhs) const noexcept
{
	return rhs < *this;
}

bool	Point::operator<=(Point const & rhs) const noexcept
{
	return !(rhs < *this);
}

bool	Point::operator>=(Point const & rhs) const noexcept
{
	return !(*this < rhs);
}

bool	Point::operator==(Point const & rhs) const noexcept
{
	return _x == rhs._x && _y == rhs._y;
}

bool	Point::operator!=(Point const & rhs) const noexcept
{
	return !(*this == rhs);
}

Point	Point::operator+(Point const & rhs) const noexcept
{
	return { _x + rhs._x, _y + rhs._y };
}

Point	Point::operator-(Point const & rhs) const noexcept
{
	return { _x - rhs._x, _y - rhs._y };
}

Point	Point::operator*(Point const & rhs) const noexcept
{
	return { _x * rhs._x, _y * rhs._y };
}

Point	Point::operator/(Point const & rhs) const noexcept
{
	int x = rhs._x == 0 ? 0 : _x / rhs._x;
	int y = rhs._y == 0 ? 0 : _y / rhs._y;
	return { x, y };
}

Point &	Point::operator+=(Point const & rhs) noexcept
{
	_x += rhs._x;
	_y += rhs._y;
	return *this;
}

Point &	Point::operator-=(Point const & rhs) noexcept
{
	_x -= rhs._x;
	_y -= rhs._y;
	return *this;
}

Point &	Point::operator*=(Point const & rhs) noexcept
{
	_x *= rhs._x;
	_y *= rhs._y;
	return *this;
}

Point &	Point::operator/=(Point const & rhs) noexcept
{
	_x /= rhs._x;
	_y /= rhs._y;
	return *this;
}

std::array<int, 2>	Point::getArray() const noexcept
{
	return { _x, _y };
}

int		Point::x(void) const noexcept
{
	return getX();
}

int		Point::y(void) const noexcept
{
	return getY();
}

int		Point::getX(void) const noexcept
{
	return _x;
}

int		Point::getY(void) const noexcept
{
	return _y;
}

void	Point::setX(int x) noexcept
{
	_x = x;
}

void	Point::setY(int y) noexcept
{
	_y = y;
}

void	Point::incX(int inc) noexcept
{
	_x += inc;
}

void	Point::incY(int inc) noexcept
{
	_y += inc;
}

void	Point::move(Direction const & dir) noexcept
{
	move(dir, 1);
}

void	Point::move(Direction const & dir, int inc) noexcept
{
	*this = dir.move(*this, inc);
}

Point	Point::moveAt(Direction const & dir) const noexcept
{
	return moveAt(dir, 1);
}

Point	Point::moveAt(Direction const & dir, int inc) const noexcept
{
	return dir.move(*this, inc);
}

std::ostream & operator<<(std::ostream & os, Point const & point)
{
	os << "{ " << point.x() << " ; " <<  point.y() << " }";
	return os;
}

size_t	Point::getLength() const noexcept
{
	return std::sqrt(_x * _x + _y * _y);
}
