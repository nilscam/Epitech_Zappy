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
		irr::scene::ISceneManager & sceneManager,
		std::map<int, irr::video::ITexture *> & textures
)
	:	_sceneManager(sceneManager)
	,	_textures(textures)
	,	_mesh(nullptr)
	,	_lastMeshPath("")
	,	_lastMeshRotation(-1)
	,	_lastMeshPosition({ -1, -1, -1 })
	,	_randomPos(generateRandomPos())
	,	_mapPos(pos)
	,	_id(id)
	,	_dir(dir)
	,	_teamIdx(teamIdx)
	,	_isAnimating(false)
	,	_movDurationMillis(1000)
	,	_timeUnit(1)
	,	_animationPath(IrrlichtDisplayConst::PERSO)
	,	_isMoving(false)
	,	_isFalling(false)
{}

IrrlichtDisplay::Player::~Player()
{
	if (_mesh)
	{
		_mesh->remove();
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

void	IrrlichtDisplay::Player::setLevel(
	__attribute__((unused)) size_t level
)
{}

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
	// mesh
	if (_isAnimating)
	{
		changeMesh(_animationPath);
	}
	else if (_isFalling)
	{
		changeMesh(IrrlichtDisplayConst::PERSO_FALLING);
		// changeMesh(IrrlichtDisplayConst::PERSO_FALL_IMPACT);
		// changeMesh(IrrlichtDisplayConst::PERSO_FALL_GET_UP);
	}
	else if (_isMoving)
	{
		if (_movIsPushed)
			changeMesh(IrrlichtDisplayConst::PERSO_FALL);
		else
			changeMesh(IrrlichtDisplayConst::PERSO_RUN);
	}
	else
	{
		changeMesh(IrrlichtDisplayConst::PERSO);
	}
}

void	IrrlichtDisplay::Player::animate(PlayerAnimationStyle const & how)
{
	_isAnimating = true;
	_startAnimationClock.mark();
	switch (how)
	{
		case INCANTATION:
		{
			_animationPath = IrrlichtDisplayConst::PERSO_HEADSPIN;
			break;
		}
		case EGG_LAYING:
		case DROP_RESOURCE:
		{
			_animationPath = IrrlichtDisplayConst::PERSO_DROP;
			break;
		}
		case TAKE_RESOURCE:
		{
			_animationPath = IrrlichtDisplayConst::PERSO_TAKE;
			break;
		}
		case PUSH_PLAYER:
		{
			_animationPath = IrrlichtDisplayConst::PERSO_KICK1;
			break;
		}
		default:
		{
			_isAnimating = false;
			break;
		}
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
	// todo
}

void	IrrlichtDisplay::Player::loopAnimate(void) noexcept
{
	if (_isAnimating && _startAnimationClock.timeSinceMark() > _movDurationMillis)
	{
		_isAnimating = false;
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
		_mesh->setScale(IrrlichtDisplayConst::PLAYER_SCALE);
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
		if (_movDurationMillis > 0)
		{
			irr::f32 fps = (float)_timeUnit * maxFrames;
			_mesh->setAnimationSpeed(fps);
		}
	}
}
