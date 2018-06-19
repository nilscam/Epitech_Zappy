/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PlayerInfo.cpp
*/

#include "PlayerInfo.hpp"

Player::Player(
	Point pos,
	Direction currentDir,
	std::string nameTeam,
	int idxTeam,
	int level
)
	:	_pos(pos)
	,	_currentDir(currentDir)
	,	_nameTeam(nameTeam)
	,	_idxTeam(idxTeam)
	,	_level(level)
{}

std::ostream & operator<<(std::ostream & os, PlayerInfo const & info)
{
	(void)os; (void)info;
	return (os);
}

Point		Player::getPos(void) const
{ return _pos; }
Direction	Player::getCurrentDir(void) const
{ return _currentDir; }
std::string	Player::getNameTeam(void) const
{ return _nameTeam; }
int			Player::getIdxTeam(void) const
{ return _idxTeam; }
int			Player::getLevel(void) const
{ return _level; }
bool		Player::getIsDead(void) const
{ return _isDead; }
bool		Player::getIsIncanting(void) const
{ return _isIncanting; }

void		Player::setPos(Point const & pos)
{ _pos = pos; }
void		Player::setCurrentDir(Direction & currentDir)
{ _currentDir = currentDir; }
void		Player::setNameTeam(std::string & nameTeam)
{ _nameTeam = nameTeam; }
void		Player::setIdxTeam(int idxTeam)
{ _idxTeam = idxTeam; }
void		Player::setLevel(int level)
{ _level = level; }
void		Player::setIsDead(bool isDead)
{ _isDead = isDead; }
void		Player::setIsIncanting(bool isIncanting)
{ _isIncanting = isIncanting; }