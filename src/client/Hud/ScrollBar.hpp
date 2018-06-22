//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ScrollBar.hpp
//

#ifndef ScrollBar_HPP
#define ScrollBar_HPP

#include "include.hpp"
#include <vector>

class ScrollBar
{
public:
	ScrollBar(irr::gui::IGUIScrollBar *ScrollBar, int id);
	ScrollBar();
	~ScrollBar();
	void	setPos(int pos);
	int		getPos(void) const;
	int getId() const;
private:
	int _id;
	long _idx;
	int	_pos;
	irr::gui::IGUIScrollBar *_scrollBar;	
};

#endif