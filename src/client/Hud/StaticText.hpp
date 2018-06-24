//
// EPITECH PROJECT, 2018
// zappy
// File description:
// StaticText.hpp
//

#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "include.hpp"
#include "utils.hpp"

class StaticText
{
public:
	StaticText(irr::gui::IGUIStaticText *txt, int id);
	~StaticText();
	int getId() const;
	void setText(const char *str);
	void setVisible(bool visible);
private:
	int _id;
	irr::gui::IGUIStaticText *txt;
};

#endif
