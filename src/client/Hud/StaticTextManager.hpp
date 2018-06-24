//
// EPITECH PROJECT, 2018
// zappy
// File description:
// StaticTextManager.hpp
//

#ifndef STATICTEXTMANAGER_HPP
#define STATICTEXTMANAGER_HPP

#include "include.hpp"
#include "StaticText.hpp"
#include <iostream>
#include <vector>

class StaticTextManager
{
public:
	StaticTextManager();
	~StaticTextManager();
	void addStaticText(StaticText text);
	void setVisible(bool visible, int id);
	void setText(const char *str, int id);
private:
	std::vector<StaticText> list;
};



#endif
