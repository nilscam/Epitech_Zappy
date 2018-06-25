//
// EPITECH PROJECT, 2018
// zappy
// File description:
// CheckBoxManager.cpp
//

#include "CheckBoxManager.hpp"
#include "Menu.hpp"

CheckBoxManager::CheckBoxManager()
{
}

CheckBoxManager::~CheckBoxManager()
{
}

void CheckBoxManager::addCheckBox(CheckBox chk)
{
	list.push_back(chk);
}

void CheckBoxManager::setVisible(bool visible, int id)
{
	for (std::vector<CheckBox>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setVisible(visible);
			return;
		}
	}
	std::cerr << "CheckBoxManager::setVisible() can't find id " <<
		id << "\n";
}

void CheckBoxManager::isCheck(Menu *menu, int id)
{
	for (std::vector<CheckBox>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).isCheck(menu);
			return;
		}
	}
	std::cerr << "CheckBoxManager::isCheck() can't find id " <<
		id << "\n";
}

void CheckBoxManager::check(bool checked, int id)
{
	for (std::vector<CheckBox>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).check(checked);
			return;
		}
	}
	std::cerr << "CheckBoxManager::check() can't find id " <<
		id << "\n";
}
