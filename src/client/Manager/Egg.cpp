/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Egg.cpp
*/

#include "Egg.hpp"

Egg::Egg(Point pos,int idxPlayerFrom)
	:	_pos(pos)
	,	_idxPlayerFrom(idxPlayerFrom)
{}

Point		Egg::getPos(void) const
{ return _pos; }
int			Egg::getIdxPlayerFrom(void) const
{ return _idxPlayerFrom; }

void		Egg::setPos(Point const & pos)
{ _pos = pos; }
void		Egg::setIdxPlayerFrom(int idxPlayerFrom)
{ _idxPlayerFrom = idxPlayerFrom; }