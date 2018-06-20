//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ButtonManager.hpp
//

#ifndef BUTTONMANAGER_HPP
#define BUTTONMANAGER_HPP

#include "include.hpp"
#include "Button.hpp"
#include <vector>

class ButtonManager
{
public:
	ButtonManager();
	~ButtonManager();
	void addButton(Button button);
	void setVisible(bool visible, int id);
	void isButtonPressed();
	void setScaleImage(bool scale, int id);
	void setImage(irr::video::ITexture *text, int id);
private:
	std::vector<Button> list;
};

#endif
