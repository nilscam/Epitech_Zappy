/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Direction.hpp
*/

#ifndef Direction_HPP
#define Direction_HPP

#include "ASerializable.hpp"
#include "Point.hpp"
#include "Event.hpp"

class Direction : public ASerializable
{
public:

	enum Dir_t
	{
		None = 0,
		Left = 0x1,
		Up = 0x2,
		Down = 0x4,
		Right = 0x8
	};

	Direction();
	Direction(Dir_t dir);
	Direction(Point const & from, Point const & to);
	Direction(Point const & dir);
	Direction(double degrees);
	Direction(Event event);
	virtual ~Direction() = default;
	Direction(Direction const & rhs) = default;
	Direction(Direction && rhs) = default;
	Direction & operator=(Direction const & rhs) = default;
	Direction & operator=(Direction && rhs) = default;

	Dir_t	operator*() noexcept;
	bool	operator==(Dir_t const & rhs) const noexcept;
	bool	operator!=(Dir_t const & rhs) const noexcept;
	bool	operator==(Direction const & rhs) const noexcept;
	bool	operator!=(Direction const & rhs) const noexcept;

	void			setDir(Dir_t dir) noexcept;
	/* ASerializable.hpp */
	void	serialize(Saver & saver) const override;
	void	deserialize(Loader & loader) override;

	Direction &		reverse() noexcept;
	Direction &		turnLeft() noexcept;
	Direction &		turnRight() noexcept;
	Point			move(Point const & pos) const noexcept;
	Point			move(Point const & pos, int inc) const noexcept;

	Dir_t			getDir() const noexcept;
	std::string		getRepr() const noexcept;
	Event			getEvent() const noexcept;

	friend std::ostream & operator<<(std::ostream & os, Direction const & dir);

private:

	Dir_t	dirFromPos(Point const & from, Point const & to) const noexcept;
	Dir_t	dirFromDir(Point const & dir) const noexcept;
	Dir_t	dirFromAngle(double degrees) const noexcept;
	Dir_t	dirFromEvent(Event event) const noexcept;

	Dir_t	_dir;

};

#endif // !Direction_HPP
