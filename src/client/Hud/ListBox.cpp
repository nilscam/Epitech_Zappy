//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ListBox.cpp
//

#include "ListBox.hpp"

ListBox::ListBox(irr::gui::IGUIListBox *list, int id)
{
	_idx = 0;
	_id = id;
	_color.push_back(irr::video::SColor(255, 150, 150, 150));
	_color.push_back(irr::video::SColor(255, 200, 20, 40));
	_color.push_back(irr::video::SColor(255, 255, 0, 0));
	_color.push_back(irr::video::SColor(255, 0, 0, 255));
	_color.push_back(irr::video::SColor(255, 0, 255, 0));
	_color.push_back(irr::video::SColor(255, 204, 163, 0));
	_color.push_back(irr::video::SColor(255, 153, 102, 51));
	listBox = list;
	listBox->setAutoScrollEnabled(true);
	setHeight(20);
}

ListBox::ListBox()
{
}

ListBox::~ListBox()
{
}

void ListBox::addText(const wchar_t *text, MSGtype type)
{
	listBox->addItem(text);
	listBox->setSelected(_idx);
	setColor(type);
	_idx += 1;
}

void ListBox::setColor(MSGtype type)
{
	listBox->setItemOverrideColor(_idx, _color[type]);
}

void ListBox::setHeight(int height)
{
	listBox->setItemHeight(height);
}

void ListBox::setVisible(bool visible)
{
	listBox->setVisible(visible);
}

int ListBox::getId() const
{
	return _id;
}
