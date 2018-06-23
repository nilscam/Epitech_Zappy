//
// EPITECH PROJECT, 2018
// zappy
// File description:
// EditBox.cpp
//

#include "EditBox.hpp"

EditBox::EditBox(irr::gui::IGUIEditBox *edt, irr::gui::IGUIStaticText *txt,
		 int id)
{
	edit = edt;
	text = txt;
	_id = id;
}

EditBox::~EditBox()
{
}

void EditBox::setVisible(bool visible)
{
	edit->setVisible(visible);
	text->setVisible(visible);
}

const wchar_t *EditBox::getText() const
{
	return edit->getText();
}

int EditBox::getId() const
{
	return _id;
}
