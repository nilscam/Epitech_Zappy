//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Button.cpp
//

#include "Button.hpp"
#include "Menu.hpp"

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

void Button::pressed(Menu *menu)
{
	bool isPressed = button->isPressed();
	if (isPressed && !_active) {
		menu->_snd->playSound(SoundManager::Sound::MENU_OK);
		_active = true;
		if (_action == TEST)
			menu->test(_id);
		if (_action == MENU_CANCEL)
			menu->menu_cancel();
		if (_action == MENU_OPEN)
			menu->menu_open();
		if (_action == CREDITS_CANCEL)
			menu->credits_cancel();
		if (_action == CREDITS_OPEN)
			menu->credits_open();
		if (_action == OPTIONS_CANCEL)
			menu->options_cancel();
		if (_action == OPTIONS_OPEN)
			menu->options_open();
		if (_action == EXIT)
			menu->exit();
		if (_action == SRV_FIRST_OK)
			menu->server_first_ok();
		if (_action == SRV_SECOND_OK)
			menu->server_second_ok();
		if (_action == ADD_TEAM1)
			menu->add_team1();
		if (_action == ADD_TEAM2)
			menu->add_team2();
		if (_action == ADD_TEAM3)
			menu->add_team3();
		if (_action == ADD_TEAM4)
			menu->add_team4();
		if (_action == LAUNCH_GAME)
			menu->launch_game();
		if (_action == NEXT_SONG)
			menu->next_song();
		if (_action == CHANGE_SKYBOX)
			menu->nextSkyBox();
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

void Button::setText(const wchar_t *str)
{
	button->setText(str);
}
