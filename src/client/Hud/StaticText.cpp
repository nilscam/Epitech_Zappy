//
// EPITECH PROJECT, 2018
// zappy
// File description:
// StaticText.cp
//

#include "StaticText.hpp"

StaticText::StaticText(irr::gui::IGUIStaticText *tx, int id)
{
	_id = id;
	txt = tx;	
}

StaticText::~StaticText()
{
}


int StaticText::getId() const
{
	return _id;
}

void StaticText::setText(const char *str)
{
	const wchar_t *text = char_to_wchar(str);
	txt->setText(text);
}

void StaticText::setVisible(bool visible)
{
	txt->setVisible(visible);
}

