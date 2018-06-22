//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Rectangle.hpp
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "include.hpp"

class Rectangle
{
public:
	Rectangle(int, int, int, int);
	~Rectangle();
	irr::core::rect<irr::s32>get() const;
	int getX() const;
	int getX2() const;
	int getY() const;
	int getY2() const; 
private:
	int _x;
	int _x2;
	int _y;
	int _y2;
	irr::core::rect<irr::s32> rect;
};

#endif

