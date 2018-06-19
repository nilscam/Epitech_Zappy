/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Direction.cpp
*/

#include "Direction.hpp"
#include <cmath>

Direction::Direction()
	:	Direction(None)
{}

Direction::Direction(Dir_t dir)
	:	_dir(dir)
{}

Direction::Direction(Point const & from, Point const & to)
	:	_dir(dirFromPos(from, to))
{}

Direction::Direction(Point const & dir)
	:	_dir(dirFromDir(dir))
{}

Direction::Direction(double degrees)
	:	_dir(dirFromAngle(degrees))
{}

Direction::Direction(Event event)
	:	_dir(dirFromEvent(event))
{}

Direction::Dir_t	Direction::operator*() noexcept
{
	return getDir();
}

bool	Direction::operator==(Dir_t const & rhs) const noexcept
{
	return _dir == rhs;
}

bool	Direction::operator!=(Dir_t const & rhs) const noexcept
{
	return !(*this == rhs);
}

bool	Direction::operator==(Direction const & rhs) const noexcept
{
	return _dir == rhs._dir;
}

bool	Direction::operator!=(Direction const & rhs) const noexcept
{
	return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & os, Direction const & dir)
{
	os << dir.getRepr();
	return os;
}

void	Direction::setDir(Direction::Dir_t dir) noexcept
{
	_dir = dir;
}

void	Direction::serialize(Saver & saver) const
{
	saver.save(_dir);
}

void	Direction::deserialize(Loader & loader)
{
	loader.load(_dir);
}

Direction &	Direction::reverse() noexcept
{
	if (_dir == Left)
		_dir = Right;
	else if (_dir == Right)
		_dir = Left;
	else if (_dir == Up)
		_dir = Down;
	else if (_dir == Down)
		_dir = Up;
	return *this;
}

Direction &	Direction::turnLeft() noexcept
{
	if (_dir == Left)
		_dir = Down;
	else if (_dir == Right)
		_dir = Up;
	else if (_dir == Up)
		_dir = Left;
	else if (_dir == Down)
		_dir = Right;
	return *this;
}

Direction &	Direction::turnRight() noexcept
{
	if (_dir == Left)
		_dir = Up;
	else if (_dir == Right)
		_dir = Down;
	else if (_dir == Up)
		_dir = Right;
	else if (_dir == Down)
		_dir = Left;
	return *this;
}

Point	Direction::move(Point const & pos) const noexcept
{
	return move(pos, 1);
}

Point	Direction::move(Point const & pos, int inc) const noexcept
{
	Point newPos = pos;
	if (_dir == Left)
		newPos.incX(-inc);
	else if (_dir == Right)
		newPos.incX(inc);
	else if (_dir == Up)
		newPos.incY(-inc);
	else if (_dir == Down)
		newPos.incY(inc);
	return newPos;
}

Direction::Dir_t	Direction::getDir() const noexcept
{
	return _dir;
}

std::string	Direction::getRepr() const noexcept
{
	return _dir == Left ? "Left"
			: _dir == Right ? "Right"
			: _dir == Up ? "Up"
			: _dir == Down ? "Down"
			: "None";
}

Direction::Dir_t	Direction::dirFromPos(Point const & from, Point const & to) const noexcept
{
	Point dir { to.getX() - from.getX(), to.getY() - from.getY() };
	return dirFromDir(dir);
	
}

Direction::Dir_t	Direction::dirFromDir(Point const & dir) const noexcept
{
	if (dir.getX() == 1 && dir.getY() == 0)
		return Right;
	else if (dir.getX() == -1 && dir.getY() == 0)
		return Left;
	else if (dir.getX() == 0 && dir.getY() == 1)
		return Down;
	else if (dir.getX() == 0 && dir.getY() == -1)
		return Up;
	double degrees = atan2(dir.getX(), dir.getY()) * 180.0 / M_PI;
	return dirFromAngle(degrees);
}

Direction::Dir_t	Direction::dirFromAngle(double d) const noexcept
{
	if (d <= -45 && d >= -135)
		return Left;
	else if (d >= 45 && d <= 135)
		return Right;
	else if (d >= 135 && d <= 225)
		return Up;
	return Down;
}

Direction::Dir_t	Direction::dirFromEvent(Event event) const noexcept
{
	if (event & Event::Left)
		return Dir_t::Left;
	else if (event & Event::Right)
		return Dir_t::Right;
	else if (event & Event::Up)
		return Dir_t::Up;
	else if (event & Event::Down)
		return Dir_t::Down;
	return None;
}

Event	Direction::getEvent() const noexcept
{
	if (_dir == Dir_t::Left)
		return Event::Left;
	else if (_dir == Dir_t::Right)
		return Event::Right;
	else if (_dir == Dir_t::Up)
		return Event::Up;
	else if (_dir == Dir_t::Down)
		return Event::Down;
	return Event::None;
}
