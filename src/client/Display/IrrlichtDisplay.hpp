//
// Created by baptiste roubieu on 20/06/2018.
//

#ifndef IrrlichtDisplay_H_
#define IrrlichtDisplay_H_

#include "IDisplay.hpp"
#include <irrlicht/irrlicht.h>
#include <memory>


class IrrlichtDisplay: private IDisplay {
public:

	IrrlichtDisplay();
	~IrrlichtDisplay() override;

	void init(void) override;
	void deinit(void) override;
	void setMapSize(Point const &size) override;
	void setTeams(std::vector<std::string> const &teams) override;
	void setTimeUnit(double unit) override;
	void display(void) override;
	void setMapTile(Point const &pos, Map::MapCase const &content) override;
	void addPlayer(size_t id, Point const &pos, Direction const &dir, size_t level, std::string const &team,
				   PlayerOrigin const &origin) override;
	void killPlayer(size_t id) override;
	void movePlayer(size_t id, Point const &to, PlayerMoveStyle const &how) override;
	void changePlayerDir(size_t id, Direction const & dir) override;
	void setPlayerLevel(size_t id, size_t level) override;
	void addEgg(size_t idEgg, size_t idPlayerFrom) override;
	void removeEgg(size_t id) override;
	void setPlayerAction(size_t id, PlayerAnimationStyle const &what) override;
	irr::scene::ISceneNode		*create_block(int texture, irr::core::vector3df pos, irr::core::vector3df scale);
	irr::scene::IMeshSceneNode	*create_food(int texture, irr::core::vector3df pos, irr::core::vector3df scale);
	irr::scene::IMeshSceneNode *create_mesh(int texture, irr::core::vector3df pos, irr::core::vector3df scale, const irr::io::path &filename);
	void 	initTexture();
	irr::scene::IMeshSceneNode *create_gem(int texture, irr::core::vector3df pos, irr::core::vector3df scale);
	int	random_pos();
	bool					isDeviceRunning(void);
	irr::IrrlichtDevice		*getDevice(void) const;
	irr::scene::ICameraSceneNode	*create_camera();
	void 							create_sky();

private:

	class Team
	{
	public:
		std::string		_name;
	};

	class AStone {
	public:
		irr::scene::IAnimatedMesh *mesh;
		irr::scene::IMeshSceneNode	*node;
	};
	/*
	class Linemate : public AStone {};
	class Deraumere : public AStone {};
	class Sibur : public AStone {};
	class Mendiane : public AStone {};
	class Phiras : public AStone {};
	class Thystame : public AStone {};
	 */

	class Food {
	public:
		irr::scene::IAnimatedMesh *mesh;
		irr::scene::IMeshSceneNode	*node;
	};

	class Player
	{
	public:
		size_t id;
		Point  pos;
		Direction dir;
		size_t level;
		//Team const & team;
		irr::scene::IAnimatedMesh *mesh;
		irr::scene::IMeshSceneNode	*node;
	};

	class Egg
	{
	public:
		size_t id;
		Point pos;
		//Team const & team;
		irr::scene::IAnimatedMesh *mesh;
		irr::scene::IMeshSceneNode	*node;
	};

	struct MapContent
	{
	public:
		std::vector<std::shared_ptr<AStone>>	_stones;
		std::vector<std::shared_ptr<Food>>	_foods;
		irr::scene::ISceneNode					*_block;
	};

	std::vector<std::vector<std::shared_ptr<MapContent>>>	_map;
	std::map<size_t, std::shared_ptr<Player>>				_players;
	std::map<size_t, std::shared_ptr<Egg>>					_eggs;
	std::vector<std::shared_ptr<Team>>					_teams;
	double												_timeUnit;

	irr::IrrlichtDevice					*_device;
	irr::video::IVideoDriver				*_driver;
	irr::scene::ISceneManager				*_sceneManager;
	std::map<int, irr::video::ITexture *>	_texture;

};


#endif //IrrlichtDisplay_H_
