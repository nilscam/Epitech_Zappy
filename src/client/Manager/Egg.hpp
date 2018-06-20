/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Egg.hpp
*/

#ifndef Egg_HPP
#define Egg_HPP

#include "Point.hpp"

class Egg
{
public:

	Egg(
		Point pos,
		int idxPlayerFrom,
	);
	virtual ~Egg() = default;
	Egg(Egg const & rhs) = default;
	Egg(Egg && rhs) = default;
	Egg & operator=(Egg const & rhs) = default;
	Egg & operator=(Egg && rhs) = default;

	Point		getPos(void) const;
	int			getIdxPlayerFrom(void) const;

	void		setPos(Point const & pos);
	void		setIdxPlayerFrom(int idxPlayerFrom);

private:
	Point		_pos;
	int			_idxPlayerFrom;
};

#endif // !Egg_HPP