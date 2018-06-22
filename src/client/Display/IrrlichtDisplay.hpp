//
// Created by baptiste roubieu on 20/06/2018.
//

#ifndef IrrlichtDisplay_H_
#define IrrlichtDisplay_H_

#include "IDisplay.hpp"
#include "GUI.hpp"
#include "MyEventReceiver.hpp"
#include "Clock.hpp"
#include "Math.hpp"
#include <irrlicht/irrlicht.h>
#include <memory>
#include <list>

namespace IrrlichtDisplayConst
{
	const irr::core::vector3df	FOOD_SCALE = { 1.5, 1.5, 1.5 };
	const irr::core::vector3df	STONE_SCALE = { 0.1, 0.1, 0.1 };
	const irr::core::vector3df	EGG_SCALE = { 0.1, 0.1, 0.1 };
	const irr::core::vector3df	PLAYER_SCALE = { 2.2, 2.2, 2.2 };
	const irr::core::vector3df	BLOCK_SCALE = { 5, 5, 5 };
	const int SIZE_MAP_TILE = 50;
	const int SCREEN_X = 1920;//800;//1920;
	const int SCREEN_Y = 1080;//800;//1080;
	const int NOT_CLICKED = -1;
	const int CLICK_ON_MAP = -2;
	const int FPS = 32;
	const float EGG_Z = 27.5;
	const float FOOD_Z = 30;
	const float STONE_Z = 28;
	const float PLAYER_Z = 27.5;
	const float BLOCK_Z = 0;
	const irr::io::path	TEXTURE_BASE = "./Ress/model/wood.jpg";
	const irr::io::path	IRON_BOX = "./Ress/model/iron_box.png";
	const irr::io::path	GRASS = "./Ress/model/grass.jpg";
	const irr::io::path	PURPLE_GEM = "./Ress/model/PowerGem/purplegem.png";
	const irr::io::path	PINK_GEM = "./Ress/model/PowerGem/pinkgem.png";
	const irr::io::path	RED_GEM = "./Ress/model/Gem1/Red.png";
	const irr::io::path	GREEN_GEM = "./Ress/model/Gem1/Green.png";
	const irr::io::path	YELLOW_GEM = "./Ress/model/Gem1/Yellow.png";
	const irr::io::path	BLUE_GEM = "./Ress/model/Gem1/Blue.png";
	const irr::io::path	YOSHI_EGG = "./Ress/model/Egg/YoshSS00.png";
	const irr::io::path	FOOD_BASE = "./Ress/model/Food/Watermelon/Texture/WatermelonTexture.png";
	const irr::io::path	GEM_MESH = "./Ress/model/PowerGem/gem.dae";
	const irr::io::path	FOOD_MESH = "./Ress/model/Food/Watermelon/Watermelon.obj";
	const irr::io::path	EGG_MESH = "./Ress/model/Egg/YoshiEgg.obj";
	const irr::io::path	SKY_UP = "./Ress/model/irrlicht2_up.jpg";
	const irr::io::path	SKY_DOWN = "./Ress/model/irrlicht2_dn.jpg";
	const irr::io::path	SKY_LEFT = "./Ress/model/irrlicht2_lf.jpg";
	const irr::io::path	SKY_RIGHT = "./Ress/model/irrlicht2_rt.jpg";
	const irr::io::path	SKY_FORWARD = "./Ress/model/irrlicht2_ft.jpg";
	const irr::io::path	SKY_BACKWARD = "./Ress/model/irrlicht2_bk.jpg";
	const irr::io::path 	PERSO = "./Ress/model/perso/perso.DAE";
	const irr::io::path	TEXTURE_PERSO = "./Ress/model/perso/texture_perso.png";
	const irr::io::path	PERSO_RUN = "././Ress/model/perso/MD3/running.MD3";
	const irr::io::path	PERSO_KICK1 = "././Ress/model/perso/MD3/mmakick.MD3";
	const irr::io::path	PERSO_KICK2 = "././Ress/model/perso/MD3/mmakick2.MD3";
	const irr::io::path	PERSO_HEADSPIN = "././Ress/model/perso/MD3/head_spin.MD3";
	const irr::io::path	PERSO_DROP = "././Ress/model/perso/MD3/drop.MD3";
	const irr::io::path	PERSO_TAKE = "././Ress/model/perso/MD3/take.MD3";
	const irr::io::path	PERSO_FALL = "././Ress/model/perso/MD3/die.MD3";


	enum TexIdx {
		TEXTURE_BASE_IDX,
		IRON_BOX_IDX,
		GRASS_IDX,
		PURPLE_GEM_IDX,
		PINK_GEM_IDX,
		RED_GEM_IDX,
		GREEN_GEM_IDX,
		YELLOW_GEM_IDX,
		BLUE_GEM_IDX,
		YOSHI_EGG_IDX,
		FOOD_BASE_IDX,
		TEXTURE_PERSO_IDX,
	};

}

class IrrlichtDisplay: private IDisplay {
public:

	IrrlichtDisplay();
	~IrrlichtDisplay() override;

	/* IDisplay */
	bool	init(void) override;
	void	loop(void) override;
	void	deinit(void) override;
	void	setMapSize(Point const & size) override;
	int		getTeamClicked(std::list<int> idxPlayers);
	void	setCameraPos(Point const & size);
	void	setCameraOnPlayer(int id);
	void	setTeams(std::vector<std::string> const & teams) override;
	void	setTimeUnit(double unit) override;
	void	display(void) override;
	void	setMapTile(
		Point const & pos,
		Map::MapCase const & content
	) override;
	void	addPlayer(
		size_t id,
		Point const & pos,
		Direction const & dir,
		size_t level,
		std::string const & team,
		PlayerOrigin const & origin
	) override;
	void	killPlayer(size_t id) override;
	void	movePlayer(
		size_t id,
		Point const & to,
		PlayerMoveStyle const & how
	) override;
	void	changePlayerDir(size_t id, Direction const & dir) override;
	void	setPlayerLevel(size_t id, size_t level) override;
	void	addEgg(size_t idEgg, size_t idPlayerFrom) override;
	void	removeEgg(size_t id) override;
	void	setPlayerAction(
		size_t id,
		PlayerAnimationStyle const & what
	) override;


	void display(std::shared_ptr<GUI> gui);

	/* Init */
	bool							initTexture();
	irr::scene::ICameraSceneNode	*create_camera();
	bool 							create_sky();
	irr::scene::ISceneNode			*create_block(
		int texture,
		irr::core::vector3df pos,
		irr::core::vector3df scale
	);
	irr::scene::IMeshSceneNode		*create_food(
		int texture,
		irr::core::vector3df pos,
		irr::core::vector3df scale
	);
	irr::scene::IMeshSceneNode		*create_mesh(
		int texture,
		irr::core::vector3df pos,
		irr::core::vector3df scale,
		const irr::io::path &filename
	);
	irr::scene::IMeshSceneNode		*create_gem(
		int texture,
		irr::core::vector3df pos,
		irr::core::vector3df scale
	);
	irr::scene::IMeshSceneNode		*create_egg(
			int texture,
			irr::core::vector3df pos,
			irr::core::vector3df scale
	);
	irr::scene::IAnimatedMeshSceneNode *create_player(
			irr::core::vector3df pos,
			irr::core::vector3df scale,
			int idxtexture
	);
	/* Utils */
	bool						isDeviceRunning(void);
	irr::IrrlichtDevice			*getDevice(void) const;
	long long					getMovementDuration(void) const noexcept;

	static int						random_pos();
	static int						getRotationDegrees(Direction const & dir);
	static irr::core::vector3df		getRandomPos(Point mapPos, float z);
	static irr::core::vector3df		getCenterPos(Point mapPos, float z);
	static irr::core::vector3df		moveVector(
		irr::core::vector3df from,
		Direction const & dir,
		float inc
	);

private:

	class Team
	{
	public:

		Team(std::string const & name)
				:	_name(name)
		{}
		virtual ~Team() = default;

	private:

		std::string		_name;

	};

	class AStone
	{
	public:

		enum Type { S1, S2, S3, S4, S5, S6 };

		AStone(irr::scene::IMeshSceneNode * node, Type const & type)
				:	_node(node)
				,	_type(type)
		{}
		virtual ~AStone()
		{
			if (_node != nullptr)
			{
				_node->remove();
			}
		}

		bool	operator==(AStone::Type const & rhs) const noexcept
		{ return _type == rhs; }

		bool	operator!=(AStone::Type const & rhs) const noexcept
		{ return !(*this == rhs); }

	private:

		irr::scene::IMeshSceneNode *	_node;
		Type							_type;

	};

	class Food
	{
	public:

		Food(irr::scene::IMeshSceneNode * node)
				:	_node(node)
		{}
		virtual ~Food()
		{
			if (_node != nullptr)
			{
				_node->remove();
			}
		}

	private:

		irr::scene::IMeshSceneNode *	_node;

	};

	class Player
	{
	public:

		Player(
				size_t id,
				Point const & pos,
				Direction const & dir,
				size_t level,
				irr::scene::IAnimatedMeshSceneNode * node
		);
		virtual ~Player();

		void	setPos(Point const & pos, long long movDurationMillis);
		void	setLevel(size_t level);
		void	setDir(Direction const & dir);
		Point	getPos(void) const noexcept;
		irr::core::vector3df	getPosMesh(void) const noexcept;
		void	loop(void);

	private:

		void	rotateNode(Direction const & dir);
		void	positionNode(Point const & pos);

		size_t									_id;
		Point									_pos;
		Direction								_dir;
		size_t									_level;
		irr::scene::IAnimatedMeshSceneNode *	_node;

		bool		_isMoving;
		Point		_movFrom;
		Point		_movTo;
		Direction	_movDir;
		Clock		_movClock;
		long long	_movDuration;
		double 		_movLastPercentage;

	};

	class Egg
	{
	public:

		Egg(size_t id, Point const & pos, irr::scene::IMeshSceneNode * node)
				:	_id(id)
				,	_pos(pos)
				,	_node(node)
		{}
		virtual ~Egg()
		{
			if (_node != nullptr)
			{
				_node->remove();
			}
		}

	private:

		size_t							_id;
		Point							_pos;
		irr::scene::IMeshSceneNode *	_node;
	};

	class MapContent
	{
	public:

		MapContent(irr::scene::ISceneNode * node)
				:	_node(node)
		{}
		virtual ~MapContent()
		{
			_node->remove();
		}

		void	setFoods(std::vector<std::shared_ptr<Food>> const & foods)
		{ _foods = foods; }

		void	setStones(std::vector<std::shared_ptr<AStone>> const & stones)
		{ _stones = stones; }

		std::vector<std::shared_ptr<AStone>> &	stones() noexcept
		{ return _stones; }

		std::vector<std::shared_ptr<Food>> &	foods() noexcept
		{ return _foods; }

	private:

		std::vector<std::shared_ptr<AStone>>	_stones;
		std::vector<std::shared_ptr<Food>>		_foods;
		irr::scene::ISceneNode					*_node;

	};

	/* Deinit */
	void							remove_block(irr::scene::ISceneNode * node);
	void							remove_mesh(irr::scene::IMeshSceneNode * mesh);

	/* Refresh */
	void	setFoodTile(
		std::shared_ptr<MapContent> & m,
		Point const &pos,
		Map::MapCase const & content
	);
	void	setStoneTile(
		std::shared_ptr<MapContent> & m,
		Point const &pos,
		int textureIdx,
		AStone::Type type,
		int nbAfter
	);
	void	setStonesTile(
		std::shared_ptr<MapContent> & m,
		Point const &pos,
		Map::MapCase const & content
	);

	bool							doesPlayerExist(size_t id) const noexcept;
	bool							doesEggExist(size_t id) const noexcept;
	bool							doesMapContentExist(Point const & pos) const noexcept;
	std::shared_ptr<Player>		getPlayer(size_t id) noexcept;
	std::shared_ptr<Egg>			getEgg(size_t id) noexcept;
	std::shared_ptr<MapContent>	getMapContent(Point const & pos) noexcept;
	void							manageCam();

	std::vector<std::vector<std::shared_ptr<MapContent>>>	_map;
	std::map<size_t, std::shared_ptr<Player>>				_players;
	std::map<size_t, std::shared_ptr<Egg>>					_eggs;
	std::vector<std::shared_ptr<Team>>						_teams;
	double													_timeUnit;

	irr::IrrlichtDevice *					_device;
	irr::video::IVideoDriver *				_driver;
	irr::scene::ISceneManager *				_sceneManager;
	irr::scene::ICameraSceneNode *			_camera;
	MyEventReceiver							_receiver;
	std::map<int, irr::video::ITexture *>	_texture;
	bool									_isInit;
	int										_followCam;
	Clock									_antiSpamCam;

};


#endif //IrrlichtDisplay_H_
