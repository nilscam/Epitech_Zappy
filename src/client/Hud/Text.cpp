//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Text.cpp
//

#include "Text.hpp"

Text::Text(irr::gui::IGUIStaticText *list, int id)
{
	_idx = 0;
	_id = id;
	_Text = list;
}

Text::Text()
{
}

Text::~Text()
{
}

void	Text::setPos(int pos)
{
	_Text->setPos(pos);
}
int		Text::getPos(void) const
{
	auto pos = _Text->getPos();
	return pos;
}

void	Text::setText(const std::string & str)
{
	const size_t cSize = strlen(str.c_str()) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, str.c_str(), cSize);
	_Text->setText(wc);
}

int Text::getId() const
{
	return _id;
}
