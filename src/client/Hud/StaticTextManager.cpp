//
// EPITECH PROJECT, 2018
// zappy
// File description:
// StaticTextManager.cpp
//

#include "StaticTextManager.hpp"

StaticTextManager::StaticTextManager()
{
}

StaticTextManager::~StaticTextManager()
{
}

void StaticTextManager::addStaticText(StaticText txt)
{
	list.push_back(txt);
}

void StaticTextManager::setVisible(bool scale, int id)
{
	for (std::vector<StaticText>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setVisible(scale);
			return;
		}
	}
	std::cerr << "StaticTextManager::setVisible() can't find id " <<
		id << "\n";
}

void StaticTextManager::setText(const char *str, int id)
{
	for (std::vector<StaticText>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setText(str);
			return;
		}
	}
	std::cerr << "StaticTextManager::setText() can't find id " <<
		id << "\n";
}
