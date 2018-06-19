/*
** EPITECH PROJECT, 2018
** Manager
** File description:
** Manager
*/

#include "Manager.hpp"

Manager::Manager(char *ip, int port)
{
	_client = std::make_unique<Client>();
	_readBuffer = std::make_unique<Buffer>(LIMIT_READ);
	_sendBuffer = std::make_unique<Buffer>(LIMIT_SEND);
	_char_read = 0;
	_args = NULL;
	this->initReadCmd();
	if (!this->connectClient(ip, port)) {
		throw std::runtime_error("Error: Failed to connect");
	}
}
Manager::~Manager()
{
}
int		Manager::connectClient(char *ip, int port)
{
	if (_client->connectServer(ip, port) == -1) {
		return (0);
	}
	while ("Cyril > Thery") {
		Select select;
		int fd = _client->getFdServer();
		select.addFd(fd);
		try
		{ select.select(1); }
		catch (Select::ExceptSelect const & err)
		{ _stop = true; }
		if (select.canRead(fd))
		{
			this->readInFd(_client->getFdServer());
			if (_char_read > 0 && _readBuffer->isEndOfCommand()) {
				_args = this->parseMe(_readBuffer->Get(), " \n");
				if (_args && !strcmp(_args[0], "WELCOME")) {
					_sendBuffer->Put("SPECTATOR\n");
					this->writeInFd(_client->getFdServer());
				} else if (_args && !strcmp(_args[0], "ok")) {
					return (1);
				}
				this->freeArgs();
			} else {
				return (0);
			}
		}
	}
	return (0);
}
void	Manager::spectateGame()
{
	_stop = false;
	while (!_stop)
	{
		Select select;
		int fd = _client->getFdServer();
		select.addFd(fd);
		try
		{ select.select(1); }
		catch (Select::ExceptSelect const & err)
		{ _stop = true; }
		try
		{
			if (select.canRead(fd))
			{
				this->readInFd(fd);
				this->parseCmd();
				this->freeArgs();
			}
			if (select.canWrite(fd))
			{
				this->writeInFd(fd);
			}
			if (select.canError(fd)) {}
		}
		catch (std::exception const & err)
		{
			_stop = true;
		}
	}
}
void	Manager::readInFd(int fd)
{
	char	*buffer = (char *)calloc(LIMIT_READ, 1);
	_char_read = read(fd, buffer, LIMIT_READ);
	if (_char_read <= 0) {
		_args = NULL;
		return;
	}
	std::cout << "RCV:" << buffer << std::endl;
	_readBuffer->Put(buffer);
	free(buffer);
}
void	Manager::writeInFd(int fd)
{
	char	*buffer = _sendBuffer->Get();
	write(fd, buffer, strlen(buffer));
}

void	Manager::initReadCmd()
{
	_cmd["msz"] = std::bind(&Manager::msz, this);
	_cmd["bct"] = std::bind(&Manager::bct, this);
	_cmd["tna"] = std::bind(&Manager::tna, this);
	_cmd["pnw"] = std::bind(&Manager::tna, this);
	_cmd["ppo"] = std::bind(&Manager::pnw, this);
	_cmd["plv"] = std::bind(&Manager::ppo, this);
	_cmd["pin"] = std::bind(&Manager::plv, this);
	_cmd["pex"] = std::bind(&Manager::pin, this);
	_cmd["pbc"] = std::bind(&Manager::pex, this);
	_cmd["pic"] = std::bind(&Manager::pbc, this);
	_cmd["pie"] = std::bind(&Manager::pic, this);
	_cmd["pfk"] = std::bind(&Manager::pie, this);
	_cmd["pdr"] = std::bind(&Manager::pfk, this);
	_cmd["pgt"] = std::bind(&Manager::pdr, this);
	_cmd["pdi"] = std::bind(&Manager::pgt, this);
	_cmd["enw"] = std::bind(&Manager::pdi, this);
	_cmd["eht"] = std::bind(&Manager::enw, this);
	_cmd["ebo"] = std::bind(&Manager::eht, this);
	_cmd["edi"] = std::bind(&Manager::ebo, this);
	_cmd["sgt"] = std::bind(&Manager::edi, this);
	_cmd["sst"] = std::bind(&Manager::sgt, this);
	_cmd["seg"] = std::bind(&Manager::sst, this);
	_cmd["smg"] = std::bind(&Manager::seg, this);
	_cmd["suc"] = std::bind(&Manager::smg, this);
	_cmd["sbp"] = std::bind(&Manager::suc, this);
}

void	Manager::freeArgs()
{
	if (_args) {
		for(size_t i = 0; _args[i]; i++) {
			free(_args[i]);
		}
		free(_args);
		_args = NULL;
	}
}

void	Manager::parseCmd()
{
	_args = this->parseMe(_readBuffer->Get(), " \n");
	if (_args && _args[0] && _cmd.find(std::string(_args[0])) != _cmd.end()) {
		_cmd[std::string(_args[0])]();
	} else {
		std::cout << "Command Not found" << std::endl;
	}
}

bool	Manager::msz()//! X Y\n || msz\n map size
{
	if (!_args[1] || !_args[2])
		return (false);
	_map.createMap(atoi(_args[1]), atoi(_args[2]));
	return (true);
}

//! boo	bct(); X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles || mct\n content of the map (all the tiles)
bool	Manager::bct()//! X Y q0 q1 q2 q3 q4 q5 q6\n || bct X Y\n content of a tile
{
	_map.updateMap(_args);
	return (true);
}

bool	Manager::tna()//! N\n * nbr_teams || tna\n name of all the teams
{
	int	i = 0;
	_teams.clear();
	while (_args[i]) {
		if (!_args[i + 1]) {
			break;
		}
		_teams.emplace_back(std::string(_args[i + 1]));
	}
	return (true);
}
bool	Manager::pnw()// #n X Y O L N\n connection of a new player
{
	if (!_args[1] || !_args[2] || !_args[3]
		|| !_args[4] || !_args[5] || !_args[6])
		return (false);
	std::string teamName(_args[6]);
	int	idxTeam = 0;
	for(size_t i = 0; i < _teams.size(); i++)
	{
		if (teamName == _teams[i]) {
			idxTeam = i;
			break;
		}
	}
	_idxPlayers.push_back(atoi(_args[1]));
	Direction dir;
	dir.setDir(atoi(_args[4]));
	Point	pos(atoi(_args[2]), atoi(_args[3]));
	_players[_idxPlayers.back()] = std::make_shared<Player>(
		pos,
		dir,
		teamName,
		idxTeam,
		atoi(_args[5]));
	return (true);
}
bool	Manager::ppo()//! n X Y O\n || ppo #n\n player’s position
{
	if (!_args[1] || !_args[2] || !_args[3] || !_args[4]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end()) {
		_players[idxPlayer]->setPos({atoi(_args[2]), atoi(_args[3])});
		Direction dir;
		dir.setDir(atoi(_args[4]));
		_players[idxPlayer]->setCurrentDir(dir);
	}
	return (true);
}
bool	Manager::plv()//! n L\n || plv #n\n player’s level
{
	if (!_args[1] || !_args[2]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end()) {
		_players[idxPlayer]->setLevel(atoi(_args[2]));
	}
	return (true);
}
bool	Manager::pin()//! n X Y q0 q1 q2 q3 q4 q5 q6\n || pin #n\n player’s inventory
{
	if (!_args[1] || !_args[2] || !_args[3]
		|| !_args[4] || !_args[5] || !_args[6]
		|| !_args[7] || !_args[8] || !_args[9] || !_args[10] ) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end()) {
		_players[idxPlayer]->setPos({atoi(_args[2]), atoi(_args[3])});
		_players[idxPlayer]->setNbFood(atoi(_args[4]));
		_players[idxPlayer]->setNbStone1(atoi(_args[5]));
		_players[idxPlayer]->setNbStone2(atoi(_args[6]));
		_players[idxPlayer]->setNbStone3(atoi(_args[7]));
		_players[idxPlayer]->setNbStone4(atoi(_args[8]));
		_players[idxPlayer]->setNbStone5(atoi(_args[9]));
		_players[idxPlayer]->setNbStone6(atoi(_args[10]));
	}
	return (true);
}
bool	Manager::pex()// n\n explusion
{
	return (true);
}
bool	Manager::pbc()// n M\n broadcast
{
	if (!_args[1] || !_args[2]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end()) {
		_players[idxPlayer]->setIsBroadcasting(true);
	}	
	return (true);
}
bool	Manager::pic()// X Y L n n . . . \n start of an incantation (by the first player)
{
	if (!_args[1] || !_args[2] || !_args[3] || !_args[4]) {
		return (false);
	}
	for(int i = 4; _args[i]; i++) {
		int idxPlayer = atoi(_args[i]);
		if (_players.find(idxPlayer) != _players.end()) {
			_players[idxPlayer]->setIsIncanting(true);
		}
	}
	return (true);
}
bool	Manager::pie()// X Y R\n end of an incantation
{
	if (!_args[1] || !_args[2] || !_args[3]) {
		return (false);
	}
	Point pos(atoi(_args[1]), atoi(_args[2]));
	for(auto it = _idxPlayers.begin(); it != _idxPlayers.end(); ++it)
	{
		if (_players[*it]->getPos() == pos && _players[*it]->getIsIncanting()) {
			_players[*it]->setIsIncanting(false);
		}
	}
	return (true);
}
bool	Manager::pfk()// n\n egg laying by the player
{
	return (true);
}
bool	Manager::pdr()// n i\n resource dropping
{
	if (!_args[1] || !_args[2]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	int nbRess = atoi(_args[2]);
	if (_players.find(idxPlayer) != _players.end()) {
		auto items = _map.getCase(_players[idxPlayer]->getPos());
		if (nbRess == 0) {
			_players[idxPlayer]->setNbFood(_players[idxPlayer]->getNbFood() - 1);
			items._food += 1;
		} else if (nbRess == 1) {
			_players[idxPlayer]->setNbStone1(_players[idxPlayer]->getNbStone1() - 1);
			items._stone1 += 1;
		} else if (nbRess == 2) {
			_players[idxPlayer]->setNbStone2(_players[idxPlayer]->getNbStone2() - 1);
			items._stone2 += 1;
		} else if (nbRess == 3) {
			_players[idxPlayer]->setNbStone3(_players[idxPlayer]->getNbStone3() - 1);
			items._stone3 += 1;
		} else if (nbRess == 4) {
			_players[idxPlayer]->setNbStone4(_players[idxPlayer]->getNbStone4() - 1);
			items._stone4 += 1;
		} else if (nbRess == 5) {
			_players[idxPlayer]->setNbStone5(_players[idxPlayer]->getNbStone5() - 1);
			items._stone5 += 1;
		} else if (nbRess == 6) {
			_players[idxPlayer]->setNbStone6(_players[idxPlayer]->getNbStone6() - 1);
			items._stone6 += 1;
		}
		_map.setCase(_players[idxPlayer]->getPos(), items);
	}
	return (true);
}
bool	Manager::pgt()// n i\n resource collecting
{
	if (!_args[1] || !_args[2]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	int nbRess = atoi(_args[2]);
	if (_players.find(idxPlayer) != _players.end()) {
		auto items = _map.getCase(_players[idxPlayer]->getPos());
		if (nbRess == 0) {
			_players[idxPlayer]->setNbFood(_players[idxPlayer]->getNbFood() + 1);
			items._food -= 1;
		} else if (nbRess == 1) {
			_players[idxPlayer]->setNbStone1(_players[idxPlayer]->getNbStone1() + 1);
			items._stone1 -= 1;
		} else if (nbRess == 2) {
			_players[idxPlayer]->setNbStone2(_players[idxPlayer]->getNbStone2() + 1);
			items._stone2 -= 1;
		} else if (nbRess == 3) {
			_players[idxPlayer]->setNbStone3(_players[idxPlayer]->getNbStone3() + 1);
			items._stone3 -= 1;
		} else if (nbRess == 4) {
			_players[idxPlayer]->setNbStone4(_players[idxPlayer]->getNbStone4() + 1);
			items._stone4 -= 1;
		} else if (nbRess == 5) {
			_players[idxPlayer]->setNbStone5(_players[idxPlayer]->getNbStone5() + 1);
			items._stone5 -= 1;
		} else if (nbRess == 6) {
			_players[idxPlayer]->setNbStone6(_players[idxPlayer]->getNbStone6() + 1);
			items._stone6 -= 1;
		}
		_map.setCase(_players[idxPlayer]->getPos(), items);
	}
	return (true);
}
bool	Manager::pdi()// n\n death of a player
{
	if (!_args[1]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end()) {
		_players[idxPlayer]->setIsDead(true);
		for(auto it = _idxPlayers.begin(); it != _idxPlayers.end(); ++it) {
			if (*it == idxPlayer) {
				_idxPlayers.erase(it);
				break;
			}
		}
	}
	return (true);
}
bool	Manager::enw()// e n X Y\n an egg was laid by a player
{
	if (!_args[1] || !_args[2] || !_args[3] || !_args[4]) {
		return (false);
	}
	int	eggNumber = atoi(_args[1]);
	Point eggPos(atoi(_args[3]), atoi(_args[4]));
	_idxEggs.push_back(eggNumber);
	_eggs[eggNumber] = eggPos;
	return (true);
}
bool	Manager::eht()// e\n egg hatching
{
	if (!_args[1]) {
		return (false);
	}
	int idxEgg = atoi(_args[1]);
	if (_eggs.find(idxEgg) != _eggs.end()) {
		for(auto it = _idxEggs.begin(); it != _idxEggs.end(); ++it) {
			if (*it == idxEgg) {
				_idxEggs.erase(it);
				break;
			}
		}
	}
	return (true);
}
bool	Manager::ebo()// e\n player connection for an egg
{
	return (true);
}
bool	Manager::edi()// e\n death of an hatched egg
{
	return (true);
}
bool	Manager::sgt()//! T\n || sgt\n time unit request
{
	if (!_args[1]) {
		return (false);
	}
	_freq = atoi(_args[1]);
	return (true);
}
bool	Manager::sst()//! T\n || sst T\n time unit modification
{
	if (!_args[1]) {
		return (false);
	}
	_freq = atoi(_args[1]);
	return (true);
}
bool	Manager::seg()// N\n end of game
{
	if (!_args[1]) {
		return (false);
	}
	_winner = std::string(_args[1]);
	_stop = true;
	return (true);
}
bool	Manager::smg()// M\n message from the server
{
	return (true);
}
bool	Manager::suc()//\n unknown command
{
	return (true);
}
bool	Manager::sbp()//\n command parameter
{
	return (true);
}