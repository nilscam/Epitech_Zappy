//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Text.hpp
//

#ifndef Text_HPP
#define Text_HPP

#include "include.hpp"
#include <vector>

class Text
{
public:
	Text(irr::gui::IGUIStaticText *Text, int id);
	Text();
	~Text();
	void	setPos(int pos);
	int		getPos(void) const;
	void	setText(const std::string & str);
	int		getId() const;
private:
	int _id;
	long _idx;
	int	_pos;
	irr::gui::IGUIStaticText *_Text;	
};

#endif