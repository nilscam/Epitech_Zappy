/*
** EPITECH PROJECT, 2018
** Manager
** File description:
** Manager
*/

#include "Manager.hpp"

Manager::Manager()
{
	_needToExit = false;
	_client = std::make_unique<Client>();
	_readBuffer = std::make_unique<Buffer>(LIMIT_READ);
	_sendBuffer = std::make_unique<Buffer>(LIMIT_SEND);
	_char_read = 0;
	_args = NULL;
	_port = 4242;
	_followCamPlayer = -2;
	_lastSkyBox = 0;
	this->initReadCmd();
	_display = std::make_unique<IrrlichtDisplay>();
	if (!_display->init()) {
		throw std::runtime_error("Error init lib\n");
	}
	_gui = std::make_shared<GUI>(_display->getDevice(), _display->getDriver());
}

bool	Manager::init()
{
	while (!this->initServer());
	return (true);
}

bool	Manager::init(const char *ip, int port)
{
	if (!this->connectClient(ip, port)) {
		return (false);
	}
	return (true);
}

bool	Manager::initServer()
{
	_display->setMapSize({5, 5});
	_gui->menu.server_open();
	while (!_gui->menu.isServerLaunch) {
		_display->loop();
		if (_display->isDeviceRunning() && !_gui->menu.getExit()) {
			_display->display(_gui);
			this->manageSkyBox();
		} else {
			_needToExit = true;
			return (true);
		}
	}
	std::cout << _gui->getPort() << std::endl;
	if (!this->connectClient(std::string("127.0.0.1").c_str(), _gui->getPort())) {
		std::cout << "failed to connect" <<std::endl;
		return (false);
	}
	return (true);
}

Manager::~Manager()
{
	_display->deinit();
}

int		Manager::connectClient(const char *ip, int port)
{
	bool connected = false;
	Clock timeout;
	Clock retry;
	while (!connected && timeout.timeSinceMark() < 2000)
	{
		connected = (_client->connectServer(ip, port) != -1);
		std::cout << "Connecting to " << ip << ":" << port << "... : " << connected << std::endl;
		while (!connected && retry.timeSinceMark() < 250);
		retry.mark();
	}
	if (!connected)
	{
		std::cout << "Failed to connect to " << ip << ":" << port << std::endl;
		return 0;
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
					_sendBuffer->Put("msz\nmct\ntna\npnw\negg\nsgt\n");
					this->writeInFd(_client->getFdServer());
					this->freeArgs();
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
	_gui->launchGui();
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
		if (_display->isDeviceRunning() && !_gui->menu.getExit()) {
			_display->loop();
			_display->display(_gui);
			this->updateGUILevelPlayer();
			this->updateGUITimeUnit();
			this->manageCamOnPlayer();
			this->manageSkyBox();
			//_display->getTeamClicked(_idxPlayers);
		} else {
			_stop = true;
		}
	}
	_client->disconnect();
}
bool	Manager::needToExit(void) const noexcept
{
	return _needToExit;
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
	if (buffer) {
		write(fd, buffer, strlen(buffer));
		free(buffer);
	}
}

void	Manager::initReadCmd()
{
	_cmd["msz"] = std::bind(&Manager::msz, this);
	_cmd["bct"] = std::bind(&Manager::bct, this);
	_cmd["tna"] = std::bind(&Manager::tna, this);
	_cmd["pnw"] = std::bind(&Manager::pnw, this);
	_cmd["ppo"] = std::bind(&Manager::ppo, this);
	_cmd["plv"] = std::bind(&Manager::plv, this);
	_cmd["pin"] = std::bind(&Manager::pin, this);
	_cmd["pex"] = std::bind(&Manager::pex, this);
	_cmd["pbc"] = std::bind(&Manager::pbc, this);
	_cmd["pic"] = std::bind(&Manager::pic, this);
	_cmd["pie"] = std::bind(&Manager::pie, this);
	_cmd["pfk"] = std::bind(&Manager::pfk, this);
	_cmd["pdr"] = std::bind(&Manager::pdr, this);
	_cmd["pgt"] = std::bind(&Manager::pgt, this);
	_cmd["pdi"] = std::bind(&Manager::pdi, this);
	_cmd["enw"] = std::bind(&Manager::enw, this);
	_cmd["eht"] = std::bind(&Manager::eht, this);
	_cmd["ebo"] = std::bind(&Manager::ebo, this);
	_cmd["edi"] = std::bind(&Manager::edi, this);
	_cmd["sgt"] = std::bind(&Manager::sgt, this);
	_cmd["sst"] = std::bind(&Manager::sst, this);
	_cmd["seg"] = std::bind(&Manager::seg, this);
	_cmd["smg"] = std::bind(&Manager::smg, this);
	_cmd["suc"] = std::bind(&Manager::suc, this);
	_cmd["sbp"] = std::bind(&Manager::sbp, this);
	_cmd["egg"] = std::bind(&Manager::egg, this);
}

void	Manager::freeArgs()
{
	if (_args) {
		if (_args[0]) {
			free(_args[0]);
		}
		free(_args);
		_args = NULL;
	}
}

void	Manager::parseCmd()
{
	char **cmd = this->parseMe(_readBuffer->Get(), "\n");
	
	for(size_t i = 0; cmd && cmd[i]; i++) {
		_args = this->parseMe(cmd[i], " ");
		if (_args && _args[0] && _cmd.find(std::string(_args[0])) != _cmd.end()) {
			_cmd[std::string(_args[0])]();
		} else {
			std::cout << "Command Not found" << std::endl;
		}
	}
	if (cmd) {
		free(cmd[0]);
		free(cmd);
	}
}

void	Manager::updateGUILevelPlayer()
{
	std::map<int, std::map<int, int>> teamLevel;
	for(size_t i = 0; i < _teams.size(); i++)
	{
		teamLevel[i][1] = 0;
		teamLevel[i][2] = 0;
		teamLevel[i][3] = 0;
		teamLevel[i][4] = 0;
		teamLevel[i][5] = 0;
		teamLevel[i][6] = 0;
		teamLevel[i][7] = 0;
		teamLevel[i][8] = 0;
	}
	for(auto it = _idxPlayers.begin(); it != _idxPlayers.end(); ++it) {
		++teamLevel[_players[*it]->getIdxTeam()][_players[*it]->getLevel()];
	}
	for(size_t i = 0; i < _teams.size(); i++) {
		for(size_t j = 1; j < 9; j++) {
			_gui->table.setValue(j, i + 1, std::to_string(teamLevel[i][j]));
		}
	}
}

void	Manager::updateGUITimeUnit()
{
	if (!_gui->scrollBarPosChanged()) {
		return;
	}
	auto freq = _gui->scrollBar.getPos();
	char str[20];
	sprintf(str, "sst %d\n", freq);
	_sendBuffer->Put(str);
}

void	Manager::manageCamOnPlayer()
{
	if (_followCamPlayer >= 0) {
		// _gui->affPlayerInventory(_players[_followCamPlayer]->getNbFood(),
		// 						_players[_followCamPlayer]->getNbStone1(),
		// 						_players[_followCamPlayer]->getNbStone2(),
		// 						_players[_followCamPlayer]->getNbStone3(),
		// 						_players[_followCamPlayer]->getNbStone4(),
		// 						_players[_followCamPlayer]->getNbStone5(),
		// 						_players[_followCamPlayer]->getNbStone6());
	}
	auto playerFollowCam = _display->getIdPlayerFollowCam();
	if (playerFollowCam != _followCamPlayer && playerFollowCam >= 0) {
		char str[20];
		sprintf(str, "pin %d\n", playerFollowCam);
		_sendBuffer->Put(str);
		_followCamPlayer = playerFollowCam;
	} else if (playerFollowCam != _followCamPlayer && playerFollowCam < 0) {
		//_gui->setVisibleInventory(false);
		_followCamPlayer = playerFollowCam;
	}
}

void	Manager::manageSkyBox()
{
	if (_gui->menu.idSkyBox != _lastSkyBox) {
		_lastSkyBox = _gui->menu.idSkyBox;
		_display->create_sky(_lastSkyBox);
	}
}

ListBox::MSGtype	Manager::getColorForTeam(std::string const & name) const noexcept
{
	int idx = 0;
	for (auto const & team : _teams)
	{
		if (name == team)
		{
			return	idx == 0 ? ListBox::MSGtype::RED_TEAM
				:	idx == 1 ? ListBox::MSGtype::BLUE_TEAM
				:	idx == 2 ? ListBox::MSGtype::GREEN_TEAM
				:	idx == 3 ? ListBox::MSGtype::YELLOW_TEAM
				:	ListBox::MSGtype::OTHER_TEAM;
		}
		++idx;
	}
	return ListBox::MSGtype::OTHER_TEAM;
}

bool	Manager::msz()//! X Y\n || msz\n map size
{
	if (!_args[1] || !_args[2])
		return (false);
	_map.createMap(atoi(_args[1]), atoi(_args[2]));
	_display->setMapSize({atoi(_args[1]), atoi(_args[2])});
	_gui->addListBoxMessage(
		"Size of the map : " + std::string(_args[1])
		+ "x" + std::string(_args[2]),
		getColorForTeam(_teams.back())
	);
	return (true);
}

//! boo	bct(); X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles || mct\n content of the map (all the tiles)
bool	Manager::bct()//! X Y q0 q1 q2 q3 q4 q5 q6\n || bct X Y\n content of a tile
{
	_map.updateMap(_args);
	if (!_args[1] || !_args[2] || !_args[3]
	|| !_args[4] || !_args[5] || !_args[6]
	|| !_args[7] || !_args[8] || !_args[9])
		return (false);
	Point point(atoi(_args[1]), atoi(_args[2]));
	if (_map.isInMap(point)) {
		Map::MapCase items;
		items._food = atoi(_args[3]);
		items._stone1 = atoi(_args[4]);
		items._stone2 = atoi(_args[5]);
		items._stone3 = atoi(_args[6]);
		items._stone4 = atoi(_args[7]);
		items._stone5 = atoi(_args[8]);
		items._stone6 = atoi(_args[9]);
		_display->setMapTile(point, items);
	}
	return (true);
}

bool	Manager::tna()//! N\n * nbr_teams || tna\n name of all the teams
{
	if (!_args[1]) {
		return (false);
	}
	_teams.emplace_back(std::string(_args[1]));
	_display->setTeams(_teams);
	_gui->table.addTeamName({{_teams.back()}});
	_gui->addListBoxMessage(
		"New team Connected : " + _teams.back(),
		getColorForTeam(_teams.back())
	);
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
	int level = atoi(_args[5]);
	_players[_idxPlayers.back()] = std::make_shared<Player>(
		pos,
		dir,
		teamName,
		idxTeam,
		level);
	_display->addPlayer(
		_idxPlayers.back(),
		pos,
		dir,
		level,
		teamName,
		IDisplay::PlayerOrigin::TELEPORT
		);
	_gui->addListBoxMessage(
		"New Player Connected : #" + std::to_string(_idxPlayers.back()),
		getColorForTeam(teamName)
	);
	_gui->playSound(SoundManager::Sound::SOUND_YOSHI_YOSH);
	return (true);
}
bool	Manager::ppo()//! n X Y O\n || ppo #n\n player’s position
{
	if (!_args[1] || !_args[2] || !_args[3] || !_args[4]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	Point pos(atoi(_args[2]), atoi(_args[3]));
	Direction dir;
	dir.setDir(atoi(_args[4]));
	if (_players.find(idxPlayer) != _players.end()) {
		if (dir != _players[idxPlayer]->getCurrentDir()) {
			_display->changePlayerDir(idxPlayer, dir);
			_players[idxPlayer]->setCurrentDir(dir);
		}
		if (pos != _players[idxPlayer]->getPos()) {
			_display->movePlayer(idxPlayer, pos);
			_players[idxPlayer]->setPos(pos);
		}
		// _gui->addListBoxMessage(
		// 	"Player #" + std::to_string(idxPlayer)
		// 	+ " Move",
		// 	getColorForTeam(_players[idxPlayer]->getNameTeam())
		// );
	}
	return (true);
}
bool	Manager::plv()//! n L\n || plv #n\n player’s level
{
	if (!_args[1] || !_args[2]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	int	level = atoi(_args[2]);
	if (_players.find(idxPlayer) != _players.end()) {
		_display->setPlayerLevel(idxPlayer, level);
		_players[idxPlayer]->setLevel(level);
		_gui->addListBoxMessage(
			"Player #" + std::to_string(idxPlayer)
			+ " level is now " + std::to_string(level),
			getColorForTeam(_players[idxPlayer]->getNameTeam())
		);
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
	if (!_args[1]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end()) {
		_display->setPlayerAction(
				idxPlayer, IDisplay::PlayerAnimationStyle::PUSH_PLAYER);
		_gui->addListBoxMessage(
			"Player #" + std::to_string(idxPlayer)
			+ " is aggressive today !",
			getColorForTeam(_players[idxPlayer]->getNameTeam())
		);
		_gui->playSound(SoundManager::Sound::SOUND_YOSHI_KICK);
	}
	for(auto it = _idxPlayers.begin(); it != _idxPlayers.end(); ++it)
	{
		if (*it == idxPlayer) {
			continue;
		}
		if (_players[idxPlayer]->getPos() == _players[*it]->getPos()) {
			Point pos(_players[*it]->getPos());
			if (_players[idxPlayer]->getCurrentDir() == Direction::Up) {
				pos.incY(-1);
			} else if (_players[idxPlayer]->getCurrentDir() == Direction::Right) {
				pos.incX(1);
			} else if (_players[idxPlayer]->getCurrentDir() == Direction::Down) {
				pos.incY(1);
			} else if (_players[idxPlayer]->getCurrentDir() == Direction::Left) {
				pos.incX(-1);
			}
			Point mapSize = _map.getMapSize();
			if (pos.getX() < 0) {
				pos.setX(mapSize.getX() + (pos.getX() % mapSize.getX()));
			}
			if (pos.getY() < 0) {
				pos.setY(mapSize.getY() + (pos.getY() * mapSize.getY()));
			}
			pos.setX(pos.getX() % mapSize.getX());
			pos.setY(pos.getY() % mapSize.getY());
			_players[*it]->setPos(pos);
			_display->pushPlayer(*it, pos, _players[*it]->getCurrentDir());
		}
	}
	
	return (true);
}
bool	Manager::pbc()// n M\n broadcast
{
	if (!_args[1] || !_args[2]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end()) {
		_display->setPlayerAction(
			idxPlayer, IDisplay::PlayerAnimationStyle::BROADCAST);
		_players[idxPlayer]->setIsBroadcasting(true);
		_gui->addListBoxMessage(
			"Player #" + std::to_string(idxPlayer)
			+ " said '" + std::string(_args[2]) + "'",
			getColorForTeam(_players[idxPlayer]->getNameTeam())
		);
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
			_display->setPlayerAction(
				idxPlayer, IDisplay::PlayerAnimationStyle::START_INCANTATION);
			_players[idxPlayer]->setIsIncanting(true);
			_gui->addListBoxMessage(
				"Player #" + std::to_string(idxPlayer)
				+ " is incanting",
				getColorForTeam(_players[idxPlayer]->getNameTeam())
			);
			_gui->playSound(SoundManager::Sound::SOUND_INVOCATION);
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
			_display->setPlayerAction(
				*it, IDisplay::PlayerAnimationStyle::END_INCANTATION);
			_gui->addListBoxMessage(
				"Player #" + std::to_string(*it)
				+ " has finished his incantation",
				getColorForTeam(_players[*it]->getNameTeam())
			);
		}
	}
	return (true);
}
bool	Manager::pfk()// n\n egg laying by the player
{
	if (!_args[1]) {
		return (false);
	}
	int idxPlayer = atoi(_args[1]);
	if (_players.find(idxPlayer) != _players.end())
	{
		_gui->addListBoxMessage(
			"Player #" + std::to_string(idxPlayer)
			+ " is laying an egg",
			getColorForTeam(_players[idxPlayer]->getNameTeam())
		);
	}
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
		std::string what = "Something";
		auto items = _map.getCase(_players[idxPlayer]->getPos());
		if (nbRess == 0) {
			_players[idxPlayer]->setNbFood(_players[idxPlayer]->getNbFood() - 1);
			items._food += 1;
			what = "Food";
		} else if (nbRess == 1) {
			_players[idxPlayer]->setNbStone1(_players[idxPlayer]->getNbStone1() - 1);
			items._stone1 += 1;
			what = "Linemate";
		} else if (nbRess == 2) {
			_players[idxPlayer]->setNbStone2(_players[idxPlayer]->getNbStone2() - 1);
			items._stone2 += 1;
			what = "Deraumere";
		} else if (nbRess == 3) {
			_players[idxPlayer]->setNbStone3(_players[idxPlayer]->getNbStone3() - 1);
			items._stone3 += 1;
			what = "Sibur";
		} else if (nbRess == 4) {
			_players[idxPlayer]->setNbStone4(_players[idxPlayer]->getNbStone4() - 1);
			items._stone4 += 1;
			what = "Mendiane";
		} else if (nbRess == 5) {
			_players[idxPlayer]->setNbStone5(_players[idxPlayer]->getNbStone5() - 1);
			items._stone5 += 1;
			what = "Phiras";
		} else if (nbRess == 6) {
			_players[idxPlayer]->setNbStone6(_players[idxPlayer]->getNbStone6() - 1);
			items._stone6 += 1;
			what = "Thystame";
		}
		_map.setCase(_players[idxPlayer]->getPos(), items);
		_display->setPlayerAction(
			idxPlayer, IDisplay::PlayerAnimationStyle::DROP_RESOURCE);
		_display->setMapTile(_players[idxPlayer]->getPos(), items);
		_gui->addListBoxMessage(
			"Player #" + std::to_string(idxPlayer)
			+ " Dropped " + what,
			getColorForTeam(_players[idxPlayer]->getNameTeam())
		);
		_gui->playSound(SoundManager::Sound::SOUND_POP);
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
		std::string what = "Something";
		auto items = _map.getCase(_players[idxPlayer]->getPos());
		if (nbRess == 0) {
			_players[idxPlayer]->setNbFood(_players[idxPlayer]->getNbFood() + 1);
			items._food -= 1;
			what = "Food";
		} else if (nbRess == 1) {
			_players[idxPlayer]->setNbStone1(_players[idxPlayer]->getNbStone1() + 1);
			items._stone1 -= 1;
			what = "Linemate";
		} else if (nbRess == 2) {
			_players[idxPlayer]->setNbStone2(_players[idxPlayer]->getNbStone2() + 1);
			items._stone2 -= 1;
			what = "Deraumere";
		} else if (nbRess == 3) {
			_players[idxPlayer]->setNbStone3(_players[idxPlayer]->getNbStone3() + 1);
			items._stone3 -= 1;
			what = "Sibur";
		} else if (nbRess == 4) {
			_players[idxPlayer]->setNbStone4(_players[idxPlayer]->getNbStone4() + 1);
			items._stone4 -= 1;
			what = "Mendiane";
		} else if (nbRess == 5) {
			_players[idxPlayer]->setNbStone5(_players[idxPlayer]->getNbStone5() + 1);
			items._stone5 -= 1;
			what = "Phiras";
		} else if (nbRess == 6) {
			_players[idxPlayer]->setNbStone6(_players[idxPlayer]->getNbStone6() + 1);
			items._stone6 -= 1;
			what = "Thystame";
		}
		_map.setCase(_players[idxPlayer]->getPos(), items);
		_display->setPlayerAction(
			idxPlayer, IDisplay::PlayerAnimationStyle::TAKE_RESOURCE);
		_display->setMapTile(_players[idxPlayer]->getPos(), items);
		_gui->addListBoxMessage(
			"Player #" + std::to_string(idxPlayer)
			+ " Took " + what,
			getColorForTeam(_players[idxPlayer]->getNameTeam())
		);
		_gui->playSound(SoundManager::Sound::SOUND_POP);
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
				_display->killPlayer(idxPlayer);
				_idxPlayers.erase(it);
				break;
			}
		}
		_gui->addListBoxMessage(
			"Player #" + std::to_string(idxPlayer)
			+ " Died",
			getColorForTeam(_players[idxPlayer]->getNameTeam())
		);
		_gui->playSound(SoundManager::Sound::SOUND_YOSHI_WAAH);
	}
	return (true);
}
bool	Manager::enw()// e n X Y\n an egg was laid by a player
{
	if (!_args[1] || !_args[2] || !_args[3] || !_args[4]) {
		return (false);
	}
	int	eggNumber = atoi(_args[1]);
	int idxPlayer = atoi(_args[2]);
	Point eggPos(atoi(_args[3]), atoi(_args[4]));
	_idxEggs.push_back(eggNumber);
	auto egg = std::make_shared<Egg>(eggPos, idxPlayer);
	_eggs[eggNumber] = egg;
	_display->addEgg(eggNumber, idxPlayer);
	_display->setPlayerAction(
			idxPlayer, IDisplay::PlayerAnimationStyle::EGG_LAYING);
	_gui->addListBoxMessage(
		"Player #" + std::to_string(idxPlayer)
		+ " has laid an egg",
		getColorForTeam(_players[idxPlayer]->getNameTeam())
	);
	_gui->playSound(SoundManager::Sound::SOUND_YOSHI_POP);
	return (true);
}
bool	Manager::eht()// e\n egg hatching
{
	if (!_args[1]) {
		return (false);
	}
	int idxEgg = atoi(_args[1]);
	int idxPlayer = _eggs[idxEgg]->getIdxPlayerFrom();
	if (_players.find(idxPlayer) != _players.end()) {
		auto team = _players[idxPlayer]->getNameTeam();
		_gui->getServerHandler()->addAi(team);
		std::cout << "Added ai" << std::endl;
	}
	_gui->addListBoxMessage(
		"Egg #" + std::to_string(idxEgg) + " is hatched"
	);
	return (true);
}

bool	Manager::ebo()// <egg_nb> <player_nb> <X> <Y> <dir> <lvl> <team>\n player connection for an egg
{
	if (!_args[1] || !_args[2] || !_args[3]
		|| !_args[4] || !_args[5] || !_args[6] || !_args[7])
		return (false);
	int idxEgg = atoi(_args[1]);
	if (_eggs.find(idxEgg) != _eggs.end()) {
		for(auto it = _idxEggs.begin(); it != _idxEggs.end(); ++it) {
			if (*it == idxEgg) {
				_display->removeEgg(idxEgg);
				_idxEggs.erase(it);
				break;
			}
		}
	}
	std::string teamName(_args[7]);
	int	idxTeam = 0;
	for(size_t i = 0; i < _teams.size(); i++)
	{
		if (teamName == _teams[i]) {
			idxTeam = i;
			break;
		}
	}
	_idxPlayers.push_back(atoi(_args[2]));
	Direction dir;
	dir.setDir(atoi(_args[5]));
	Point	pos(atoi(_args[3]), atoi(_args[4]));
	int level = atoi(_args[6]);
	_players[_idxPlayers.back()] = std::make_shared<Player>(
		pos,
		dir,
		teamName,
		idxTeam,
		level);
	_display->addPlayer(
		_idxPlayers.back(),
		pos,
		dir,
		level,
		teamName,
		IDisplay::PlayerOrigin::EGG
		);
	_gui->addListBoxMessage(
		"New Player Connected : #" + std::to_string(_idxPlayers.back())
		+ " from egg #" + std::to_string(idxEgg),
		getColorForTeam(teamName)
	);
	_gui->playSound(SoundManager::Sound::SOUND_YOSHI_YOSH);
	return (true);
}
bool	Manager::edi()// e\n death of an hatched egg
{
	if (!_args[1]) {
		return (false);
	}
	int idxEgg = atoi(_args[1]);
	if (_eggs.find(idxEgg) != _eggs.end()) {
		for(auto it = _idxEggs.begin(); it != _idxEggs.end(); ++it) {
			if (*it == idxEgg) {
				auto idPlayer = _eggs[idxEgg]->getIdxPlayerFrom();
				if (_players.find(idPlayer) != _players.end()) {
					auto teamName = _players[idPlayer]->getNameTeam();
					_gui->addListBoxMessage(
						"Death of the hatched egg #" + std::to_string(idxEgg),
						getColorForTeam(teamName)
					);
				}
				_display->removeEgg(idxEgg);
				_idxEggs.erase(it);
				break;
			}
		}
	}
	return (true);
}
bool	Manager::sgt()//! T\n || sgt\n time unit request
{
	if (!_args[1]) {
		return (false);
	}
	_freq = atoi(_args[1]);
	_display->setTimeUnit(_freq);
	return (true);
}
bool	Manager::sst()//! T\n || sst T\n time unit modification
{
	if (!_args[1]) {
		return (false);
	}
	_freq = atoi(_args[1]);
	_display->setTimeUnit(_freq);
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
	if (!_args[1]) {
		return (false);
	}
	_gui->addListBoxMessage(
		"SERVER : " + std::string(_args[1]),
		ListBox::MSGtype::SYSTEM
	);
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

bool	Manager::egg()// e X Y
{
	if (!_args[1] || !_args[2] || !_args[3]) {
		return (false);
	}
	int	eggNumber = atoi(_args[1]);
	int idxPlayer = 1;
	Point eggPos(atoi(_args[2]), atoi(_args[3]));
	_idxEggs.push_back(eggNumber);
	auto egg = std::make_shared<Egg>(eggPos, idxPlayer);
	_eggs[eggNumber] = egg;
	_display->addEgg(eggNumber, idxPlayer);
	_display->setPlayerAction(
			idxPlayer, IDisplay::PlayerAnimationStyle::EGG_LAYING);
	return (true);
}
