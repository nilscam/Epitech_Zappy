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
	const int MIN_LEVEL = 8;
	const int MAX_LEVEL = 8;
	const irr::core::vector3df	FOOD_SCALE = { 1.5, 1.5, 1.5 };
	const irr::core::vector3df	STONE_SCALE = { 0.1, 0.1, 0.1 };
	const irr::core::vector3df	EGG_SCALE = { 0.1, 0.1, 0.1 };
	const irr::core::vector3df	CURSOR_SCALE = { 30, 30, 30 };
	const float	CURSOR_INC_Y = 45;
	const float MIN_PLAYER_SCALE = 2.2;
	const float MAX_PLAYER_SCALE = 5.0;
	const irr::core::vector3df	BLOCK_SCALE = { 5, 5, 5 };
	const irr::core::vector3df	EGG_FX_SCALE = {20.0f, 20.0f, 20.0f};
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
	const irr::io::path	IRON_BOX = "./Ress/model/texture_grass.jpg";
	const irr::io::path	GRASS = "./Ress/model/grass.jpg";
	const irr::io::path	PURPLE_GEM = "./Ress/model/PowerGem/purplegem.png";
	const irr::io::path	PINK_GEM = "./Ress/model/PowerGem/pinkgem.png";
	const irr::io::path	RED_GEM = "./Ress/model/Gem1/Red.png";
	const irr::io::path	GREEN_GEM = "./Ress/model/Gem1/Green.png";
	const irr::io::path	YELLOW_GEM = "./Ress/model/Gem1/Yellow.png";
	const irr::io::path	BLUE_GEM = "./Ress/model/Gem1/Blue.png";
	const irr::io::path	TEXTURE_YOSHI_EGG_RED = "./Ress/model/Egg/Yoshi_egg_red.png";
	const irr::io::path	TEXTURE_YOSHI_EGG_BLUE = "./Ress/model/Egg/Yoshi_egg_blue.png";
	const irr::io::path	TEXTURE_YOSHI_EGG_GREEN = "./Ress/model/Egg/Yoshi_egg_green.png";
	const irr::io::path	TEXTURE_YOSHI_EGG_YELLOW = "./Ress/model/Egg/Yoshi_egg_yellow.png";
	const irr::io::path	TEXTURE_YOSHI_EGG_BROWN = "./Ress/model/Egg/Yoshi_egg_brown.png";
	const irr::io::path	GEM_MESH = "./Ress/model/PowerGem/gem.dae";
	const irr::io::path	EGG_MESH = "./Ress/model/Egg/YoshiEgg.obj";

	const irr::io::path	SKY_UP = "./Ress/model/irrlicht2_up.jpg";
	const irr::io::path	SKY_DOWN = "./Ress/model/irrlicht2_dn.jpg";
	const irr::io::path	SKY_LEFT = "./Ress/model/irrlicht2_lf.jpg";
	const irr::io::path	SKY_RIGHT = "./Ress/model/irrlicht2_rt.jpg";
	const irr::io::path	SKY_FORWARD = "./Ress/model/irrlicht2_ft.jpg";
	const irr::io::path	SKY_BACKWARD = "./Ress/model/irrlicht2_bk.jpg";
	const irr::io::path SKY_UP1 = "./Ress/model/sor_cwd/cwd_up.JPG";
	const irr::io::path SKY_DOWN1 = "./Ress/model/sor_cwd/cwd_dn.JPG";
	const irr::io::path SKY_LEFT1 = "./Ress/model/sor_cwd/cwd_lf.JPG";
	const irr::io::path SKY_RIGHT1 = "./Ress/model/sor_cwd/cwd_rt.JPG";
	const irr::io::path SKY_FORWARD1 = "./Ress/model/sor_cwd/cwd_bk.JPG";
	const irr::io::path SKY_BACKWARD1 = "./Ress/model/sor_cwd/cwd_ft.JPG";
	const irr::io::path SKY_UP2 = "./Ress/model/skybox/mp_met/met_up.tga";
	const irr::io::path SKY_DOWN2 = "./Ress/model/skybox/mp_met/met_dn.tga";
	const irr::io::path SKY_LEFT2 = "./Ress/model/skybox/mp_met/met_lf.tga";
	const irr::io::path SKY_RIGHT2 = "./Ress/model/skybox/mp_met/met_rt.tga";
	const irr::io::path SKY_FORWARD2 = "./Ress/model/skybox/mp_met/met_bk.tga";
	const irr::io::path SKY_BACKWARD2 = "./Ress/model/skybox/mp_met/met_ft.tga";
	const irr::io::path SKY_UP3 = "./Ress/model/skybox/mp_seeingred/seeingred_up.tga";
	const irr::io::path SKY_DOWN3 = "./Ress/model/skybox/mp_seeingred/seeingred_dn.tga";
	const irr::io::path SKY_LEFT3 = "./Ress/model/skybox/mp_seeingred/seeingred_lf.tga";
	const irr::io::path SKY_RIGHT3 = "./Ress/model/skybox/mp_seeingred/seeingred_rt.tga";
	const irr::io::path SKY_FORWARD3 = "./Ress/model/skybox/mp_seeingred/seeingred_bk.tga";
	const irr::io::path SKY_BACKWARD3 = "./Ress/model/skybox/mp_seeingred/seeingred_ft.tga";
	const irr::io::path SKY_UP4 = "./Ress/model/skybox/sb_strato/stratosphere_up.tga";
	const irr::io::path SKY_DOWN4 = "./Ress/model/skybox/sb_strato/stratosphere_dn.tga";
	const irr::io::path SKY_LEFT4 = "./Ress/model/skybox/sb_strato/stratosphere_lf.tga";
	const irr::io::path SKY_RIGHT4 = "./Ress/model/skybox/sb_strato/stratosphere_rt.tga";
	const irr::io::path SKY_FORWARD4 = "./Ress/model/skybox/sb_strato/stratosphere_bk.tga";
	const irr::io::path SKY_BACKWARD4 = "./Ress/model/skybox/sb_strato/stratosphere_ft.tga";

	const irr::io::path 	PERSO = "./Ress/model/perso/perso.dae";
	const irr::io::path	TEXTURE_PERSO_RED = "./Ress/model/perso/texture_perso_1.png";
	const irr::io::path	TEXTURE_PERSO_BLUE = "./Ress/model/perso/texture_perso_2.png";
	const irr::io::path	TEXTURE_PERSO_GREEN = "./Ress/model/perso/texture_perso_3.png";
	const irr::io::path	TEXTURE_PERSO_YELLOW = "./Ress/model/perso/texture_perso_4.png";
	const irr::io::path	TEXTURE_PERSO_BROWN = "./Ress/model/perso/texture_perso_5.png";
	const irr::io::path	PERSO_RUN = "./Ress/model/perso/MD3/running.MD3";
	const irr::io::path	PERSO_KICK1 = "./Ress/model/perso/MD3/mmakick.MD3";
	const irr::io::path	PERSO_KICK2 = "./Ress/model/perso/MD3/mmakick2.MD3";
	const irr::io::path	PERSO_HEADSPIN = "./Ress/model/perso/MD3/head_spin.MD3";
	const irr::io::path	PERSO_DROP = "./Ress/model/perso/MD3/drop.MD3";
	const irr::io::path	PERSO_TAKE = "./Ress/model/perso/MD3/take.MD3";
	const irr::io::path	PERSO_FALL = "./Ress/model/perso/MD3/fall_impact_kick.MD3";
	const irr::io::path PERSO_IDLES[] = {
		"./Ress/model/perso/MD3/idle1.MD3",
		"./Ress/model/perso/MD3/idle2.MD3",
		"./Ress/model/perso/MD3/idle3.MD3"
	};
	const irr::io::path PERSO_BACKFLIP = "./Ress/model/perso/MD3/backflip.MD3";
	// const irr::io::path PERSO_DIE = "./Ress/model/perso/MD3/die.MD3"; //! not working
	const irr::io::path PERSO_DIE = "./Ress/model/perso/MD3/fall_impact_kick.MD3";
	// const irr::io::path PERSO_FALLING = "./Ress/model/perso/MD3/falling.MD3"; //! not working
	const irr::io::path PERSO_FALLING = "./Ress/model/perso/MD3/backflip.MD3";
	const irr::io::path PERSO_FALL_IMPACT = "./Ress/model/perso/MD3/fall_impact_down.MD3";
	const irr::io::path PERSO_FALL_GET_UP = "./Ress/model/perso/MD3/fall_get_up.MD3";
	const irr::io::path PARTICLE_WHITE = "./Ress/model/particlewhite.bmp";
	const irr::io::path CURSOR = "./Ress/model/BattleCursor/SelectMonster.dae";
	// const irr::io::path CURSOR = "./Ress/model/PowerGem/gem.dae";
	const irr::io::path CURSOR_TEXTURE = "./Ress/model/BattleCursor/Battle_Arrow.png";

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
		YOSHI_EGG_RED_IDX,
		YOSHI_EGG_BLUE_IDX,
		YOSHI_EGG_GREEN_IDX,
		YOSHI_EGG_YELLOW_IDX,
		YOSHI_EGG_BROWN_IDX,
		FOOD_BASE_IDX_1,
		FOOD_BASE_IDX_2,
		FOOD_BASE_IDX_3,
		FOOD_BASE_IDX_4,
		FOOD_BASE_IDX_5,
		FOOD_BASE_IDX_6,
		TEXTURE_PERSO_RED_IDX,
		TEXTURE_PERSO_BLUE_IDX,
		TEXTURE_PERSO_GREEN_IDX,
		TEXTURE_PERSO_YELLOW_IDX,
		TEXTURE_PERSO_BROWN_IDX,
		SKY_UP_IDX,
		SKY_DOWN_IDX,
		SKY_LEFT_IDX,
		SKY_RIGHT_IDX,
		SKY_FORWARD_IDX,
		SKY_BACKWARD_IDX,
		SKY_UP1_IDX,
		SKY_DOWN1_IDX,
		SKY_LEFT1_IDX,
		SKY_RIGHT1_IDX,
		SKY_FORWARD1_IDX,
		SKY_BACKWARD1_IDX,
		SKY_UP2_IDX,
		SKY_DOWN2_IDX,
		SKY_LEFT2_IDX,
		SKY_RIGHT2_IDX,
		SKY_FORWARD2_IDX,
		SKY_BACKWARD2_IDX,
		SKY_UP3_IDX,
		SKY_DOWN3_IDX,
		SKY_LEFT3_IDX,
		SKY_RIGHT3_IDX,
		SKY_FORWARD3_IDX,
		SKY_BACKWARD3_IDX,
		SKY_UP4_IDX,
		SKY_DOWN4_IDX,
		SKY_LEFT4_IDX,
		SKY_RIGHT4_IDX,
		SKY_FORWARD4_IDX,
		SKY_BACKWARD4_IDX,
		PARTICLE_WHITE_IDX,
		CURSOR_TEXTURE_IDX
	};

	struct FoodTexture
	{
		irr::io::path			base;
		irr::io::path			mesh;
		TexIdx					idx;
		float					z;
		irr::core::vector3df	scale;
	};

	const FoodTexture FOODS[] = {
		{
			"./Ress/model/Food/Watermelon/Texture/WatermelonTexture.png",
			"./Ress/model/Food/Watermelon/Watermelon.obj",
			FOOD_BASE_IDX_1,
			IrrlichtDisplayConst::FOOD_Z,
			IrrlichtDisplayConst::FOOD_SCALE
		},
		{
			"./Ress/model/Food/Banana/Texture/Banana Texture.png",
			"./Ress/model/Food/Banana/Banana.obj",
			FOOD_BASE_IDX_2,
			IrrlichtDisplayConst::FOOD_Z,
			IrrlichtDisplayConst::FOOD_SCALE
		},
		{
			"./Ress/model/Food/Carrot/Texture/Carrot Texture.png",
			"./Ress/model/Food/Carrot/Carrot.obj",
			FOOD_BASE_IDX_3,
			IrrlichtDisplayConst::FOOD_Z,
			IrrlichtDisplayConst::FOOD_SCALE
		},
		{
			"./Ress/model/Food/Green Pepper/Texture/Green Pepper Texture.png",
			"./Ress/model/Food/Green Pepper/Green Pepper.obj",
			FOOD_BASE_IDX_4,
			IrrlichtDisplayConst::FOOD_Z,
			IrrlichtDisplayConst::FOOD_SCALE
		},
		{
			"./Ress/model/Food/Melon/Texture/Melon Texture.png",
			"./Ress/model/Food/Melon/Melon.obj",
			FOOD_BASE_IDX_5,
			IrrlichtDisplayConst::FOOD_Z,
			IrrlichtDisplayConst::FOOD_SCALE
		},
		{
			"./Ress/model/Food/Onion/Texture/Onion Texture.png",
			"./Ress/model/Food/Onion/Onion.obj",
			FOOD_BASE_IDX_6,
			IrrlichtDisplayConst::FOOD_Z,
			IrrlichtDisplayConst::FOOD_SCALE
		}
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
	int		getIdPlayerFollowCam(void) const;
	void	setTeams(std::vector<std::string> const & teams) override;
	void	setTimeUnit(double unit) override;
	void	display(std::shared_ptr<GUI> gui) override;
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
	void	movePlayer(size_t id, Point const & to) override;
	void	pushPlayer(size_t id, Point const & to, Direction const & dir) override;
	void	changePlayerDir(size_t id, Direction const & dir) override;
	void	setPlayerLevel(size_t id, size_t level) override;
	void	addEgg(size_t idEgg, size_t idPlayerFrom) override;
	void	removeEgg(size_t id) override;
	void	setPlayerAction(
		size_t id,
		PlayerAnimationStyle const & what
	) override;

	/* Init */
	bool							initTexture();
	irr::scene::ICameraSceneNode	*create_camera();
	bool 							create_sky(int idSkyBox);
	irr::scene::ISceneNode			*create_block(
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
	bool						isDeviceRunning(void);
	irr::IrrlichtDevice			*getDevice(void) const;
	irr::video::IVideoDriver	*getDriver(void) const;
	long long					getMovementDuration(void) const noexcept;
	int							getTeamIdx(std::string const & name) const noexcept;
	void						setPlayerCursor(size_t playerId);
	void						removePlayerCursor();

	static int						random_pos();
	static int						getRotationDegrees(Direction const & dir);
	static irr::core::vector3df		getRandomPos(Point mapPos, float z);
	static irr::core::vector3df		getCenterPos(Point mapPos, float z);
	static irr::core::vector3df		moveVector(
		irr::core::vector3df from,
		Direction const & dir,
		float inc
	);
	static irr::core::vector2df		rotatePoint(
		irr::core::vector2df const & center,
		double angle,
		irr::core::vector2df point
	);
	static IrrlichtDisplayConst::FoodTexture	getRandomFood(void);

private:

	class Team
	{
	public:

		Team(int idx, std::string const & name)
				:	_idx(idx)
				,	_name(name)
		{}
		virtual ~Team() = default;

		bool	operator==(std::string const & rhs) const noexcept
		{ return _name == rhs; }
		bool	operator!=(std::string const & rhs) const noexcept
		{ return !(*this == rhs); }

		int	getIdx(void) const noexcept
		{ return _idx; }

	private:

		int				_idx;
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
				int teamIdx,
				PlayerOrigin const & origin,
				long long movDurationMillis,
				double timeUnit,
				irr::scene::ISceneManager & sceneManager,
				std::map<int, irr::video::ITexture *> & textures
		);
		virtual ~Player();

		void	moveTo(Point const & pos);
		void	pushTo(Point const & pos, Direction const & dir);
		void	setLevel(size_t level);
		void	setDir(Direction const & dir);
		Point	getPos(void) const noexcept;
		irr::core::vector3df	getPosMesh(void) const noexcept;
		void	loop(void);
		void	animate(PlayerAnimationStyle const & how);
		void 	setDurationMillis(long long movDurationMillis, double timeUnit);
		void	fall(size_t height);
		void	kill(void);
		bool	isDead(void) const noexcept;
		size_t	getId(void) const noexcept;
		int		getTeamIdx(void) const noexcept;

	private:

		void					animate(irr::io::path const & path) noexcept;
		Point					generateRandomPos(void) const noexcept;
		irr::core::vector3df	getTileCenter(Point const & mapPos) const noexcept;
		irr::core::vector3df	getTileCenter(void) const noexcept;
		irr::core::vector3df	getRotationDegrees(Direction const & dir) const noexcept;
		irr::core::vector3df	getScaleLevel(size_t level) const noexcept;
		void					setMeshPosition(
			irr::core::vector3df const & pos,
			bool force = false
		);
		void					setMeshRotation(
			irr::core::vector3df const & rot,
			bool force = false
		);
		void					setMeshScale(
			irr::core::vector3df const & scale,
			bool force = false
		);
		void					loopMoving(void) noexcept;
		void					loopFalling(void) noexcept;
		void					loopAnimate(void) noexcept;
		void					changeMesh(irr::io::path const & path) noexcept;
		long long				generateRandomTimeIdle(void) const noexcept;
		irr::io::path			randomIdle(void) const noexcept;
		void					create_particle(void);

		/* Irrlicht */
		irr::scene::ISceneManager &					_sceneManager;
		std::map<int, irr::video::ITexture *> &		_textures;

		/* Mesh */
		irr::scene::IAnimatedMeshSceneNode *	_mesh;
		irr::io::path							_lastMeshPath;
		irr::core::vector3df					_lastMeshRotation;
		irr::core::vector3df					_lastMeshPosition;
		irr::core::vector3df					_lastMeshScale;

		/* Particles */
		irr::scene::IParticleSystemSceneNode *	_particle;

		/* Data */
		Point		_randomPos;
		Point		_mapPos;
		size_t		_id;
		Direction	_dir;
		int			_teamIdx;

		/* Animations */
		bool			_isAnimating;
		long long		_movDurationMillis;
		double 			_timeUnit;
		irr::io::path	_animationPath;
		Clock			_startAnimationClock;

		/* Movements */
		bool					_isMoving;
		bool					_movIsPushed;
		Point					_movFrom;
		Point					_movTo;
		Direction				_movDir;
		Clock					_movClock;
		double 					_movLastPercentage;
		irr::core::vector3df	_movInc;

		/* Falling */
		bool					_isFalling;
		int						_fallHeight;
		irr::core::vector3df	_fallInc;
		Clock					_fallClock;

		/* Die */
		bool					_isDying;
		bool					_isDead;
		Clock					_deadClock;

		/* Idle */
		bool					_isIdle;
		long long				_timeNextIdle;
		Clock					_idleClock;

		/* Level */
		size_t					_level;

		/* Incantation */
		bool					_isIncanting;

	};

	class Egg
	{
	public:

		Egg(size_t id, int teamIdx, Point const & pos,
			irr::video::IVideoDriver * _driver,
			irr::scene::ISceneManager & sceneManager,
			std::map<int, irr::video::ITexture *> & textures);
		virtual ~Egg()
		{
			if (_mesh != nullptr)
			{
				_mesh->remove();
			}
			if (_fx_egg)
			{
				_fx_egg->remove();
			}
		}

		void							change_texture(irr::io::path const & path);
		void							create_fx(irr::core::vector3df pos, irr::core::vector3df scale);
		void							positionNode(Point const & pos);
	private:

		size_t									_id;
		Point									_pos;
		irr::scene::IMeshSceneNode *				_mesh;
		irr::core::vector3df						_meshPos;
		irr::video::IVideoDriver *				_driver;
		irr::scene::ISceneManager &				_sceneManager;
		std::map<int, irr::video::ITexture *> &	_textures;
		irr::scene::IVolumeLightSceneNode * 		_fx_egg;
		int											_teamIdx;
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

	/* Camera */
	void	setCamera(float distance, float height, irr::core::vector3df const & target);

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
	void							manageEvent();

	std::vector<std::vector<std::shared_ptr<MapContent>>>	_map;
	std::map<size_t, std::shared_ptr<Player>>				_players;
	std::list<int>											_idxPlayers;
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
	int										_zoomCam;

	irr::core::vector3df	_cameraPosition;
	irr::core::vector3df	_cameraTarget;
	bool					_rotateCamera;
	double					_cameraRotationDegrees;
	Clock					_cameraRotationClock;

	irr::scene::IMeshSceneNode *	_cursor;

};

#endif //IrrlichtDisplay_H_
