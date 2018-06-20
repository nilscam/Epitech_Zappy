//
// Created by baptiste roubieu on 20/06/2018.
//

#include "IrrlichtDisplay.hpp"

#define TEXTURE_BASE			"../../Ress/model/wood.jpg"
#define IRON_BOX				"../../Ress/model/iron_box.png"
#define GRASS					"../../Ress/model/grass.jpg"
#define PURPLE_GEM				"../../Ress/model/PowerGem/purplegem.png"
#define PINK_GEM				"../../Ress/model/PowerGem/pinkgem.png"
#define RED_GEM					"../../Ress/model/Gem1/Red.png"
#define GREEN_GEM				"../../Ress/model/Gem1/Green.png"
#define	YELLOW_GEM				"../../Ress/model/Gem1/Yellow.png"
#define BLUE_GEM				"../../Ress/model/Gem1/Blue.png"
#define YOSHI_EGG				"../../Ress/model/Egg/YoshSS00.png"

#define TEXTURE_BASE_IDX		0
#define IRON_BOX_IDX			1
#define	GRASS_IDX				2
#define PURPLE_GEM_IDX			3
#define PINK_GEM_IDX			4
#define RED_GEM_IDX			5
#define GREEN_GEM_IDX			6
#define	YELLOW_GEM_IDX			7
#define BLUE_GEM_IDX			8
#define YOSHI_EGG_IDX			9

IrrlichtDisplay::IrrlichtDisplay() = default;

IrrlichtDisplay::~IrrlichtDisplay() = default;

void IrrlichtDisplay::init(void) {
	_device = irr::createDevice(irr::video::EDT_OPENGL,
								irr::core::dimension2d<irr::u32>(1920, 1080), 32);
	_driver = _device->getVideoDriver();
	_sceneManager = _device->getSceneManager();
	_device->getCursorControl()->setVisible(true);
}

void IrrlichtDisplay::deinit(void) {

}
void	IrrlichtDisplay::initTexture()
{
	_texture[TEXTURE_BASE_IDX] = this->_driver->getTexture(TEXTURE_BASE);
	_texture[IRON_BOX_IDX] = this->_driver->getTexture(IRON_BOX);
	_texture[GRASS_IDX] = this->_driver->getTexture(GRASS);
	_texture[PURPLE_GEM_IDX] = this->_driver->getTexture(PURPLE_GEM);
	_texture[PINK_GEM_IDX] = this->_driver->getTexture(PINK_GEM);
	_texture[RED_GEM_IDX] = this->_driver->getTexture(RED_GEM);
	_texture[GREEN_GEM_IDX] = this->_driver->getTexture(GREEN_GEM);
	_texture[YELLOW_GEM_IDX] = this->_driver->getTexture(YELLOW_GEM);
	_texture[BLUE_GEM_IDX] = this->_driver->getTexture(BLUE_GEM);
	_texture[YOSHI_EGG_IDX] = this->_driver->getTexture(YOSHI_EGG);
}

void IrrlichtDisplay::setMapSize(Point const &size) {
	_map.clear(); //todo deinit
	float x_pos = 50;
	float y_pos = 50;
	for (int y = 0; y < size.getY(); ++y) {
		_map.push_back({});
		for (int x = 0; x < size.getX(); ++x) {
			x_pos = (x + 1) * 50;
			y_pos = (y + 1) * 50;
			auto content = std::make_shared<MapContent>();
			// initialise bloc aux x, y
			content->_block = create_block(IRON_BOX_IDX, {x_pos, 0, y_pos}, {5, 5, 5});
			_map[y].push_back(content);
		}
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
	for (auto it = teams.begin(); it != teams.end(); ++it) {
		auto team = std::make_shared<Team>();
		team->_name = *it;
		_teams.push_back(team);
	}
}

void IrrlichtDisplay::setTimeUnit(double unit) {
	(void)unit;
}

void IrrlichtDisplay::display(void) {

}

void IrrlichtDisplay::setMapTile(Point const &pos, Map::MapCase const &content) {
	auto & m = _map[pos.getY()][pos.getX()];
	m->_foods.clear();
	/*for (auto i = 0; i < content._food ; i++) {
		auto food = std::make_shared<Food>();
		//food->mesh = create_food();
		m->_foods.push_back(food);
	 */
	float x_pos = 50;
	float y_pos = 50;
	m->_stones.clear();
	for (auto i = 0; i < content._stone1 ; i++) {
		x_pos = (pos.getX() + 1) * 50;
		y_pos = (pos.getX()+ 1) * 50;
		auto stone1 = std::make_shared<AStone>();
		stone1->node= create_gem(PURPLE_GEM_IDX, {x_pos + random_pos(), 28, y_pos - random_pos()}, {0.1, 0.1, 0.1});
		m->_stones.push_back(stone1);
	}
	x_pos = 50;
	y_pos = 50;

	for (auto i = 0; i < content._stone2 ; i++) {
		x_pos = (pos.getX() + 1) * 50;
		y_pos = (pos.getY() + 1) * 50;
		auto stone2 = std::make_shared<AStone>();
		stone2->node = create_gem(RED_GEM_IDX, {x_pos - random_pos(), 28, y_pos}, {0.1, 0.1, 0.1});
		m->_stones.push_back(stone2);
	}

	for (auto i = 0; i < content._stone3 ; i++) {
		x_pos = (pos.getX() + 1) * 50;
		y_pos = (pos.getY() + 1) * 50;
		auto stone3 = std::make_shared<AStone>();
		stone3->node = create_gem(YELLOW_GEM_IDX, {x_pos, 28, y_pos + random_pos()}, {0.1, 0.1, 0.1});
		m->_stones.push_back(stone3);
	}

	for (auto i = 0; i < content._stone4 ; i++) {
		x_pos = (pos.getX() + 1) * 50;
		y_pos = (pos.getY() + 1) * 50;
		auto stone4 = std::make_shared<AStone>();
		stone4->node = create_gem(PINK_GEM_IDX, {x_pos + random_pos(), 28, y_pos}, {0.1, 0.1, 0.1});
		m->_stones.push_back(stone4);
	}

	for (auto i = 0; i < content._stone5 ; i++) {
		x_pos = (pos.getX() + 1) * 50;
		y_pos = (pos.getY() + 1) * 50;
		auto stone5 = std::make_shared<AStone>();
		stone5->node = create_gem(GREEN_GEM_IDX, {x_pos, 28, y_pos}, {0.1, 0.1, 0.1});
		m->_stones.push_back(stone5);
	}

	for (auto i = 0; i < content._stone6 ; i++) {
		x_pos = (pos.getX() + 1) * 50;
		y_pos = (pos.getY() + 1) * 50;
		auto stone6 = std::make_shared<AStone>();
		stone6->node = create_gem(GREEN_GEM_IDX, {x_pos - random_pos(), 28, y_pos + random_pos()}, {0.1, 0.1, 0.1});
		m->_stones.push_back(stone6);
	}

}

int	IrrlichtDisplay::random_pos()
{
	int pos;
	pos = rand() % 20;
	return (pos);
}

void
IrrlichtDisplay::addPlayer(size_t id, Point const &pos, Direction const &dir, size_t level, std::string const &team,
						   const IDisplay::PlayerOrigin &origin) {
	killPlayer(id);
	_players[id] = std::make_shared<Player>();
	_players[id]->id = id;
	_players[id]->pos = pos;
	_players[id]->level = level;
	_players[id]->dir = dir;
	(void)origin;
	(void)team;
	//_players[id]->team = team;
	//_players[id]->node = todo;
	//_players[id]->mesh = todo;
}

void IrrlichtDisplay::killPlayer(size_t id) {
	auto oldPlayer = _players.find(id);
	if (oldPlayer != _players.end())
		_players.erase(oldPlayer);
}

void IrrlichtDisplay::movePlayer(size_t id, Point const &to, const IDisplay::PlayerMoveStyle &how) {
	(void)how;
	_players[id]->pos = to;
	//todo player moove
}

void IrrlichtDisplay::setPlayerLevel(size_t id, size_t level) {
	_players[id]->level = level;
}

void IrrlichtDisplay::addEgg(size_t idEgg, size_t idPlayerFrom) {
	removeEgg(idEgg);
	_eggs[idEgg]->id = idEgg;
	_eggs[idEgg]->pos = _players[idPlayerFrom]->pos;
	//_eggs[idEgg]->team = _players[idPlayerFrom]->team;
	//todo
}

void IrrlichtDisplay::removeEgg(size_t id) {
	auto old_eggs = _eggs.find(id);
	if (old_eggs != _eggs.end())
		_eggs.erase(old_eggs);
}

void IrrlichtDisplay::setPlayerAction(size_t id, const IDisplay::PlayerAnimationStyle &what) {
	//todo
	(void)id;
	(void)what;
}


irr::scene::IMeshSceneNode *IrrlichtDisplay::create_gem(int texture,
														  irr::core::vector3df pos,
														  irr::core::vector3df scale) {
	auto* gem = create_mesh(texture, pos, scale, "../../Ress/model/PowerGem/gem.dae");
	return (gem);
}

irr::scene::IMeshSceneNode *IrrlichtDisplay::create_mesh(int texture, irr::core::vector3df pos, irr::core::vector3df scale,
														   const irr::io::path &filename) {
	irr::scene::IAnimatedMesh* mesh =_sceneManager->getMesh(filename);
	auto my_mesh = _sceneManager->addMeshSceneNode(mesh->getMesh(0));
	my_mesh->setPosition(pos);
	my_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	my_mesh->setScale(scale);
	my_mesh->setMaterialTexture(0, _texture[texture]);
	return (my_mesh);
}

irr::scene::IMeshSceneNode *IrrlichtDisplay::create_food(int texture, irr::core::vector3df pos, irr::core::vector3df scale) {
	irr::scene::IMeshSceneNode* food = create_mesh(texture, pos, scale, "../../Ress/model/PowerGem/gem.dae");
	return (food);
}