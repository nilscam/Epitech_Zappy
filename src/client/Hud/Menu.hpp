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
#include "SoundManager.hpp"
#include "CheckBoxManager.hpp"
#include "StaticTextManager.hpp"
#include "ListBox.hpp"
#include "Table.hpp"
#include "ScrollBar.hpp"
#include "utils.hpp"
#include "EID.hpp"
#include <iostream>
#include <memory>

class Menu
{
public:
	Menu();
	Menu(ImageManager *img, ButtonManager *btn, ServPanel *srv,
	     SoundManager *snd, StaticTextManager *txt, CheckBoxManager *bx,
	     Table *tbl, ListBox *lstBx, ScrollBar *scrllBr);
	~Menu();
	
	void server_open();
	void server_first_ok();
	void server_second_ok();
	void setVisible(int id);
	void isButtonPressed();
	void test(int id);
	void show_table();
	void hide_table();
	void show_listBox();
	void hide_listBox();
	void show_timer();
	void hide_timer();
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
	void hide_inventory();
	void show_inventory();
	void update_inventory(std::vector<std::string> str);
	std::shared_ptr<ServerHandler>	getServerHandler(void) const noexcept;
	int		getPort() const;
	bool		getExit() const;
	void	nextSkyBox();

	bool isMenuOpen;
	bool isOptionsOpen;
	bool isCreditsOpen;
	bool	isServerLaunch;
	bool	needToExit;
	int		idSkyBox;
	SoundManager *_snd;
	
private:
	Table *_tbl;
	ListBox *_lstBx;
	ScrollBar *_scrllBr;
	CheckBoxManager *_bx;
	StaticTextManager *_txt;
	ImageManager *_img;
	ButtonManager *_btn;
	ServPanel *_srv;
	bool start;
	std::shared_ptr<ServerHandler>	_serverHandler;
};

#endif
