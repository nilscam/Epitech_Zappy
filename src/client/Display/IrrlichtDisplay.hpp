//
// Created by baptiste roubieu on 20/06/2018.
//

#ifndef IrrlichtDisplay_H_
#define IrrlichtDisplay_H_

#include "IDisplay.hpp"
#include "GUI.hpp"
#include <irrlicht/irrlicht.h>
#include <memory>

namespace IrrlichtDisplayConst
{
	const auto TEST = "../../Ress/model/wood.jpg";
	const irr::core::vector3df	FOOD_SCALE = { 3, 3, 3 };
	const irr::core::vector3df	STONE_SCALE = { 0.1, 0.1, 0.1 };
	const irr::core::vector3df	EGG_SCALE = { 0.1, 0.1, 0.1 };
	const int SCREEN_X = 1920;
	const int SCREEN_Y = 1080;
	const int FPS = 32;
	const float EGG_Z = 27.5;
	const float FOOD_Z = 30;
	const float STONE_Z = 28;
}

#define TEXTURE_BASE			"./Ress/model/wood.jpg"
#define IRON_BOX				"./Ress/model/iron_box.png"
#define GRASS				"./Ress/model/grass.jpg"
#define PURPLE_GEM			"./Ress/model/PowerGem/purplegem.png"
#define PINK_GEM				"./Ress/model/PowerGem/pinkgem.png"
#define RED_GEM				"./Ress/model/Gem1/Red.png"
#define GREEN_GEM			"./Ress/model/Gem1/Green.png"
#define	YELLOW_GEM			"./Ress/model/Gem1/Yellow.png"
#define BLUE_GEM				"./Ress/model/Gem1/Blue.png"
#define YOSHI_EGG			"./Ress/model/Egg/YoshSS00.png"
#define FOOD_BASE			"./Ress/model/Food/Watermelon/Texture/WatermelonTexture.png"
#define GEM_MESH				"./Ress/model/PowerGem/gem.dae"
#define FOOD_MESH			"./Ress/model/Food/Watermelon/Watermelon.obj"
#define EGG_MESH				"./Ress/model/Egg/YoshiEgg.obj"

#define TEXTURE_BASE_IDX		0
#define IRON_BOX_IDX			1
#define	GRASS_IDX			2
#define PURPLE_GEM_IDX		3
#define PINK_GEM_IDX			4
#define RED_GEM_IDX			5
#define GREEN_GEM_IDX			6
#define	YELLOW_GEM_IDX		7
#define BLUE_GEM_IDX			8
#define YOSHI_EGG_IDX			9
#define FOOD_BASE_IDX			10

class IrrlichtDisplay: private IDisplay {
public:

	IrrlichtDisplay();
	~IrrlichtDisplay() override;

	/* IDisplay */
	bool	init(void) override;
	void	deinit(void) override;
	void	setMapSize(Point const & size) override;
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

	/* Utils */
	bool							isDeviceRunning(void);
	irr::IrrlichtDevice			*getDevice(void) const;

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
				irr::scene::IMeshSceneNode * node
		)
				:	_id(id)
				,	_pos(pos)
				,	_dir(dir)
				,	_level(level)
				,	_node(node)
		{}
		virtual ~Player()
		{
			if (_node != nullptr)
			{
				_node->remove();
			}
		}

		Point const &	getPos(void) const noexcept
		{ return _pos; }
		Direction const &	getDir(void) const noexcept
		{ return _dir; }
		size_t	getLevel(void) const noexcept
		{ return _level; }
		void setPos(Point const & pos) noexcept
		{ _pos = pos; }
		void setLevel(size_t level) noexcept
		{ _level = level; }
		void setDir(Direction const & dir) noexcept
		{ _dir = dir; }

	private:

		size_t							_id;
		Point							_pos;
		Direction						_dir;
		size_t							_level;
		irr::scene::IMeshSceneNode *		_node;

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

	/* Utils */
	int		random_pos() const;

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
	irr::core::vector3df			getRandomPos(Point mapPos, float z) const noexcept;

	std::vector<std::vector<std::shared_ptr<MapContent>>>	_map;
	std::map<size_t, std::shared_ptr<Player>>				_players;
	std::map<size_t, std::shared_ptr<Egg>>					_eggs;
	std::vector<std::shared_ptr<Team>>						_teams;
	double													_timeUnit;

	irr::IrrlichtDevice *					_device;
	irr::video::IVideoDriver *				_driver;
	irr::scene::ISceneManager *				_sceneManager;
	std::map<int, irr::video::ITexture *>	_texture;
	bool									_isInit;

};


#endif //IrrlichtDisplay_H_
