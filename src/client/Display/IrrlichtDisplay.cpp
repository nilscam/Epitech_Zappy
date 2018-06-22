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
		|| !this->create_sky()
		//|| !this->create_camera()
		|| !this->initTexture())
		return false;
	_device->getCursorControl()->setVisible(true);
	_isInit = true;
	return true;
}

void	IrrlichtDisplay::loop(void)
{
	if (_device && _device->run())
	{
		for (auto const & pair : _players)
		{
			auto & player = pair.second;
			player->loop();
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
	_texture[IrrlichtDisplayConst::YOSHI_EGG_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::YOSHI_EGG);
	_texture[IrrlichtDisplayConst::FOOD_BASE_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::FOOD_BASE);
	_texture[IrrlichtDisplayConst::TEXTURE_PERSO_IDX] = this->_driver->getTexture(IrrlichtDisplayConst::TEXTURE_PERSO);
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
			return (*it);
		}
	}
	_followCam = IrrlichtDisplayConst::CLICK_ON_MAP;
	return (IrrlichtDisplayConst::CLICK_ON_MAP);
}

void	IrrlichtDisplay::setCameraPos(Point const & size)
{
	float cameraX = (size.x() + 1) * IrrlichtDisplayConst::SIZE_MAP_TILE / 10;
	float cameraY = (size.y() + 1) * IrrlichtDisplayConst::SIZE_MAP_TILE / 2;
	float cameraZ = std::max(cameraX, cameraY) * 2;

	if (!_camera) {
		_camera = _sceneManager->addCameraSceneNode(0, {cameraX - 400, cameraZ, cameraY}, { cameraX, 0, cameraY });
		return;
	}
	_camera->setPosition(irr::core::vector3df(cameraX - 400, cameraZ, cameraY));
	_camera->setTarget({ cameraX, 0, cameraY });
}

void	IrrlichtDisplay::setCameraOnPlayer(int id)
{
	if (!doesPlayerExist(id)) {
		return;
	}
	auto player = getPlayer(id);
	//Point posPlayer = player->getPos();
	auto posPlayer = player->getPosMesh();
	int movex = posPlayer.X;
    int movey = posPlayer.Z;

    //int permove = myPlayer.isMoving() ? static_cast<int>(myPlayer.getMovementPercentage()) / 2 : 0;
    // int movex = (posPlayer.x() + 1) * 50;
    // int movey = (posPlayer.y() + 1) * 50;
	// std::cout << "movex:" << movex << " movey:" << movey << std::endl;
	// std::cout << "vecx:" << vec.X << " vecy:" << vec.Y << " vecz:" << vec.Z << std::endl << std::endl;
    // Direction::Dir_t dir = myPlayer.getCurrentDir().getDir();
    // switch (dir) {
    //     case Direction::Left:
    //         movex -= permove;
    //         break;
    //     case Direction::Right:
    //         movex += permove;
    //         break;
    //     case Direction::Up:
    //         movey -= permove;
    //         break;
    //     case Direction::Down:
    //         movey += permove;
    //         break;
    //     default:
    //         break;
    // }
    irr::core::vector3df position(movex, 0, movey);

    float cameraX = position.X;
    float cameraY = position.Z;
    float cameraZ = 250;
	if (!_camera) {
		_camera = _sceneManager->addCameraSceneNode(0, {cameraX - 350, cameraZ, cameraY}, { cameraX, 0, cameraY });
		return;
	}
	_camera->setPosition(irr::core::vector3df(cameraX - 300, cameraZ, cameraY));
    _camera->setTarget({ cameraX, 0, cameraY });
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
	for (auto const & team : teams)
	{
		_teams.push_back(std::make_shared<Team>(team));
	}
}

void IrrlichtDisplay::setTimeUnit(double unit)
{
	_timeUnit = unit;
}

void IrrlichtDisplay::display(void)
{
	if (_isInit && _device && _device->run())
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 135, 206, 235));
		_sceneManager->drawAll();
		_driver->endScene();
	}
}

void IrrlichtDisplay::display(std::shared_ptr<GUI> gui)
{
	this->manageCam();
	if (_isInit && _device && _device->run())
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 135, 206, 235));
		_sceneManager->drawAll();
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
		m->foods().push_back(
			std::make_shared<Food>(
				create_food(
						IrrlichtDisplayConst::FOOD_BASE_IDX,
					getRandomPos(pos, IrrlichtDisplayConst::FOOD_Z),
					IrrlichtDisplayConst::FOOD_SCALE
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

irr::scene::IAnimatedMeshSceneNode *IrrlichtDisplay::create_player(
		irr::core::vector3df pos, irr::core::vector3df scale, int idxtexture)
{
	auto * mesh = _sceneManager->getMesh(IrrlichtDisplayConst::PERSO);
	if (!mesh)
		return nullptr;
	auto * animatedMesh = _sceneManager->addAnimatedMeshSceneNode(mesh);
	if (!animatedMesh)
		return nullptr;
	animatedMesh->setPosition(pos);
	animatedMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	animatedMesh->setScale(scale);
	animatedMesh->setMaterialTexture(0, _texture[idxtexture]);
	return (animatedMesh);
}

int	IrrlichtDisplay::random_pos()
{
	int pos = rand() % 20;
	if (rand() & 1) {
		return -pos;
	}
	return (pos);
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
	__attribute__((unused)) std::string const &team,
	__attribute__((unused)) const IDisplay::PlayerOrigin &origin
)
{
	killPlayer(id);
	_players[id] = std::make_shared<Player>(
		id, pos, dir, level,
		create_player(
				getCenterPos(pos, IrrlichtDisplayConst::PLAYER_Z),
				IrrlichtDisplayConst::PLAYER_SCALE,
				IrrlichtDisplayConst::TEXTURE_PERSO_IDX
		)
	);
	auto npos = _players[id]->getPosMesh();
	std::cout << "POS PERSO:" << npos.X << " | " << npos.Y << " | " << npos.Z << std::endl;
}

void IrrlichtDisplay::killPlayer(size_t id)
{
	auto oldPlayer = _players.find(id);
	if (oldPlayer != _players.end())
	{
		_players.erase(oldPlayer);
	}
}

void IrrlichtDisplay::movePlayer(
	size_t id,
	Point const &to,
	__attribute__((unused)) const IDisplay::PlayerMoveStyle &how
)
{
	if (doesPlayerExist(id))
	{
		auto player = getPlayer(id);
		player->setPos(to, getMovementDuration());
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
			player->getPos(),
			create_egg(
					IrrlichtDisplayConst::YOSHI_EGG_IDX,
					getRandomPos(pos, IrrlichtDisplayConst::EGG_Z),
					IrrlichtDisplayConst::EGG_SCALE
			)
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

void IrrlichtDisplay::setPlayerAction(
	__attribute__((unused)) size_t id,
	__attribute__((unused)) IDisplay::PlayerAnimationStyle const & what
)
{
	if (doesPlayerExist(id))
	{
		// todo animate player
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

irr::scene::IMeshSceneNode *IrrlichtDisplay::create_food(
	int texture,
	irr::core::vector3df pos,
	irr::core::vector3df scale
)
{
	return (create_mesh(texture, pos, scale, IrrlichtDisplayConst::FOOD_MESH));
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
	// irr::SKeyMap keyMap[5];                             // re-assigne les commandes
	// keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
	// keyMap[0].KeyCode = irr::KEY_KEY_Z;                 // w
	// keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
	// keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s
	// keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
	// keyMap[2].KeyCode = irr::KEY_KEY_Q;                 // a
	// keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
	// keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
	// keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
	// keyMap[4].KeyCode = irr::KEY_SPACE;                 // barre espace
	//_camera = _sceneManager->addCameraSceneNodeFPS(0, 1.0 , 1.0f, -1, keyMap, 5);
	return (_camera);
}

bool IrrlichtDisplay::create_sky()
{
	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
	_sceneManager->addSkyBoxSceneNode(
			_driver->getTexture(IrrlichtDisplayConst::SKY_UP),
			_driver->getTexture(IrrlichtDisplayConst::SKY_DOWN),
			_driver->getTexture(IrrlichtDisplayConst::SKY_LEFT),
			_driver->getTexture(IrrlichtDisplayConst::SKY_RIGHT),
			_driver->getTexture(IrrlichtDisplayConst::SKY_FORWARD),
			_driver->getTexture(IrrlichtDisplayConst::SKY_BACKWARD)
	);
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

long long	IrrlichtDisplay::getMovementDuration(void) const noexcept
{
	return _timeUnit == 0 ? 0 : 1.0 / _timeUnit * 1E3;
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
		from.Y -= inc;
	else if (dir == Direction::Dir_t::Down)
		from.Y += inc;
	return from;
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

IrrlichtDisplay::Player::Player(
		size_t id,
		Point const & pos,
		Direction const & dir,
		size_t level,
		irr::scene::IAnimatedMeshSceneNode * node
)
	:	_id(id)
	,	_pos(pos)
	,	_dir(dir)
	,	_level(level)
	,	_node(node)
	,	_isMoving(false)
	,	_movDuration(0)
{
	positionNode(pos);
	rotateNode(dir);
}

IrrlichtDisplay::Player::~Player()
{
	if (_node != nullptr)
	{
		_node->remove();
	}
}

void	IrrlichtDisplay::Player::setPos(Point const & pos, long long movDuration)
{
	if (_pos != pos)
	{
		_pos = pos;
		if (movDuration <= 0)
		{
			_isMoving = false;
			positionNode(pos);
		}
		else
		{
			_isMoving = true;
			_movFrom = _pos;
			_movTo = pos;
			_movDir = Direction(_movFrom, _movTo);
			_movClock.mark();
			_movDuration = movDuration;
		}
	}
}

void	IrrlichtDisplay::Player::setLevel(size_t level)
{
	_level = level;
}

void	IrrlichtDisplay::Player::setDir(Direction const & dir)
{
	_dir = dir;
	rotateNode(dir);
}

Point	IrrlichtDisplay::Player::getPos(void) const noexcept
{
	return _pos;
}

irr::core::vector3df	IrrlichtDisplay::Player::getPosMesh(void) const noexcept
{
	return _node->getPosition();
}

void	IrrlichtDisplay::Player::loop(void)
{
	if (_node && _isMoving)
	{
		long long movMillis = _movClock.timeSinceMark();
		if (movMillis >= _movDuration)
		{
			_isMoving = false;
			positionNode(_movTo);
		}
		else
		{
			double movPercentage = movMillis * 100.0 / _movDuration;
			double maxDistance = IrrlichtDisplayConst::SIZE_MAP_TILE / 2;
			Point movStart;
			double distanceToEnd;
			Direction movDir;
			if (movPercentage <= 50.0)
			{
				movStart = _movFrom;
				distanceToEnd = movPercentage * maxDistance / 50.0;
				movDir = _movDir;
			}
			else
			{
				movStart = _movTo;
				distanceToEnd = maxDistance - ((movPercentage - 50) * maxDistance / 50.0);
				movDir = _movDir.reverse();
			}
			irr::core::vector3df newPos = IrrlichtDisplay::moveVector(
				IrrlichtDisplay::getCenterPos(
					movStart,
					IrrlichtDisplayConst::PLAYER_Z
				),
				movDir,
				Math::clamp(0.0, maxDistance, distanceToEnd)
			);
			_node->setPosition(newPos);
			if (distanceToEnd == maxDistance)
			{
				_isMoving = false;
			}
		}
	}
}

void	IrrlichtDisplay::Player::rotateNode(Direction const & dir)
{
	if (_node)
	{
		_node->setRotation({ 0, (float)IrrlichtDisplay::getRotationDegrees(dir), 0 });
	}
}

void	IrrlichtDisplay::Player::positionNode(Point const & pos)
{
	if (_node)
	{
		_node->setPosition(IrrlichtDisplay::getCenterPos(pos, IrrlichtDisplayConst::PLAYER_Z));
	}
}
