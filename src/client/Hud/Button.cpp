//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Button.cpp
//

#include "Button.hpp"

Button::Button(irr::gui::IGUIButton *butt, Button::Action action, int id)
{
	button = butt;
	_action = action;
	_id = id;
	_active = false;
}

Button::~Button()
{
}

void Button::pressed()
{
	bool isPressed = button->isPressed();
	if (isPressed && !_active) {
		_active = true;
		if (_action == TEST)
			std::cout << "Element {" << _id << "} is testing\n";
	       
	} else if (!isPressed && _active) {
		_active = false;
	}
}

void Button::setVisible(bool visible)
{
	button->setVisible(visible);
}

int Button::getId() const
{
	return _id;
}

void Button::setImage(irr::video::ITexture *text)
{
	button->setImage(text);
	button->setUseAlphaChannel(true);
}

void Button::setScaleImage(bool scale)
{
	button->setScaleImage(scale);
}
