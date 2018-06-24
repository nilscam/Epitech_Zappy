//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Menu.hpp
//


#ifndef MENU_HPP
#define MENU_HPP

#include "include.hpp"
#include "ImageManager.hpp"
#include "ButtonManager.hpp"
#include "ServPanel.hpp"
#include "ServerHandler.hpp"
#include "utils.hpp"
#include "EID.hpp"
#include <iostream>
#include <memory>

class Menu
{
public:
	Menu();
	Menu(ImageManager *img, ButtonManager *btn, ServPanel *srv);
	~Menu();
	void server_open();
	void server_first_ok();
	void server_second_ok();
	void setVisible(int id);
	void isButtonPressed();
	void test(int id);
	void menu_cancel();
	void menu_open();
	void options_cancel();
	void options_open();
	void credits_open();
	void credits_cancel();
	void add_team1();
	void add_team2();
	void add_team3();
	void add_team4();
	void launch_game();
	void next_song();
	void exit();
	int		getPort() const;
	bool		getExit() const;
	bool isMenuOpen;
	bool isOptionsOpen;
	bool isCreditsOpen;
	bool	isServerLaunch;
	bool	needToExit;
private:
	ImageManager *_img;
	ButtonManager *_btn;
	ServPanel *_srv;
	std::shared_ptr<ServerHandler>	_serverHandler;
};

#endif