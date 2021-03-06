//
// Created by baptiste roubieu on 20/06/2018.
//

#include "IrrlichtDisplay.hpp"
#include <algorithm>

IrrlichtDisplay::IrrlichtDisplay()
	:	_timeUnit(1)
	,	_device(nullptr)
	,	_driver(nullptr)
	,	_sceneManager(nullptr)
	,	_camera(nullptr)
	,	_isInit(false)
	,	_followCam(IrrlichtDisplayConst::CLICK_ON_MAP)
	,	_zoomCam(150)
	,	_rotateCamera(true)
	,	_cameraRotationDegrees(0)
	,	_cursor(nullptr)
{
	_antiSpamCam.mark();
}

IrrlichtDisplay::~IrrlichtDisplay()
{
	deinit();
}

bool IrrlichtDisplay::init(void)
{
	_device = irr::createDevice(
		irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(
			IrrlichtDisplayConst::SCREEN_X,
			IrrlichtDisplayConst::SCREEN_Y
		),
		IrrlichtDisplayConst::FPS
	);
	if (!_device)
		return false;
	_device->setEventReceiver(&_receiver);
	_driver = _device->getVideoDriver();
	if (!_driver)
		return false;
	_sceneManager = _device->getSceneManager();
	if (!_sceneManager
		|| !this->initTexture()
		|| !this->create_sky(0))
		//|| !this->create_camera()
		return false;
	_device->getCursorControl()->setVisible(true);
	_isInit = true;
	return true;
}

void	IrrlichtDisplay::loop(void)
{
	if (!_device || !_device->run())
		return;
	if (_rotateCamera && _cameraRotationClock.timeSinceMark() > 1)
	{
		_cameraRotationClock.mark();
		_cameraRotationDegrees += 0.095;
		if (_cameraRotationDegrees > 360)
			_cameraRotationDegrees = 0;
	}
	for (auto it = _players.begin(); it != _players.end();)
	{
		auto & player = it->second;
		player->loop();
		if (player->isDead())
		{
			for (auto idxIt = _idxPlayers.begin(); idxIt != _idxPlayers.end();)
			{
				if (*idxIt == (int)player->getId())
				{
					idxIt = _idxPlayers.erase(idxIt);
				}
				else
				{
					++idxIt;
				}
			}
			it = _players.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (_cursor)
	{
		if (doesPlayerExist(_followCam))
		{
			auto player = getPlayer(_followCam);
			_cursor->setPosition(player->getPosMesh() + irr::core::vector3df(0, IrrlichtDisplayConst::CURSOR_INC_Y, 0));
		}
		else
		{
			removePlayerCursor();
		}
	}
}

void IrrlichtDisplay::deinit(void)
{
	_map.clear();
	_players.clear();
	_eggs.clear();
	_teams.clear();
	if (_device)
	{
		_device->drop();
		_device = nullptr;
	}
}

bool	IrrlichtDisplay::initTexture()
{
	_texture[IrrlichtDisplayConst::TEXTURE_BASE_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_BASE);
	_texture[IrrlichtDisplayConst::IRON_BOX_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::IRON_BOX);
	_texture[IrrlichtDisplayConst::GRASS_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::GRASS);
	_texture[IrrlichtDisplayConst::PURPLE_GEM_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::PURPLE_GEM);
	_texture[IrrlichtDisplayConst::PINK_GEM_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::PINK_GEM);
	_texture[IrrlichtDisplayConst::RED_GEM_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::RED_GEM);
	_texture[IrrlichtDisplayConst::GREEN_GEM_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::GREEN_GEM);
	_texture[IrrlichtDisplayConst::YELLOW_GEM_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::YELLOW_GEM);
	_texture[IrrlichtDisplayConst::BLUE_GEM_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::BLUE_GEM);
	_texture[IrrlichtDisplayConst::YOSHI_EGG_RED_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_YOSHI_EGG_RED);
	_texture[IrrlichtDisplayConst::YOSHI_EGG_BLUE_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_YOSHI_EGG_BLUE);
	_texture[IrrlichtDisplayConst::YOSHI_EGG_GREEN_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_YOSHI_EGG_GREEN);
	_texture[IrrlichtDisplayConst::YOSHI_EGG_YELLOW_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_YOSHI_EGG_YELLOW);
	_texture[IrrlichtDisplayConst::YOSHI_EGG_BROWN_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_YOSHI_EGG_BROWN);
	for (size_t i = 0; i < sizeof(IrrlichtDisplayConst::FOODS) / sizeof(*IrrlichtDisplayConst::FOODS); ++i)
	{
		auto const & food = IrrlichtDisplayConst::FOODS[i];
		_texture[food.idx] = this->_driver->getTexture(food.base);
	}
	_texture[IrrlichtDisplayConst::TEXTURE_PERSO_RED_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_PERSO_RED);
	_texture[IrrlichtDisplayConst::TEXTURE_PERSO_BLUE_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_PERSO_BLUE);
	_texture[IrrlichtDisplayConst::TEXTURE_PERSO_GREEN_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_PERSO_GREEN);
	_texture[IrrlichtDisplayConst::TEXTURE_PERSO_YELLOW_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_PERSO_YELLOW);
	_texture[IrrlichtDisplayConst::TEXTURE_PERSO_BROWN_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_PERSO_BROWN);
	_texture[IrrlichtDisplayConst::SKY_UP_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_UP);
	_texture[IrrlichtDisplayConst::SKY_DOWN_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_DOWN);
	_texture[IrrlichtDisplayConst::SKY_LEFT_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_LEFT);
	_texture[IrrlichtDisplayConst::SKY_RIGHT_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_RIGHT);
	_texture[IrrlichtDisplayConst::SKY_FORWARD_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_FORWARD);
	_texture[IrrlichtDisplayConst::SKY_BACKWARD_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_BACKWARD);
	_texture[IrrlichtDisplayConst::SKY_UP1_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_UP1);
	_texture[IrrlichtDisplayConst::SKY_DOWN1_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_DOWN1);
	_texture[IrrlichtDisplayConst::SKY_LEFT1_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_LEFT1);
	_texture[IrrlichtDisplayConst::SKY_RIGHT1_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_RIGHT1);
	_texture[IrrlichtDisplayConst::SKY_FORWARD1_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_FORWARD1);
	_texture[IrrlichtDisplayConst::SKY_BACKWARD1_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_BACKWARD1);
	_texture[IrrlichtDisplayConst::SKY_UP2_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_UP2);
	_texture[IrrlichtDisplayConst::SKY_DOWN2_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_DOWN2);
	_texture[IrrlichtDisplayConst::SKY_LEFT2_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_LEFT2);
	_texture[IrrlichtDisplayConst::SKY_RIGHT2_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_RIGHT2);
	_texture[IrrlichtDisplayConst::SKY_FORWARD2_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_FORWARD2);
	_texture[IrrlichtDisplayConst::SKY_BACKWARD2_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_BACKWARD2);
	_texture[IrrlichtDisplayConst::SKY_UP3_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_UP3);
	_texture[IrrlichtDisplayConst::SKY_DOWN3_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_DOWN3);
	_texture[IrrlichtDisplayConst::SKY_LEFT3_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_LEFT3);
	_texture[IrrlichtDisplayConst::SKY_RIGHT3_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_RIGHT3);
	_texture[IrrlichtDisplayConst::SKY_FORWARD3_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_FORWARD3);
	_texture[IrrlichtDisplayConst::SKY_BACKWARD3_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_BACKWARD3);
	_texture[IrrlichtDisplayConst::SKY_UP4_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_UP4);
	_texture[IrrlichtDisplayConst::SKY_DOWN4_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_DOWN4);
	_texture[IrrlichtDisplayConst::SKY_LEFT4_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_LEFT4);
	_texture[IrrlichtDisplayConst::SKY_RIGHT4_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_RIGHT4);
	_texture[IrrlichtDisplayConst::SKY_FORWARD4_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_FORWARD4);
	_texture[IrrlichtDisplayConst::SKY_BACKWARD4_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::SKY_BACKWARD4);
	_texture[IrrlichtDisplayConst::PARTICLE_WHITE_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::PARTICLE_WHITE);
	_texture[IrrlichtDisplayConst::CURSOR_TEXTURE_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::CURSOR_TEXTURE);
	for (auto const & pair : _texture)
	{
		auto const & texture = pair.second;
		if (texture == nullptr) {
			std::cerr << "Error loading texture : " << pair.first << std::endl;
			return false;
		}
	}
	return true;
}

void IrrlichtDisplay::setMapSize(Point const &size)
{
	_map.clear();
	for (int y = 0; y < size.getY(); ++y) {
		_map.push_back({});
		for (int x = 0; x < size.getX(); ++x) {
			auto node = create_block(
				IrrlichtDisplayConst::IRON_BOX_IDX,
				getCenterPos({x, y}, IrrlichtDisplayConst::BLOCK_Z),
				IrrlichtDisplayConst::BLOCK_SCALE
			);
			auto content = std::make_shared<MapContent>(node);
			_map[y].push_back(content);
		}
	}
}

int	IrrlichtDisplay::getTeamClicked(std::list<int> idxPlayers)
{
	if (!_receiver.isMouseClick()
		|| !_camera
		|| _antiSpamCam.timeSinceMark() <= 100) {
		return (IrrlichtDisplayConst::NOT_CLICKED);
	}
	_antiSpamCam.mark();
	auto pos = _device->getCursorControl()->getPosition();
	auto node = _sceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(pos);
	auto posNode = node->getPosition();
	
	for (auto it = idxPlayers.begin(); it != idxPlayers.end(); ++it)
	{
		if (!doesPlayerExist(*it)) {
			continue;
		}
		auto player = getPlayer(*it);
		auto posPlayer = player->getPosMesh();
		if (posNode.X == posPlayer.X && posNode.Z == posPlayer.Z && posNode.Z == posPlayer.Z) {
			_followCam = *it;
			setPlayerCursor(_followCam);
			return (*it);
		}
	}
	removePlayerCursor();
	_followCam = IrrlichtDisplayConst::CLICK_ON_MAP;
	return (IrrlichtDisplayConst::CLICK_ON_MAP);
}

int		IrrlichtDisplay::getIdPlayerFollowCam(void) const
{
	return (_followCam);
}

void	IrrlichtDisplay::manageEvent()
{
	if (_receiver.IsKeyDown(irr::KEY_KEY_W))
		_zoomCam -= 5;
	else if(_receiver.IsKeyDown(irr::KEY_KEY_S))
		_zoomCam += 5;
}

void	IrrlichtDisplay::setCameraPos(Point const & size)
{
	Point mapSize = (size + 1) * IrrlichtDisplayConst::SIZE_MAP_TILE;
	Point mapCenter = mapSize / 2;
	float distance = std::max(mapSize.x(), mapSize.y()) * 0.8;
	// float distance = _zoomCam;
	float height = distance;
	setCamera(
		distance,
		height,
		{ (float)mapCenter.x(), 0, (float)mapCenter.y() }
	);
}

void	IrrlichtDisplay::setCamera(
	float distance,
	float height,
	irr::core::vector3df const & target
)
{
	_cameraTarget = target;
	_cameraPosition = _cameraTarget;
	_cameraPosition.X += distance;
	_cameraPosition.Y += height;
	if (_rotateCamera)
	{
		auto rotation = rotatePoint(
			{ _cameraTarget.X, _cameraTarget.Z },
			_cameraRotationDegrees,
			{ _cameraPosition.X, _cameraPosition.Z }
		);
		_cameraPosition.X = rotation.X;
		_cameraPosition.Z = rotation.Y;
	}
	if (!_camera)
	{
		_camera = _sceneManager->addCameraSceneNode(0, _cameraPosition, _cameraTarget);
	}
	else
	{
		_camera->setPosition(_cameraPosition);
		_camera->setTarget(_cameraTarget);
	}
}

void	IrrlichtDisplay::setCameraOnPlayer(int id)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		setCamera(_zoomCam, _zoomCam, player->getPosMesh());
	}
}

irr::scene::ISceneNode *IrrlichtDisplay::create_block(
		int texture,
		irr::core::vector3df pos,
		irr::core::vector3df scale
) {
	irr::scene::ISceneNode *block = _sceneManager->addCubeSceneNode();
	block->setPosition(pos);
	block->setScale(scale);
	block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	block->setMaterialTexture(0, _texture[texture]);
	return block;
}

void IrrlichtDisplay::setTeams(std::vector<std::string> const &teams) {
	_teams.clear();
	int idx = 0;
	for (auto const & team : teams)
	{
		_teams.push_back(std::make_shared<Team>(idx, team));
		++idx;
	}
}

void IrrlichtDisplay::setTimeUnit(double unit)
{
	_timeUnit = unit;
	for (auto const & pair : _players)
	{
		auto & player = pair.second;
		player->setDurationMillis(getMovementDuration(), _timeUnit);
	}
}

void IrrlichtDisplay::display(std::shared_ptr<GUI> gui)
{
	this->manageEvent();
	this->getTeamClicked(_idxPlayers);
	this->manageCam();
	if (_isInit && _device && _device->run())
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 135, 206, 235));
		_sceneManager->drawAll();
		gui->isButtonPressed();
		gui->draw();
		_driver->endScene();
	}
}

void	IrrlichtDisplay::manageCam()
{
	if (_followCam == IrrlichtDisplayConst::CLICK_ON_MAP && _map.size() > 0) {
		this->setCameraPos({static_cast<int>(_map.size()), static_cast<int>(_map[0].size())});
	} else if (_followCam > 0) {
		this->setCameraOnPlayer(_followCam);
	}
}

void	IrrlichtDisplay::setFoodTile(
	std::shared_ptr<MapContent> & m,
	Point const &pos,
	Map::MapCase const & content
)
{
	int before = m->foods().size();
	int after = content._food;
	while (before < after)
	{
		auto const & food = getRandomFood();
		m->foods().push_back(
			std::make_shared<Food>(
				create_mesh(
					food.idx,
					getRandomPos(pos, food.z),
					food.scale,
					food.mesh
				)
			)
		);
		++before;
	}
	while (before > after && !m->foods().empty())
	{
		m->foods().erase(m->foods().begin());
		--before;
	}
}

void	IrrlichtDisplay::setStoneTile(
	std::shared_ptr<MapContent> & m,
	Point const &pos,
	int textureIdx,
	AStone::Type type,
	int nbAfter
)
{
	int before = 0;
	for (auto const & stone : m->stones())
	{
		before += (*stone == type);
	}
	while (before < nbAfter)
	{
		m->stones().push_back(
			std::make_shared<AStone>(
				create_gem(
					textureIdx,
					getRandomPos(pos, IrrlichtDisplayConst::STONE_Z),
					IrrlichtDisplayConst::STONE_SCALE
				),
				type
			)
		);
		++before;
	}
	while (before > nbAfter)
	{
		auto it = std::find_if(m->stones().begin(), m->stones().end(),
			[type](auto const & stone)
			{
				return *stone == type;
			}
		);
		if (it == m->stones().end())
			break;
		m->stones().erase(it);
		--before;
	}
}

void	IrrlichtDisplay::setStonesTile(
	std::shared_ptr<MapContent> & m,
	Point const &pos,
	Map::MapCase const & content
)
{
	setStoneTile(m, pos, IrrlichtDisplayConst::PURPLE_GEM_IDX, AStone::Type::S1, content._stone1);
	setStoneTile(m, pos, IrrlichtDisplayConst::RED_GEM_IDX, AStone::Type::S2, content._stone2);
	setStoneTile(m, pos, IrrlichtDisplayConst::YELLOW_GEM_IDX, AStone::Type::S3, content._stone3);
	setStoneTile(m, pos, IrrlichtDisplayConst::PINK_GEM_IDX, AStone::Type::S4, content._stone4);
	setStoneTile(m, pos, IrrlichtDisplayConst::GREEN_GEM_IDX, AStone::Type::S5, content._stone5);
	setStoneTile(m, pos, IrrlichtDisplayConst::BLUE_GEM_IDX, AStone::Type::S6, content._stone6);
}

void IrrlichtDisplay::setMapTile(Point const &pos, Map::MapCase const &content)
{
	if (doesMapContentExist(pos))
	{
		auto tile = getMapContent(pos);
		setFoodTile(tile, pos, content);
		setStonesTile(tile, pos, content);
	}
}

int	IrrlichtDisplay::random_pos()
{
	int pos = rand() % (IrrlichtDisplayConst::SIZE_MAP_TILE / 2);
	return (rand() & 1 ? -pos : pos);
}

int IrrlichtDisplay::getRotationDegrees(Direction const & dir)
{
	return dir == Direction::Up ? 0 : dir == Direction::Left ? 90 : dir == Direction::Right ? 270 : 180;
}

void	IrrlichtDisplay::addPlayer(
	size_t id,
	Point const &pos,
	Direction const &dir,
	size_t level,
	std::string const &team,
	const IDisplay::PlayerOrigin &origin
)
{
	killPlayer(id);
	_idxPlayers.push_back(id);
	_players[id] = std::make_shared<Player>(
		id, pos, dir, level, getTeamIdx(team),
		origin, getMovementDuration(), _timeUnit,
		*_sceneManager, _texture
	);
}

void IrrlichtDisplay::killPlayer(size_t id)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		player->kill();
	}
}

void IrrlichtDisplay::movePlayer(size_t id, Point const &to)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		player->moveTo(to);
	}
}

void IrrlichtDisplay::pushPlayer(size_t id, Point const &to, Direction const & dir)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		player->pushTo(to, dir);
	}
}

void IrrlichtDisplay::setPlayerLevel(size_t id, size_t level)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		player->setLevel(level);
	}
}

void	IrrlichtDisplay::changePlayerDir(size_t id, Direction const & dir)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		player->setDir(dir);
	}
}

void IrrlichtDisplay::addEgg(size_t idEgg, size_t idPlayerFrom)
{
	removeEgg(idEgg);
	if (doesPlayerExist(idPlayerFrom))
	{
		auto const & player = getPlayer(idPlayerFrom);
		auto const & pos = player->getPos();
		_eggs[idEgg] = std::make_shared<Egg>(
			idEgg,
			player->getTeamIdx(),
			player->getPos(),
			/*create_egg(
					IrrlichtDisplayConst::YOSHI_EGG_IDX,
					getRandomPos(pos, IrrlichtDisplayConst::EGG_Z),
					IrrlichtDisplayConst::EGG_SCALE
			)*/
			_driver,
			*_sceneManager,
			_texture
		);
	}
}

void IrrlichtDisplay::removeEgg(size_t id)
{
	auto old_eggs = _eggs.find(id);
	if (old_eggs != _eggs.end())
	{
		_eggs.erase(old_eggs);
	}
}

void IrrlichtDisplay::setPlayerAction(size_t id, IDisplay::PlayerAnimationStyle const & what)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		player->animate(what);
	}
}

irr::scene::IMeshSceneNode *IrrlichtDisplay::create_gem(
	int texture,
	irr::core::vector3df pos,
	irr::core::vector3df scale
)
{
	return (create_mesh(texture, pos, scale, IrrlichtDisplayConst::GEM_MESH));
}

irr::scene::IMeshSceneNode *	IrrlichtDisplay::create_egg(
		int texture,
		irr::core::vector3df pos,
		irr::core::vector3df scale
)
{
	return (create_mesh(texture, pos, scale, IrrlichtDisplayConst::EGG_MESH));
}

irr::scene::IMeshSceneNode *IrrlichtDisplay::create_mesh(
	int texture,
	irr::core::vector3df pos,
	irr::core::vector3df scale,
	const irr::io::path &filename
)
{
	irr::scene::IAnimatedMesh * mesh =_sceneManager->getMesh(filename);
	if (mesh == nullptr)
		return nullptr;
	auto my_mesh = _sceneManager->addMeshSceneNode(mesh->getMesh(0));
	my_mesh->setPosition(pos);
	my_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	my_mesh->setScale(scale);
	my_mesh->setMaterialTexture(0, _texture[texture]);
	return (my_mesh);
}

irr::scene::ICameraSceneNode *IrrlichtDisplay::create_camera()
{
	 irr::SKeyMap keyMap[5];                             // re-assigne les commandes
	 keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
	 keyMap[0].KeyCode = irr::KEY_KEY_Z;                 // w
	 keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
	 keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s
	 keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
	 keyMap[2].KeyCode = irr::KEY_KEY_Q;                 // a
	 keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
	 keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
	 keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
	 keyMap[4].KeyCode = irr::KEY_SPACE;                 // barre espace
	_camera = _sceneManager->addCameraSceneNodeFPS(0, 1.0 , 1.0f, -1, keyMap, 5);
	return (_camera);
}

bool IrrlichtDisplay::create_sky(int idSkyBox)
{
	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
	idSkyBox %= 5;
	if (idSkyBox == 0) {
		_sceneManager->addSkyBoxSceneNode(
			_texture[IrrlichtDisplayConst::SKY_UP_IDX],
			_texture[IrrlichtDisplayConst::SKY_DOWN_IDX],
			_texture[IrrlichtDisplayConst::SKY_LEFT_IDX],
			_texture[IrrlichtDisplayConst::SKY_RIGHT_IDX],
			_texture[IrrlichtDisplayConst::SKY_FORWARD_IDX],
			_texture[IrrlichtDisplayConst::SKY_BACKWARD_IDX]
		);
	} else if (idSkyBox == 1) {
		_sceneManager->addSkyBoxSceneNode(
			_texture[IrrlichtDisplayConst::SKY_UP1_IDX],
			_texture[IrrlichtDisplayConst::SKY_DOWN1_IDX],
			_texture[IrrlichtDisplayConst::SKY_LEFT1_IDX],
			_texture[IrrlichtDisplayConst::SKY_RIGHT1_IDX],
			_texture[IrrlichtDisplayConst::SKY_FORWARD1_IDX],
			_texture[IrrlichtDisplayConst::SKY_BACKWARD1_IDX]
		);
	} else if (idSkyBox == 2) {
		_sceneManager->addSkyBoxSceneNode(
			_texture[IrrlichtDisplayConst::SKY_UP2_IDX],
			_texture[IrrlichtDisplayConst::SKY_DOWN2_IDX],
			_texture[IrrlichtDisplayConst::SKY_LEFT2_IDX],
			_texture[IrrlichtDisplayConst::SKY_RIGHT2_IDX],
			_texture[IrrlichtDisplayConst::SKY_FORWARD2_IDX],
			_texture[IrrlichtDisplayConst::SKY_BACKWARD2_IDX]
		);
	} else if (idSkyBox == 3) {
		_sceneManager->addSkyBoxSceneNode(
			_texture[IrrlichtDisplayConst::SKY_UP3_IDX],
			_texture[IrrlichtDisplayConst::SKY_DOWN3_IDX],
			_texture[IrrlichtDisplayConst::SKY_LEFT3_IDX],
			_texture[IrrlichtDisplayConst::SKY_RIGHT3_IDX],
			_texture[IrrlichtDisplayConst::SKY_FORWARD3_IDX],
			_texture[IrrlichtDisplayConst::SKY_BACKWARD3_IDX]
		);
	} else if (idSkyBox == 4) {
		_sceneManager->addSkyBoxSceneNode(
			_texture[IrrlichtDisplayConst::SKY_UP4_IDX],
			_texture[IrrlichtDisplayConst::SKY_DOWN4_IDX],
			_texture[IrrlichtDisplayConst::SKY_LEFT4_IDX],
			_texture[IrrlichtDisplayConst::SKY_RIGHT4_IDX],
			_texture[IrrlichtDisplayConst::SKY_FORWARD4_IDX],
			_texture[IrrlichtDisplayConst::SKY_BACKWARD4_IDX]
		);
	}
	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
	return true;
}

bool	IrrlichtDisplay::isDeviceRunning(void)
{
	return (this->_device->run());
}

irr::IrrlichtDevice		*IrrlichtDisplay::getDevice(void) const
{
	return _device;
}

irr::video::IVideoDriver	*IrrlichtDisplay::getDriver(void) const
{
	return _driver;
}

long long	IrrlichtDisplay::getMovementDuration(void) const noexcept
{
	return _timeUnit == 0 ? 0 : 1.0 / _timeUnit * 1E3;
}

int	IrrlichtDisplay::getTeamIdx(std::string const & name) const noexcept
{
	for (auto const & team : _teams)
	{
		if (*team.get() == name)
		{
			return team->getIdx();
		}
	}
	return -1;
}

void	IrrlichtDisplay::setPlayerCursor(size_t playerId)
{
	if (doesPlayerExist(playerId))
	{
		auto player = getPlayer(playerId);
		removePlayerCursor();
		irr::scene::IAnimatedMesh * mesh =_sceneManager->getMesh(IrrlichtDisplayConst::CURSOR);
		if (mesh)
		{
			_cursor = _sceneManager->addMeshSceneNode(mesh->getMesh(0));
			_cursor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_cursor->setScale(IrrlichtDisplayConst::CURSOR_SCALE);
			_cursor->setMaterialTexture(0, _texture[IrrlichtDisplayConst::CURSOR_TEXTURE_IDX]);
			irr::scene::ISceneNodeAnimator * ani = _sceneManager->createRotationAnimator({ 0, 1, 0 });
			_cursor->addAnimator(ani);
			ani->drop();
		}
	}
}

void	IrrlichtDisplay::removePlayerCursor()
{
	if (_cursor)
	{
		_cursor->remove();
		_cursor = nullptr;
	}
}

void	IrrlichtDisplay::remove_block(irr::scene::ISceneNode * node)
{
	node->remove();
}

void	IrrlichtDisplay::remove_mesh(
	__attribute__((unused))irr::scene::IMeshSceneNode * mesh)
{}

bool	IrrlichtDisplay::doesPlayerExist(size_t id) const noexcept
{
	return _players.find(id) != _players.end();
}

bool	IrrlichtDisplay::doesEggExist(size_t id) const noexcept
{
	return _eggs.find(id) != _eggs.end();
}

std::shared_ptr<IrrlichtDisplay::Player>	IrrlichtDisplay::getPlayer(size_t id) noexcept
{
	return _players[id];
}

std::shared_ptr<IrrlichtDisplay::Egg>	IrrlichtDisplay::getEgg(size_t id) noexcept
{
	return _eggs[id];
}

irr::core::vector3df	IrrlichtDisplay::getRandomPos(Point mapPos, float z)
{
	mapPos = (mapPos + 1) * 50 + Point(random_pos(), random_pos());
	return { (float)mapPos.getX(), z, (float)mapPos.getY() };
}

irr::core::vector3df	IrrlichtDisplay::getCenterPos(Point mapPos, float z)
{
	mapPos = (mapPos + 1) * 50;
	return { (float)mapPos.getX(), z, (float)mapPos.getY() };
}

irr::core::vector3df	IrrlichtDisplay::moveVector(
	irr::core::vector3df from,
	Direction const & dir,
	float inc
)
{
	if (dir == Direction::Dir_t::Left)
		from.X -= inc;
	else if (dir == Direction::Dir_t::Right)
		from.X += inc;
	else if (dir == Direction::Dir_t::Up)
		from.Z -= inc;
	else if (dir == Direction::Dir_t::Down)
		from.Z += inc;
	return from;
}

irr::core::vector2df	IrrlichtDisplay::rotatePoint(
	irr::core::vector2df const & center,
	double angle,
	irr::core::vector2df point
)
{
	angle = angle * M_PI / 180.0;
	double s = sin(angle);
	double c = cos(angle);
	point.X -= center.X;
	point.Y -= center.Y;
	double x_rot = point.X * c - point.Y * s;
	double y_rot = point.X * s + point.Y * c;
	point.X = x_rot + center.X;
	point.Y = y_rot + center.Y;
	return point;
}

IrrlichtDisplayConst::FoodTexture	IrrlichtDisplay::getRandomFood(void)
{
	int max = sizeof(IrrlichtDisplayConst::FOODS) / sizeof(*IrrlichtDisplayConst::FOODS);
	int r = Math::randomNumberBetween(0, max - 1);
	return IrrlichtDisplayConst::FOODS[r];
}

bool	IrrlichtDisplay::doesMapContentExist(Point const & pos) const noexcept
{
	int x = pos.getX();
	int y = pos.getY();
	return !(y < 0 || y >= (int)_map.size() || x < 0 || x > (int)_map[y].size());
}

std::shared_ptr<IrrlichtDisplay::MapContent>	IrrlichtDisplay::getMapContent(Point const & pos) noexcept
{
	return _map[pos.getY()][pos.getX()];
}

////////////////////////////////////// eggg/////////////////////////////////
IrrlichtDisplay::Egg::Egg(size_t id, int teamIdx,
						  Point const & pos, irr::video::IVideoDriver * _driver,
						  irr::scene::ISceneManager & sceneManager,
						  std::map<int, irr::video::ITexture *> & textures)
		:	_id(id)
		,	_pos(pos)
		,	_mesh(nullptr)
		,	_driver(_driver)
		,	_sceneManager(sceneManager)
		,	_textures(textures)
		,	_fx_egg(nullptr)
		,	_teamIdx(teamIdx)
{
	positionNode(_pos);
	create_fx(_meshPos, IrrlichtDisplayConst::EGG_FX_SCALE);
	change_texture(IrrlichtDisplayConst::EGG_MESH);
}

void IrrlichtDisplay::Egg::positionNode(Point const & pos) {
	_meshPos = IrrlichtDisplay::getRandomPos(pos, IrrlichtDisplayConst::EGG_Z);
}
void IrrlichtDisplay::Egg::change_texture(irr::io::path const &path) {
	if (_mesh)
	{
		_mesh->remove();
	}
	_mesh = nullptr;
	auto *mesh = _sceneManager.getMesh(path);
	 if (mesh) {
		 _mesh = _sceneManager.addMeshSceneNode(mesh);
		 if (_mesh) {
			 _mesh->setPosition(_meshPos);
			 _mesh->setScale(IrrlichtDisplayConst::EGG_SCALE);
			 _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			if (_teamIdx == 0)
				_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::YOSHI_EGG_RED_IDX]);
			else if (_teamIdx == 1)
				_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::YOSHI_EGG_BLUE_IDX]);
			else if (_teamIdx == 2)
				_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::YOSHI_EGG_GREEN_IDX]);
			else if (_teamIdx == 3)
				_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::YOSHI_EGG_YELLOW_IDX]);
			else
				_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::YOSHI_EGG_BROWN_IDX]);
		 }
	 }
}

void IrrlichtDisplay::Egg::create_fx(irr::core::vector3df pos, irr::core::vector3df scale) {

	if (_fx_egg)
	{
		_fx_egg->remove();
		_fx_egg = nullptr;
	}
	_fx_egg = _sceneManager.addVolumeLightSceneNode(0, -1, 32, 32, irr::video::SColor(0, 255, 255, 255), irr::video::SColor(0, 0, 0, 0));
	if (_fx_egg)
	{
		_fx_egg->setScale(scale);
		_fx_egg->setPosition(pos);
		irr::core::array<irr::video::ITexture*> textures;

		for (irr::s32 g=7; g > 0; --g)
		{
			irr::core::stringc tmp;
			tmp = "./Ress/model/portal";
			tmp += g;
			tmp += ".bmp";
			irr::video::ITexture* t = _driver->getTexture(tmp.c_str());
			textures.push_back(t);
		}
		// create texture animator
		irr::scene::ISceneNodeAnimator* glow = _sceneManager.createTextureAnimator(textures, 150);
		_fx_egg->addAnimator(glow);
		glow->drop();
	}
}

///////egggggggg/////////////

////particule///

void		created_fire(float x, float y, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager)
{
	irr::scene::IParticleSystemSceneNode* ps =
			sceneManager->addParticleSystemSceneNode(false);

	irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-10,0,-10,10,1,10), // emitter size
			irr::core::vector3df(0.0f,0.06f,0.0f),   // initial direction
			25, 40,                             // emit rate
			irr::video::SColor(0,255,255,255),       // darkest color
			irr::video::SColor(0,255,255,255),       // brightest color
			800,1500,30,                         // min and max age, angle
			irr::core::dimension2df(10.f,10.f),         // min size
			irr::core::dimension2df(20.f,20.f));        // max size

	ps->setEmitter(em); // this grabs the emitter
	em->drop(); // so we can drop it here without deleting it

	irr::scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

	ps->addAffector(paf); // same goes for the affector
	paf->drop();

	ps->setPosition(irr::core::vector3df(x, 27.5, y));
	ps->setScale(irr::core::vector3df(2,2,2));
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("./Ress/model/particlewhite.bmp"));
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

/////particule ////
