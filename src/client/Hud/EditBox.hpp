//
// EPITECH PROJECT, 2018
// zappy
// File description:
// EditBox.hpp
//

#ifndef EDITBOX_HPP
#define EDITBOX_HPP

#include "include.hpp"
#include "Rectangle.hpp"

class EditBox
{
public:
	enum ID {
		PORT = 200,
		WIDTH,
		HEIGHT,
		NAME1,
		NAME2,
		NAME3,
		NAME4,
		CLIENT,
		FREQ,
		TEAM
	};
	EditBox(irr::gui::IGUIEditBox *edt, irr::gui::IGUIStaticText *txt,
		int id);
	~EditBox();
	void setVisible(bool visible);
	const wchar_t *getText() const;
	int getId() const;
private:
	int _id;
	irr::gui::IGUIEditBox *edit;
	irr::gui::IGUIStaticText *text;
};

#endif
