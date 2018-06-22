//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Button.hpp
//

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include "include.hpp"
#include "Rectangle.hpp"
#include <string>

class Button
{
public:
	enum Action {
		NONE,
		TEST
	};
	Button(irr::gui::IGUIButton *butt, Button::Action action, int id);
	~Button();
	void setVisible(bool visible);
	void setImage(irr::video::ITexture *text);
	void setScaleImage(bool scale);
	void pressed();       
	int getId()  const;
private:
	Button::Action _action;
	irr::gui::IGUIButton *button;
	int _id;
	bool _active;
};

#endif
