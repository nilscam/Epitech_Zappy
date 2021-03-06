/*
** EPITECH PROJECT, 2018
** Manager
** File description:
** Manager
*/

#ifndef MANAGER_HPP_
# define MANAGER_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <list>
#include <vector>

#include "Client.hpp"
#include "Select.hpp"
#include "Buffer.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Clock.hpp"
#include "Rectangle.hpp"
#include "GUI.hpp"
#include "IrrlichtDisplay.hpp"
#include "Egg.hpp"
#include "ServerHandler.hpp"

#define LIMIT_READ	10000000
#define LIMIT_SEND	256

class Manager
{
public:
	Manager();
	~Manager();
	bool	init();
	bool	init(const char *ip, int port);
	bool	initServer();
	int		connectClient(const char *ip, int port);
	void	spectateGame();
	bool	needToExit(void) const noexcept;

private:
	//! Methodes
	char	**parseMe(char *str, const char *opt);
	void	readInFd(int fd);
	void	writeInFd(int fd);
	void	parseCmd(void);
	void	initReadCmd(void);
	void	freeArgs(void);
	void	updateGUILevelPlayer();
	void	updateGUITimeUnit();
	void	manageCamOnPlayer();
	ListBox::MSGtype	getColorForTeam(std::string const & name) const noexcept;
	void	manageSkyBox();
	void	manageTimeSinceBegin();

	bool	msz();//! X Y\n || msz\n map size
	bool	bct();//! X Y q0 q1 q2 q3 q4 q5 q6\n || bct X Y\n content of a tile
	//! ool	bct(); X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles || mct\n content of the map (all the tiles)
	bool	tna();//! N\n * nbr_teams || tna\n name of all the teams
	bool	pnw();// #n X Y O L N\n connection of a new player
	bool	ppo();//! n X Y O\n || ppo #n\n player’s position
	bool	plv();//! n L\n || plv #n\n player’s level
	bool	pin();//! n X Y q0 q1 q2 q3 q4 q5 q6\n || pin #n\n player’s inventory
	bool	pex();// n\n explusion
	bool	pbc();// n M\n broadcast
	bool	pic();// X Y L n n . . . \n start of an incantation (by the first player)
	bool	pie();// X Y R\n end of an incantation
	bool	pfk();// n\n egg laying by the player
	bool	pdr();// n i\n resource dropping
	bool	pgt();// n i\n resource collecting
	bool	pdi();// n\n death of a player
	bool	enw();// e n X Y\n an egg was laid by a player
	bool	eht();// e\n egg hatching
	bool	ebo();// e\n player connection for an egg
	bool	edi();// e\n death of an hatched egg
	bool	sgt();//! T\n || sgt\n time unit request
	bool	sst();//! T\n || sst T\n time unit modification
	bool	seg();// N\n end of game
	bool	smg();// M\n message from the server
	bool	suc();//\n unknown command
	bool	sbp();//\n command parameter
	bool	egg();// e X Y
	bool	time();// t \n time since beginning of the game
	//! --------- 

	//! Variables
	std::unique_ptr<ServerHandler>	_serverHandler;
	std::unique_ptr<Client>		_client;
	std::unique_ptr<Buffer>		_readBuffer;
	std::unique_ptr<Buffer>		_sendBuffer;
	std::shared_ptr<GUI>		_gui;
	std::unique_ptr<IrrlichtDisplay>				_display;
	std::map<std::string, std::function<void()>>	_cmd;
	int												_port;

	Map												_map;
	std::map<int, std::shared_ptr<Player>>			_players;
	std::list<int>									_idxPlayers;
	std::map<int, std::shared_ptr<Egg>>				_eggs;
	std::list<int>									_idxEggs;
	std::vector<std::string>						_teams;
	int												_freq;
	std::string										_winner;
	int												_followCamPlayer;
	int												_lastSkyBox;
	int												_timeSinceBegin;
	Clock											_refreshTour;
	Clock											_updateTour;

	bool						_stop;
	int							_char_read;
	char						**_args;
	bool						_needToExit;
	//! --------- 
};


#endif /* MANAGER_HPP_ */