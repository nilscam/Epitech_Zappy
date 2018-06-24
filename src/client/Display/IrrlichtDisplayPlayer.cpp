/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** IrrlichtDisplayPlayer.cpp
*/

#include "IrrlichtDisplay.hpp"

IrrlichtDisplay::Player::Player(
		size_t id,
		Point const & pos,
		Direction const & dir,
		__attribute__((unused)) size_t level,
		int teamIdx,
		PlayerOrigin const & origin,
		long long movDurationMillis,
		double timeUnit,
		irr::scene::ISceneManager & sceneManager,
		std::map<int, irr::video::ITexture *> & textures
)
	:	_sceneManager(sceneManager)
	,	_textures(textures)
	,	_mesh(nullptr)
	,	_lastMeshPath("")
	,	_lastMeshRotation(-1)
	,	_lastMeshPosition({ -1, -1, -1 })
	,	_lastMeshScale({ -1, -1, -1 })
	,	_particle(nullptr)
	,	_randomPos(generateRandomPos())
	,	_mapPos(pos)
	,	_id(id)
	,	_dir(dir)
	,	_teamIdx(teamIdx)
	,	_isAnimating(false)
	,	_movDurationMillis(movDurationMillis)
	,	_timeUnit(timeUnit)
	,	_animationPath(IrrlichtDisplayConst::PERSO)
	,	_isMoving(false)
	,	_isFalling(false)
	,	_isDying(false)
	,	_isIdle(false)
	,	_timeNextIdle(0)
	,	_level(1)
	,	_isIncanting(false)
{
	switch (origin)
	{
		case EGG:
		{
			animate(IrrlichtDisplayConst::PERSO_BACKFLIP);
			break;
		}
		default:
		case TELEPORT:
		{
			fall(150);
			break;
		}
	}
}

IrrlichtDisplay::Player::~Player()
{
	if (_mesh)
	{
		_mesh->remove();
	}
	if (_particle)
	{
		_particle->remove();
	}
}

void	IrrlichtDisplay::Player::moveTo(Point const & pos)
{
	if (_mapPos != pos)
	{
		if (_movDurationMillis <= 0)
		{
			_isMoving = false;
		}
		else
		{
			_isMoving = true;
			_movIsPushed = false;
			_movFrom = _mapPos;
			_movTo = pos;
			_movDir = _dir;
			_movClock.mark();
			_movLastPercentage = -1;
		}
		_mapPos = pos;
	}
}

void	IrrlichtDisplay::Player::pushTo(Point const & pos, Direction const & dir)
{
	if (_mapPos != pos)
	{
		if (_movDurationMillis <= 0)
		{
			_isMoving = false;
		}
		else
		{
			_isMoving = true;
			_movIsPushed = true;
			_movFrom = _mapPos;
			_movTo = pos;
			_movDir = dir;
			_movClock.mark();
			_movLastPercentage = -1;
		}
		_mapPos = pos;
	}
}

void	IrrlichtDisplay::Player::setLevel(size_t level)
{
	_level = level;
}

void	IrrlichtDisplay::Player::setDir(Direction const & dir)
{
	_dir = dir;
}

Point	IrrlichtDisplay::Player::getPos(void) const noexcept
{
	return _mapPos;
}

irr::core::vector3df	IrrlichtDisplay::Player::getPosMesh(void) const noexcept
{
	return _lastMeshPosition;
}

void	IrrlichtDisplay::Player::loop(void)
{
	// loop
	loopMoving();
	loopFalling();
	loopAnimate();
	// pos
	irr::core::vector3df pos = getTileCenter();
	irr::core::vector3df const zero = { 0, 0, 0 };
	pos += (_isFalling ? _fallInc : zero);
	pos += (_isMoving ? _movInc : zero);
	setMeshPosition(pos);
	// rot
	setMeshRotation(getRotationDegrees(_dir));
	// scale
	setMeshScale(getScaleLevel(_level));
	// mesh
	if (_isDying)
	{
		_isIdle = false;
		if (!_isDead && _deadClock.timeSinceMark() > 3000)
		{
			_isDead = true;
		}
	}
	else if (_isAnimating)
	{
		_isIdle = false;
		changeMesh(_animationPath);
	}
	else if (_isFalling)
	{
		_isIdle = false;
		changeMesh(IrrlichtDisplayConst::PERSO_FALLING);
	}
	else if (_isMoving)
	{
		_isIdle = false;
		if (_movIsPushed)
			changeMesh(IrrlichtDisplayConst::PERSO_FALL);
		else
			changeMesh(IrrlichtDisplayConst::PERSO_RUN);
	}
	else if (_isIncanting)
	{
		_isIdle = false;
		changeMesh(IrrlichtDisplayConst::PERSO_HEADSPIN);
	}
	else
	{
		bool wasIdle = _isIdle;
		_isIdle = true;
		if (!_mesh || !wasIdle
		|| (_mesh->getFrameNr() >= _mesh->getEndFrame()
			&& _idleClock.timeSinceMark() >= _timeNextIdle))
		{
			_timeNextIdle = generateRandomTimeIdle();
			_idleClock.mark();
			changeMesh(randomIdle());
		}
	}
}

void	IrrlichtDisplay::Player::animate(PlayerAnimationStyle const & how)
{
	switch (how)
	{
		case START_INCANTATION:
		{
			_isIncanting = true;
			break;
		}
		case END_INCANTATION:
		{
			_isIncanting = false;
			break;
		}
		case EGG_LAYING:
		case DROP_RESOURCE:
		{
			animate(IrrlichtDisplayConst::PERSO_DROP);
			break;
		}
		case TAKE_RESOURCE:
		{
			animate(IrrlichtDisplayConst::PERSO_TAKE);
			break;
		}
		case PUSH_PLAYER:
		{
			animate(IrrlichtDisplayConst::PERSO_KICK1);
			break;
		}
		default:
		{}
	}
}

void 	IrrlichtDisplay::Player::setDurationMillis(
	long long movDurationMillis,
	double timeUnit
)
{
	_movDurationMillis = movDurationMillis;
	_timeUnit = timeUnit;
}

void	IrrlichtDisplay::Player::fall(size_t height)
{
	_isFalling = true;
	_fallHeight = height;
}

void	IrrlichtDisplay::Player::kill(void)
{
	_isDying = true;
	_deadClock.mark();
	changeMesh(IrrlichtDisplayConst::PERSO_DIE);
	create_particle();
}

bool	IrrlichtDisplay::Player::isDead(void) const noexcept
{
	return _isDead;
}

size_t	IrrlichtDisplay::Player::getId(void) const noexcept
{
	return _id;
}

int		IrrlichtDisplay::Player::getTeamIdx(void) const noexcept
{
	return _teamIdx;
}

void	IrrlichtDisplay::Player::animate(irr::io::path const & path) noexcept
{
	_isAnimating = true;
	_startAnimationClock.mark();
	_animationPath = path;
}

Point	IrrlichtDisplay::Player::generateRandomPos(void) const noexcept
{
	int max = IrrlichtDisplayConst::SIZE_MAP_TILE / 4;
	int x = Math::randomNumberBetween(-max, max);
	int y = Math::randomNumberBetween(-max, max);
	return { x, y };
}

irr::core::vector3df	IrrlichtDisplay::Player::getTileCenter(
	Point const & mapPos
) const noexcept
{
	irr::core::vector3df mesh = IrrlichtDisplay::getCenterPos(
			mapPos, IrrlichtDisplayConst::PLAYER_Z
	);
	return {
			mesh.X + _randomPos.getX(),
			mesh.Y,
			mesh.Z + _randomPos.getY()
	};
}

irr::core::vector3df	IrrlichtDisplay::Player::getTileCenter(void) const noexcept
{
	return getTileCenter(_mapPos);
}

irr::core::vector3df	IrrlichtDisplay::Player::getRotationDegrees(
	Direction const & dir
) const noexcept
{
	return { 0, (float) IrrlichtDisplay::getRotationDegrees(dir), 0 };
}

irr::core::vector3df	IrrlichtDisplay::Player::getScaleLevel(size_t level) const noexcept
{
	float maxLevel = IrrlichtDisplayConst::MAX_LEVEL;
	float minScale = IrrlichtDisplayConst::MIN_PLAYER_SCALE;
	float maxScale = IrrlichtDisplayConst::MAX_PLAYER_SCALE;
	float lvl = (float)(level);
	float scale = (lvl * ((maxScale - minScale) / maxLevel)) + minScale;
	return { scale, scale, scale };
}

void	IrrlichtDisplay::Player::setMeshPosition(
	irr::core::vector3df const & pos,
	bool force
)
{
	if (force || _lastMeshPosition != pos)
	{
		_lastMeshPosition = pos;
		if (_mesh)
		{
			_mesh->setPosition(pos);
		}
	}
}

void	IrrlichtDisplay::Player::setMeshRotation(
	irr::core::vector3df const & rot,
	bool force
)
{
	if (force || _lastMeshRotation != rot)
	{
		_lastMeshRotation = rot;
		if (_mesh)
		{
			_mesh->setRotation(rot);
		}
	}
}

void	IrrlichtDisplay::Player::setMeshScale(
	irr::core::vector3df const & scale,
	bool force
)
{
	if (force || _lastMeshScale != scale)
	{
		_lastMeshScale = scale;
		if (_mesh)
		{
			_mesh->setScale(scale);
		}
	}
}

void	IrrlichtDisplay::Player::loopMoving(void) noexcept
{
	if (_isMoving)
	{
		long long movMillis = _movClock.timeSinceMark();
		if (movMillis >= _movDurationMillis)
		{
			_isMoving = false;
		}
		else
		{
			double movPercentage = movMillis * 100.0 / _movDurationMillis;
			if (movPercentage != _movLastPercentage)
			{
				_movLastPercentage = movPercentage;
				double maxDistance = IrrlichtDisplayConst::SIZE_MAP_TILE / 2;
				Point movStart;
				double distanceToEnd;
				Direction movDir = _movDir;
				bool isFirstTile = movPercentage <= 50.0;
				if (isFirstTile)
				{
					movStart = _movFrom;
					distanceToEnd = movPercentage * maxDistance / 50.0;
				}
				else
				{
					movStart = _movTo;
					distanceToEnd = maxDistance - ((movPercentage - 50) * maxDistance / 50.0);
					movDir.reverse();
				}
				irr::core::vector3df from = getTileCenter();
				irr::core::vector3df to = IrrlichtDisplay::moveVector(
						getTileCenter(movStart),
						movDir,
						Math::clamp(0.0, maxDistance, distanceToEnd)
				);
				_movInc = to - from;
				if (!isFirstTile && distanceToEnd >= maxDistance)
				{
					_isMoving = false;
				}
			}
		}
		if (!_isMoving)
		{
			_mapPos = _movTo;
		}
	}
}

void	IrrlichtDisplay::Player::loopFalling(void) noexcept
{
	if (_isFalling)
	{
		if (_fallClock.timeSinceMark() > 2)
		{
			_fallClock.mark();
			_fallHeight -= 2;
		}
		if (_fallHeight <= 10)
		{
			animate(IrrlichtDisplayConst::PERSO_FALL_IMPACT);
			_isFalling = false;
		}
		_fallInc = { 0, (float)_fallHeight, 0 };
	}
}

void	IrrlichtDisplay::Player::loopAnimate(void) noexcept
{
	if (_isAnimating
	&& (!_mesh
		|| (_startAnimationClock.timeSinceMark() > _movDurationMillis
			&& _mesh->getFrameNr() >= _mesh->getEndFrame())))
	{
		_isAnimating = false;
		if (_animationPath == IrrlichtDisplayConst::PERSO_FALL_IMPACT)
		{
			animate(IrrlichtDisplayConst::PERSO_FALL_GET_UP);
		}
	}
}

void	IrrlichtDisplay::Player::changeMesh(irr::io::path const & path) noexcept
{
	if (path == _lastMeshPath)
		return;
	_lastMeshPath = path;
	if (_mesh)
	{
		_mesh->remove();
		_mesh = nullptr;
	}
	auto * mesh = _sceneManager.getMesh(path);
	_mesh = mesh ? _sceneManager.addAnimatedMeshSceneNode(mesh) : nullptr;
	if (_mesh)
	{
		setMeshPosition(_lastMeshPosition, true);
		setMeshRotation(_lastMeshRotation, true);
		setMeshScale(_lastMeshScale, true);
		_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		if (_teamIdx == 0)
			_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::TEXTURE_PERSO_RED_IDX]);
		else if (_teamIdx == 1)
			_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::TEXTURE_PERSO_BLUE_IDX]);
		else if (_teamIdx == 2)
			_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::TEXTURE_PERSO_GREEN_IDX]);
		else if (_teamIdx == 3)
			_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::TEXTURE_PERSO_YELLOW_IDX]);
		else
			_mesh->setMaterialTexture(0, _textures[IrrlichtDisplayConst::TEXTURE_PERSO_BROWN_IDX]);
		auto maxFrames = _mesh->getEndFrame();
		if (_isDying || _isAnimating || _isIdle)
		{
			_mesh->setLoopMode(false);
		}
		if (_isDying || _isIdle || _timeUnit <= 0)
		{
			_mesh->setAnimationSpeed(30);
		}
		else
		{
			irr::f32 fps = (float)_timeUnit * maxFrames;
			_mesh->setAnimationSpeed(fps);
		}
	}
}

long long	IrrlichtDisplay::Player::generateRandomTimeIdle(void) const noexcept
{
	return Math::randomNumberBetween(2500, 4500);
}

irr::io::path	IrrlichtDisplay::Player::randomIdle(void) const noexcept
{
	int max = sizeof(IrrlichtDisplayConst::PERSO_IDLES) / sizeof(*IrrlichtDisplayConst::PERSO_IDLES);
	int r = Math::randomNumberBetween(0, max - 1);
	return IrrlichtDisplayConst::PERSO_IDLES[r];
}

void	IrrlichtDisplay::Player::create_particle(void)
{
	_particle = _sceneManager.addParticleSystemSceneNode(false);
	irr::scene::IParticleEmitter * em = _particle->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-10,0,-10,10,1,10), // emitter size
			irr::core::vector3df(0.0f,0.06f,0.0f),   // initial direction
			25, 40,                             // emit rate
			irr::video::SColor(0,255,255,255),       // darkest color
			irr::video::SColor(0,255,255,255),       // brightest color
			800,1500,30,                         // min and max age, angle
			irr::core::dimension2df(10.f,10.f),         // min size
			irr::core::dimension2df(20.f,20.f));        // max size
	if (em)
	{
		_particle->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it
	}
	irr::scene::IParticleAffector * paf = _particle->createFadeOutParticleAffector();
	if (paf)
	{
		_particle->addAffector(paf); // same goes for the affector
		paf->drop();
	}
	_particle->setPosition(_lastMeshPosition);
	_particle->setScale(irr::core::vector3df(2,2,2));
	_particle->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_particle->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	_particle->setMaterialTexture(0, _textures[IrrlichtDisplayConst::PARTICLE_WHITE_IDX]);
	_particle->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}
