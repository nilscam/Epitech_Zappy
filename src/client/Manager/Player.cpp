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
{
	_nbFood = 0;
	_nbStone1 = 0;
	_nbStone2 = 0;
	_nbStone3 = 0;
	_nbStone4 = 0;
	_nbStone5 = 0;
	_nbStone6 = 0;
	_isDead = false;
	_isIncanting = false;
}

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
bool		Player::getIsBroadcasting(void) const
{ return _isBroadcasting; }
int			getNbFood(void) const
{ return _nbFood; }
int			getNbStone1(void) const
{ return _nbStone1; }
int			getNbStone2(void) const
{ return _nbStone2; }
int			getNbStone3(void) const
{ return _nbStone3; }
int			getNbStone4(void) const
{ return _nbStone4; }
int			getNbStone5(void) const
{ return _nbStone5; }
int			getNbStone6(void) const
{ return _nbStone6; }

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
void		setIsBroadcasting(bool isBroadcasting)
{ _isBroadcasting = isBroadcasting; }
void		setNbFood(int Food)
{ _nbFood; = Food; }
void		setNbStone1(int Stone1)
{ _nbStone1 = Stone1;  }
void		setNbStone2(int Stone2)
{ _nbStone2 = Stone2;  }
void		setNbStone3(int Stone3)
{ _nbStone3 = Stone3;  }
void		setNbStone4(int Stone4)
{ _nbStone4 = Stone4;  }
void		setNbStone5(int Stone5)
{ _nbStone5 = Stone5;  }
void		setNbStone6(int Stone6)
{ _nbStone6 = Stone6;  }