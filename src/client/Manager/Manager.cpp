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
		this->parseCmd();
		return;
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

void	Manager::parseCmd()
{
	_cmd["msz"] = std::bind(&Manager::msz, this);
	_cmd["msz"]();
}

bool	Manager::msz()//! X Y\n || msz\n map size
{
	std::cout << "ON PASSE" << std::endl;
	if (!_args || !_args[0] || strncmp(_args[0], "msz", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::bct()//! X Y q0 q1 q2 q3 q4 q5 q6\n || bct X Y\n content of a tile
{
	if (!_args || !_args[0] || strncmp(_args[0], "bct", 3)) {
		return (false);
	}
	return (true);
}
//! boo	bct(); X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles || mct\n content of the map (all the tiles)
bool	Manager::tna()//! N\n * nbr_teams || tna\n name of all the teams
{
	if (!_args || !_args[0] || strncmp(_args[0], "tna", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pnw()// #n X Y O L N\n connection of a new player
{
	if (!_args || !_args[0] || strncmp(_args[0], "pnw", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::ppo()//! n X Y O\n || ppo #n\n player’s position
{
	if (!_args || !_args[0] || strncmp(_args[0], "ppo", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::plv()//! n L\n || plv #n\n player’s level
{
	if (!_args || !_args[0] || strncmp(_args[0], "plv", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pin()//! n X Y q0 q1 q2 q3 q4 q5 q6\n || pin #n\n player’s inventory
{
	if (!_args || !_args[0] || strncmp(_args[0], "pin", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pex()// n\n explusion
{
	if (!_args || !_args[0] || strncmp(_args[0], "pex", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pbc()// n M\n broadcast
{
	if (!_args || !_args[0] || strncmp(_args[0], "pbc", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pic()// X Y L n n . . . \n start of an incantation (by the first player)
{
	if (!_args || !_args[0] || strncmp(_args[0], "pic", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pie()// X Y R\n end of an incantation
{
	if (!_args || !_args[0] || strncmp(_args[0], "pie", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pfk()// n\n egg laying by the player
{
	if (!_args || !_args[0] || strncmp(_args[0], "pfk", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pdr()// n i\n resource dropping
{
	if (!_args || !_args[0] || strncmp(_args[0], "pdr", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pgt()// n i\n resource collecting
{
	if (!_args || !_args[0] || strncmp(_args[0], "pgt", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::pdi()// n\n death of a player
{
	if (!_args || !_args[0] || strncmp(_args[0], "pdi", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::enw()// e n X Y\n an egg was laid by a player
{
	if (!_args || !_args[0] || strncmp(_args[0], "enw", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::eht()// e\n egg hatching
{
	if (!_args || !_args[0] || strncmp(_args[0], "eht", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::ebo()// e\n player connection for an egg
{
	if (!_args || !_args[0] || strncmp(_args[0], "ebo", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::edi()// e\n death of an hatched egg
{
	if (!_args || !_args[0] || strncmp(_args[0], "edi", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::sgt()//! T\n || sgt\n time unit request
{
	if (!_args || !_args[0] || strncmp(_args[0], "sgt", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::sst()//! T\n || sst T\n time unit modification
{
	if (!_args || !_args[0] || strncmp(_args[0], "sst", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::seg()// N\n end of game
{
	if (!_args || !_args[0] || strncmp(_args[0], "seg", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::smg()// M\n message from the server
{
	if (!_args || !_args[0] || strncmp(_args[0], "smg", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::suc()//\n unknown command
{
	if (!_args || !_args[0] || strncmp(_args[0], "suc", 3)) {
		return (false);
	}
	return (true);
}
bool	Manager::sbp()//\n command parameter
{
	if (!_args || !_args[0] || strncmp(_args[0], "sbp", 3)) {
		return (false);
	}
	return (true);
}