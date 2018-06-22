/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** IDisplay.hpp
*/

#ifndef IDisplay_HPP
#define IDisplay_HPP

#include "Point.hpp"
#include "Direction.hpp"
#include "Map.hpp"

#include <vector>
#include <string>

class IDisplay
{
public:

	virtual ~IDisplay() = default;

	enum PlayerOrigin { TELEPORT, EGG };
	enum PlayerMoveStyle { WALK, PUSHED };
	enum PlayerAnimationStyle
	{ NONE, BROADCAST, INCANTATION, EGG_LAYING, DROP_RESOURCE, TAKE_RESOURCE, PUSH_PLAYER };

	/* Init */
	virtual bool	init(void) = 0;
	virtual void	loop(void) = 0;
	virtual void	deinit(void) = 0;
	virtual void	setMapSize(Point const & size) = 0;
	virtual void	setTeams(std::vector<std::string> const & teams) = 0;

	/* Runtime */
	virtual void	setTimeUnit(double unit) = 0;
	virtual void	display(void) = 0;
	virtual void	setMapTile(
		Point const & pos,
		Map::MapCase const & content
	) = 0;
	virtual void	addPlayer(
		size_t id,
		Point const & pos,
		Direction const & dir,
		size_t level,
		std::string const & team,
		PlayerOrigin const & origin
	) = 0;
	virtual void	killPlayer(size_t id) = 0;
	virtual void	movePlayer(
		size_t id,
		Point const & to,
		PlayerMoveStyle const & how
	) = 0;
	virtual void	changePlayerDir(size_t id, Direction const & dir) = 0;
	virtual void	setPlayerLevel(size_t id, size_t level) = 0;
	virtual void	addEgg(size_t idEgg, size_t idPlayerFrom) = 0;
	virtual void	removeEgg(size_t id) = 0;
	virtual void	setPlayerAction(
		size_t id,
		PlayerAnimationStyle const & what
	) = 0;

};

#endif // !IDisplay_HPP
