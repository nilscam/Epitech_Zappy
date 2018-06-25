//
// EPITECH PROJECT, 2018
// zappy
// File description:
// CheckBox.cpp
//

#include "CheckBox.hpp"
#include "Menu.hpp"

CheckBox::CheckBox(irr::gui::IGUICheckBox *ch, int id)
{
	_id = id;
	chk = ch;
}

CheckBox::~CheckBox()
{
}

int CheckBox::getId() const
{
	return _id;
}

void CheckBox::setVisible(bool visible)
{
	chk->setVisible(visible);      
}

void CheckBox::check(bool check)
{
	chk->setChecked(check);
}

void CheckBox::isCheck(Menu *menu)
{
	if (chk->isChecked() && _id == MENU_OPTIONS_CHECKBOX_MUSIC) {
		menu->_snd->setVolume(0);
	} else if (_id == MENU_OPTIONS_CHECKBOX_MUSIC) {
		menu->_snd->setVolume(100);
	} else if (chk->isChecked() && _id == MENU_OPTIONS_CHECKBOX_TABLE) {
		menu->hide_table();
	} else if (_id == MENU_OPTIONS_CHECKBOX_TABLE) {
		menu->show_table();
	} else if (chk->isChecked() && _id == MENU_OPTIONS_CHECKBOX_TIMER) {
		menu->hide_timer();
	} else if (_id == MENU_OPTIONS_CHECKBOX_TIMER) {
		menu->show_timer();
	} else if (chk->isChecked() && _id == MENU_OPTIONS_CHECKBOX_LISTBOX) {
		menu->hide_listBox();
	} else if (_id == MENU_OPTIONS_CHECKBOX_LISTBOX) {
		menu->show_listBox();
	}
}
