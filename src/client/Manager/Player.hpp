/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Player.hpp
*/

#ifndef Player_HPP
#define Player_HPP

#include "Direction.hpp"
#include "Point.hpp"

class Player
{
public:

	Player(
		Point pos,
		Direction currentDir,
		std::string nameTeam,
		int idxTeam,
		int level
	);
	virtual ~Player() = default;
	Player(Player const & rhs) = default;
	Player(Player && rhs) = default;
	Player & operator=(Player const & rhs) = default;
	Player & operator=(Player && rhs) = default;

	Point		getPos(void) const;
	Direction	getCurrentDir(void) const;
	std::string	getNameTeam(void) const;
	int			getIdxTeam(void) const;
	int			getLevel(void) const;
	bool		getIsDead(void) const;
	bool		getIsIncanting(void) const;
	bool		getIsBroadcasting(void) const;
	int			getNbFood(void) const;
	int			getNbStone1(void) const;
	int			getNbStone2(void) const;
	int			getNbStone3(void) const;
	int			getNbStone4(void) const;
	int			getNbStone5(void) const;
	int			getNbStone6(void) const;

	void		setPos(Point const & pos);
	void		setCurrentDir(Direction & currentDir);
	void		setNameTeam(std::string & nameTeam);
	void		setIdxTeam(int idxTeam);
	void		setLevel(int level);
	void		setIsDead(bool isDead);
	void		setIsIncanting(bool isIncanting);
	void		setIsBroadcasting(bool isBroadcasting);
	void		setNbFood(int Food);
	void		setNbStone1(int Stone1);
	void		setNbStone2(int Stone2);
	void		setNbStone3(int Stone3);
	void		setNbStone4(int Stone4);
	void		setNbStone5(int Stone5);
	void		setNbStone6(int Stone6);

	friend std::ostream & operator<<(std::ostream & os, Player const & info);

private:
	Point		_pos;
	Direction	_currentDir;
	std::string	_nameTeam;
	int			_idxTeam;
	int			_nbFood;
	int			_nbStone1;
	int			_nbStone2;
	int			_nbStone3;
	int			_nbStone4;
	int			_nbStone5;
	int			_nbStone6;
	int			_level;
	bool		_isDead;
	bool		_isIncanting;
	bool		_isBroadcasting;
};

#endif // !Player_HPP