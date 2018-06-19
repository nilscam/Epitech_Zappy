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
	while ("Cyril > Threy") {
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
	map.createMap(atoi(_args[1]), atoi(_args[2]));
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
	return (true);
}
bool	Manager::pnw()// #n X Y O L N\n connection of a new player
{
	return (true);
}
bool	Manager::ppo()//! n X Y O\n || ppo #n\n player’s position
{
	return (true);
}
bool	Manager::plv()//! n L\n || plv #n\n player’s level
{
	return (true);
}
bool	Manager::pin()//! n X Y q0 q1 q2 q3 q4 q5 q6\n || pin #n\n player’s inventory
{
	return (true);
}
bool	Manager::pex()// n\n explusion
{
	return (true);
}
bool	Manager::pbc()// n M\n broadcast
{
	return (true);
}
bool	Manager::pic()// X Y L n n . . . \n start of an incantation (by the first player)
{
	return (true);
}
bool	Manager::pie()// X Y R\n end of an incantation
{
	return (true);
}
bool	Manager::pfk()// n\n egg laying by the player
{
	return (true);
}
bool	Manager::pdr()// n i\n resource dropping
{
	return (true);
}
bool	Manager::pgt()// n i\n resource collecting
{
	return (true);
}
bool	Manager::pdi()// n\n death of a player
{
	return (true);
}
bool	Manager::enw()// e n X Y\n an egg was laid by a player
{
	return (true);
}
bool	Manager::eht()// e\n egg hatching
{
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
	return (true);
}
bool	Manager::sst()//! T\n || sst T\n time unit modification
{
	return (true);
}
bool	Manager::seg()// N\n end of game
{
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