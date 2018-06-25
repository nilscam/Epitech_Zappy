//
// EPITECH PROJECT, 2018
// zappy
// File description:
// CheckBox.hpp
//

#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "include.hpp"

class Menu;

class CheckBox
{
public:
	CheckBox(irr::gui::IGUICheckBox *chk, int id);
	~CheckBox();
	int getId() const;
	void setVisible(bool visible);
	void check(bool check);
	void isCheck(Menu *menu);
private:
	int _id;
	irr::gui::IGUICheckBox *chk;
};

#endif
