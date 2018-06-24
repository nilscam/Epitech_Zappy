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

class Menu;

class Button
{
public:
	enum Action {
		NONE,
		TEST,		
		MENU_CANCEL,
		MENU_OPEN,
		CREDITS_CANCEL,
		CREDITS_OPEN,
		OPTIONS_CANCEL,
		OPTIONS_OPEN,
		EXIT,
		OPEN_CLIENT,
		CLOSE_CLIENT,
		ADD_CLIENT,
		SRV_FIRST_OK,
		SRV_SECOND_OK,
		ADD_TEAM1,
		ADD_TEAM2,
		ADD_TEAM3,
		ADD_TEAM4,
		LAUNCH_GAME,
		NEXT_SONG,
		CHANGE_SKYBOX
	};
	Button(irr::gui::IGUIButton *butt, Button::Action action, int id);
	~Button();
	void setVisible(bool visible);
	void setImage(irr::video::ITexture *text);
	void setScaleImage(bool scale);
	void pressed(Menu *menu);
	void setText(const wchar_t *str);
	int getId()  const;
private:
	Button::Action _action;
	irr::gui::IGUIButton *button;
	int _id;
	bool _active;
};

#endif
