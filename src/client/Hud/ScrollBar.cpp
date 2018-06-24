//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ScrollBar.cpp
//

#include "ScrollBar.hpp"

ScrollBar::ScrollBar(irr::gui::IGUIScrollBar *list, int id)
{
	_idx = 0;
	_id = id;
	_scrollBar = list;
}

ScrollBar::ScrollBar()
{
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::setVisible(bool visible)
{
	_scrollBar->setVisible(visible);
}

void	ScrollBar::setPos(int pos)
{
	_scrollBar->setPos(pos);
}
int		ScrollBar::getPos(void) const
{
	auto pos = _scrollBar->getPos();
	return pos;
}

int ScrollBar::getId() const
{
	return _id;
}
