
//
// EPITECH PROJECT, 2018
// zappy
// File description:
// SrvClient.hpp
//

#ifndef SRVCLIENT_HPP
#define SRVCLIENT_HPP


#include "include.hpp"
#include <iostream>
#include <string>
#include <vector>

class SrvClient
{
public:
	enum ID {
		TEAM1,
		TEAM2,
		TEAM3,
		TEAM4
	};
	SrvClient();
	~SrvClient();
	const wchar_t *updateClient(SrvClient::ID id);
	std::string wchar_to_string(const wchar_t *str);
	void setNbTeam(const wchar_t *str);
	void addClient(const wchar_t *team);
	const wchar_t *getName(SrvClient::ID id);
	int getNb(SrvClient::ID id);
	int getNbTeam();
	void addPlayer(SrvClient::ID id);
	void printAllTeam();
	void printAllPlayer();
private:
	int nbTeam;
	std::vector<const wchar_t *> team;
	std::vector<int> nb;
};


#endif
