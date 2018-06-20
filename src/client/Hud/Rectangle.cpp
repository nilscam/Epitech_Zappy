//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Rectangle.cpp
//

#include "Rectangle.hpp"

Rectangle::Rectangle(int x, int y, int x2, int y2)
{
	rect = irr::core::rect<irr::s32>(x, y, x2, y2);
	_x = x;
	_x2 = x2;
	_y = y;
	_y2 = y2;
}

Rectangle::~Rectangle()
{
}

irr::core::rect<irr::s32> Rectangle::get() const
{
	return rect;
}

int Rectangle::getX() const
{
	return _x;
}

int Rectangle::getY() const
{
	return _y;
}

int Rectangle::getY2() const
{
	return _y2;
}

int Rectangle::getX2() const
{
	return _x2;
}
