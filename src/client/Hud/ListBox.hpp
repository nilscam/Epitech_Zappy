//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ListBox.hpp
//

#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "include.hpp"
#include <vector>

class ListBox
{
public:
	enum MSGtype {
		DEFAULT,
		SYSTEM,
		RED_TEAM,
		BLUE_TEAM,
		GREEN_TEAM,
		YELLOW_TEAM,
		OTHER_TEAM
	};
	ListBox(irr::gui::IGUIListBox *listBox, int id);
	ListBox();
	~ListBox();
	void addText(const wchar_t *text, MSGtype type = DEFAULT);
	void setColor(MSGtype type);
	void setHeight(int height);
	void setVisible(bool visible);
	int getId() const;
private:
	int _id;
	long _idx;
	std::vector<irr::video::SColor> _color;
	irr::gui::IGUIListBox *listBox;	
};

#endif
