//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Menu.cpp
//

#include "Menu.hpp"

Menu::Menu()
{
}

Menu::Menu(ImageManager *img, ButtonManager *btn, ServPanel *srv,
	   SoundManager *snd, StaticTextManager *txt)
{
	_img = img;
	_btn = btn;
	_srv = srv;
	_snd = snd;
	_txt = txt;
	isMenuOpen = false;
	isOptionsOpen = false;
	isCreditsOpen = false;
	isServerLaunch = false;
	needToExit = false;
	idSkyBox = 0;
	_serverHandler = nullptr;
}

Menu::~Menu()
{
}

void Menu::isButtonPressed()
{
	_btn->isButtonPressed(this);
}

void Menu::test(int id)
{
	std::cout << "Button " << id << " is testing\n";
}

void Menu::menu_open()
{
	/* FOR CYRIL 
	show_inventory();
	hide_inventory();
	update_inventory({"12", "13", "20", "31", "42", "20", "12"}); */

	if (!isMenuOpen && !isOptionsOpen && !isCreditsOpen) {
		isMenuOpen = true;
		_btn->setVisible(true, MENU_BTN_OPTIONS);
		_btn->setVisible(true, MENU_BTN_CREDITS);
		_btn->setVisible(true, MENU_BTN_EXIT);
		_btn->setVisible(true, MENU_BTN_CANCEL_MENU);
		_img->setVisible(true, MENU_PANEL);
		_img->setVisible(true, MENU_HEADER);
		_img->setVisible(true, MENU_MENU_TEXT);		
	} else {
		options_cancel();
		credits_cancel();
		menu_cancel();
	}
	std::cout << "Menu open\n";
}

void Menu::menu_cancel()
{
	if (isMenuOpen && !isOptionsOpen && !isCreditsOpen) {
		isMenuOpen = false;
		_btn->setVisible(false, MENU_BTN_OPTIONS);
		_btn->setVisible(false, MENU_BTN_CREDITS);
		_btn->setVisible(false, MENU_BTN_EXIT);
		_btn->setVisible(false, MENU_BTN_CANCEL_MENU);
		_img->setVisible(false, MENU_PANEL);
		_img->setVisible(false, MENU_HEADER);
		_img->setVisible(false, MENU_MENU_TEXT);
	}
	std::cout << "Menu cancel\n";
}

void Menu::options_cancel()
{
	if (isMenuOpen && isOptionsOpen && !isCreditsOpen) {
		isOptionsOpen = false;
		_btn->setVisible(false, MENU_BTN_CANCEL_OPTIONS);
		_btn->setVisible(true, MENU_BTN_OPTIONS);
		_btn->setVisible(true, MENU_BTN_CREDITS);
		_btn->setVisible(true, MENU_BTN_EXIT);
		_btn->setVisible(true, MENU_BTN_CANCEL_MENU);
		_img->setVisible(false, MENU_OPTIONS_TEXT);
		_img->setVisible(true, MENU_MENU_TEXT);
	}
	std::cout << "Options cancel\n";
}

void Menu::options_open()
{
	if (isMenuOpen && !isOptionsOpen && !isCreditsOpen) {
		isOptionsOpen = true;
		_btn->setVisible(false, MENU_BTN_OPTIONS);
		_btn->setVisible(false, MENU_BTN_CREDITS);
		_btn->setVisible(false, MENU_BTN_EXIT);
		_btn->setVisible(false, MENU_BTN_CANCEL_MENU);
		_btn->setVisible(true, MENU_BTN_CANCEL_OPTIONS);
		_img->setVisible(false, MENU_MENU_TEXT);
		_img->setVisible(true, MENU_OPTIONS_TEXT);	
	}
	std::cout << "Options open\n";
}

void Menu::credits_cancel()	
{
	if (isMenuOpen && !isOptionsOpen && isCreditsOpen) {
		isCreditsOpen = false;
		_btn->setVisible(false, MENU_BTN_CANCEL_CREDITS);
		_btn->setVisible(true, MENU_BTN_OPTIONS);
		_btn->setVisible(true, MENU_BTN_CREDITS);
		_btn->setVisible(true, MENU_BTN_EXIT);
		_btn->setVisible(true, MENU_BTN_CANCEL_MENU);
		_img->setVisible(false, MENU_CREDITS_TEXT);
		_img->setVisible(true, MENU_MENU_TEXT);
	}
	std::cout << "Credits cancel\n";
}

void Menu::credits_open()
{
	if (isMenuOpen && !isOptionsOpen && !isCreditsOpen) {
		isCreditsOpen = true;
		_btn->setVisible(false, MENU_BTN_OPTIONS);
		_btn->setVisible(false, MENU_BTN_CREDITS);
		_btn->setVisible(false, MENU_BTN_EXIT);
		_btn->setVisible(false, MENU_BTN_CANCEL_MENU);
		_btn->setVisible(true, MENU_BTN_CANCEL_CREDITS);
		_img->setVisible(false, MENU_MENU_TEXT);
		_img->setVisible(true, MENU_CREDITS_TEXT);	
	}
	std::cout << "Credits open\n";
}

void Menu::server_open()
{
	isMenuOpen = false;
	isOptionsOpen = false;
	isCreditsOpen = false;
	isServerLaunch = false;
	_btn->setVisible(false, ADD_TEAM1);
	_btn->setVisible(false, ADD_TEAM2);
	_btn->setVisible(false, ADD_TEAM3);
	_btn->setVisible(false, ADD_TEAM4);
	_btn->setVisible(false, LAUNCH_GAME);

	_img->setVisible(true, MENU_SRV_PANEL);
	_btn->setVisible(true, SRV_FIRST_OK);
	_srv->setVisible(true, EditBox::PORT);
	_srv->setVisible(true, EditBox::WIDTH);
	_srv->setVisible(true, EditBox::HEIGHT);
	_srv->setVisible(true, EditBox::CLIENT);
	_srv->setVisible(true, EditBox::FREQ);
	_srv->setVisible(true, EditBox::TEAM);
}

void Menu::server_first_ok()
{
	_btn->setVisible(false, SRV_FIRST_OK);
	_srv->setVisible(false, EditBox::PORT);
	_srv->setVisible(false, EditBox::WIDTH);
	_srv->setVisible(false, EditBox::HEIGHT);
	_srv->setVisible(false, EditBox::CLIENT);
	_srv->setVisible(false, EditBox::FREQ);
	_srv->setVisible(false, EditBox::TEAM);

	_srv->setString(EditBox::PORT);
	_srv->setString(EditBox::WIDTH);
	_srv->setString(EditBox::HEIGHT);
	_srv->setString(EditBox::CLIENT);
	_srv->setString(EditBox::FREQ);
	_srv->setString(EditBox::TEAM);
		
	std::wcout << "PORT : [" << _srv->port << "]\n";
	std::wcout << "WIDTH : [" << _srv->width << "]\n";
	std::wcout << "HEIGHT : [" << _srv->height << "]\n";
	std::wcout << "CLIENT : [" << _srv->client << "]\n";
	std::wcout << "FREQ : [" << _srv->freq << "]\n";
	std::wcout << "TEAM : [" << _srv->team << "]\n";

	_srv->srvClient->setNbTeam(_srv->team);
	_btn->setVisible(true, SRV_SECOND_OK);
	_srv->setVisible(true, EditBox::NAME1);
	if (_srv->srvClient->getNbTeam() >= 2)
		_srv->setVisible(true, EditBox::NAME2);
	if (_srv->srvClient->getNbTeam() >= 3)
		_srv->setVisible(true, EditBox::NAME3);
	if (_srv->srvClient->getNbTeam() >= 4)
		_srv->setVisible(true, EditBox::NAME4);
}

void Menu::server_second_ok()
{
	_srv->setString(EditBox::NAME1);
	if (_srv->srvClient->getNbTeam() >= 2) {
		_srv->setString(EditBox::NAME2);
	}
	if (_srv->srvClient->getNbTeam() >= 3) {
		_srv->setString(EditBox::NAME3);
	}
	if (_srv->srvClient->getNbTeam() >= 4) {
		_srv->setString(EditBox::NAME4);
	}
	_btn->setVisible(false, SRV_SECOND_OK);
	_img->setVisible(false, MENU_SRV_PANEL);
	_srv->setVisible(false, EditBox::NAME1);
	_srv->setVisible(false, EditBox::NAME2);
	_srv->setVisible(false, EditBox::NAME3);
	_srv->setVisible(false, EditBox::NAME4);	

	
	_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM1),
		      ADD_TEAM1);
	if (_srv->srvClient->getNbTeam() >= 2) {
		_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM2),
			      ADD_TEAM2);
	}
	if (_srv->srvClient->getNbTeam() >= 3) {
		_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM3),
			      ADD_TEAM3);		
	}
	if (_srv->srvClient->getNbTeam() >= 4) {
		_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM4),
			      ADD_TEAM4);
	}

	_serverHandler = std::make_shared<ServerHandler>();
	auto port = atoi(wchar_to_string(_srv->port).c_str());
	auto width = atoi(wchar_to_string(_srv->width).c_str());
	auto height = atoi(wchar_to_string(_srv->height).c_str());
	auto client = atoi(wchar_to_string(_srv->client).c_str());
	auto freq = atoi(wchar_to_string(_srv->freq).c_str());
	auto vec = _srv->srvClient->getVectorTeam();
	std::cout << "Starting server to port " << port << std::endl;
	bool started = _serverHandler->startServer(width, height, port, vec, client, freq);
	if (!started)
	{
		std::cout << "Failed to start server" << std::endl;
		server_open();
	}
	else
	{
		std::cout << "Server listening to port " << port << std::endl;
		isServerLaunch = true;
		_btn->setVisible(true, LAUNCH_GAME);		
		_btn->setVisible(true, ADD_TEAM1);
		if (_srv->srvClient->getNbTeam() >= 2) {
			_btn->setVisible(true, ADD_TEAM2);
		}
		if (_srv->srvClient->getNbTeam() >= 3) {
			_btn->setVisible(true, ADD_TEAM3);
		}
		if (_srv->srvClient->getNbTeam() >= 4) {
			_btn->setVisible(true, ADD_TEAM4);
		}
	}
	/* EXECUTE SERVER */
}

void Menu::add_team1()
{
	_srv->srvClient->addPlayer(SrvClient::TEAM1);
	_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM1),
		      ADD_TEAM1);
}

void Menu::add_team2()
{
	_srv->srvClient->addPlayer(SrvClient::TEAM2);
	_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM2),
		      ADD_TEAM2);
}

void Menu::add_team3()
{
	_srv->srvClient->addPlayer(SrvClient::TEAM3);
	_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM3),
		      ADD_TEAM3);
}

void Menu::add_team4()
{
	_srv->srvClient->addPlayer(SrvClient::TEAM4);		
	_btn->setText(_srv->srvClient->updateClient(SrvClient::TEAM4),
		      ADD_TEAM4);
}

void Menu::hide_inventory()
{
	_img->setVisible(false, INVENTORY_PANEL);
	_img->setVisible(false, INV_IMG_1);
	_img->setVisible(false, INV_IMG_2);
	_img->setVisible(false, INV_IMG_3);
	_img->setVisible(false, INV_IMG_4);
	_img->setVisible(false, INV_IMG_5);
	_img->setVisible(false, INV_IMG_6);
	_img->setVisible(false, INV_IMG_7);
	_txt->setVisible(false, INV_VALUE_1);
	_txt->setVisible(false, INV_VALUE_2);
	_txt->setVisible(false, INV_VALUE_3);
	_txt->setVisible(false, INV_VALUE_4);
	_txt->setVisible(false, INV_VALUE_5);
	_txt->setVisible(false, INV_VALUE_6);
	_txt->setVisible(false, INV_VALUE_7);
}

void Menu::show_inventory()
{
	_img->setVisible(true, INVENTORY_PANEL);
	_img->setVisible(true, INV_IMG_1);
	_img->setVisible(true, INV_IMG_2);
	_img->setVisible(true, INV_IMG_3);
	_img->setVisible(true, INV_IMG_4);
	_img->setVisible(true, INV_IMG_5);
	_img->setVisible(true, INV_IMG_6);
	_img->setVisible(true, INV_IMG_7);
	_txt->setVisible(true, INV_VALUE_1);
	_txt->setVisible(true, INV_VALUE_2);
	_txt->setVisible(true, INV_VALUE_3);
	_txt->setVisible(true, INV_VALUE_4);
	_txt->setVisible(true, INV_VALUE_5);
	_txt->setVisible(true, INV_VALUE_6);
	_txt->setVisible(true, INV_VALUE_7);
}

void Menu::update_inventory(std::vector<std::string> string)
{
	int count = 0;
	
	for (std::vector<std::string>::iterator it = string.begin();
	     it != string.end(); ++it) {
		if (count == 0) {
			_txt->setText((*it).c_str(), INV_VALUE_1);
		} else if (count == 1) {
			_txt->setText((*it).c_str(), INV_VALUE_2);
		} else if (count == 2) {
			_txt->setText((*it).c_str(), INV_VALUE_3);
		} else if (count == 3) {
			_txt->setText((*it).c_str(), INV_VALUE_4);
		} else if (count == 4) {
			_txt->setText((*it).c_str(), INV_VALUE_5);
		} else if (count == 5) {
			_txt->setText((*it).c_str(), INV_VALUE_6);
		} else if (count == 6) {
			_txt->setText((*it).c_str(), INV_VALUE_7);
		}
		count += 1;
	}
}

void Menu::launch_game()
{
	_btn->setVisible(false, ADD_TEAM1);
	_btn->setVisible(false, ADD_TEAM2);
	_btn->setVisible(false, ADD_TEAM3);
	_btn->setVisible(false, ADD_TEAM4);
	_btn->setVisible(false, LAUNCH_GAME);

	for(size_t i = 0; i < _srv->srvClient->team.size(); i++) {
		auto nbLaunch = _srv->srvClient->nb[i];
		auto str = wchar_to_string(_srv->srvClient->team[i]);
		_serverHandler->addAi(str, nbLaunch);
	}
	/* EXECUTE ALL IA */
}

void Menu::next_song()
{
	_snd->playNextMusic();
	std::cout << "Next music !" << "\n";
}

void Menu::exit()
{
	needToExit = true;
	std::cout << "Exit\n";
}

int		Menu::getPort() const
{
	return atoi(wchar_to_string(_srv->port).c_str());
}

bool	Menu::getExit() const
{
	return needToExit;
}

std::shared_ptr<ServerHandler>	Menu::getServerHandler(void) const noexcept
{
	return _serverHandler;
}

void	Menu::nextSkyBox()
{
	++idSkyBox;
}