//
// EPITECH PROJECT, 2018
// zappy
// File description:
// CheckBoxManager.hpp
//

#ifndef CHECKBOXMANAGER_HPP
#define CHECKBOXMANAGER_HPP

#include "include.hpp"
#include "CheckBox.hpp"
#include <iostream>
#include <vector>

class Menu;

class CheckBoxManager
{
public:
	CheckBoxManager();
	~CheckBoxManager();
	void addCheckBox(CheckBox checkBox);
	void setVisible(bool visible, int id);
	void check(bool value, int id);
	void isCheck(Menu *menu, int id);
private:
	std::vector<CheckBox> list;
};

#endif
