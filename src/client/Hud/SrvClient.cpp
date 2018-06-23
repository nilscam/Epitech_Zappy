//
// EPITECH PROJECT, 2018
// zappy
// File description:
// SrvClient.hpp
//

#include "SrvClient.hpp"

SrvClient::SrvClient()
{
}

SrvClient::~SrvClient()
{
}

void SrvClient::setNbTeam(const wchar_t *str)
{
	nbTeam = atoi(wchar_to_string(str).c_str());
	if (!nbTeam)
		++nbTeam;
}

void SrvClient::addClient(const wchar_t *str)
{
	nb.push_back(0);
	team.push_back(str);
}

const wchar_t *SrvClient::getName(SrvClient::ID id)
{
	int count = 0;	
	for (std::vector<const wchar_t *>::iterator it = team.begin();
	     it != team.end(); ++it) {
		if (count == id) {
			return (*it);
		}
		count += 1;
	}
	std::cout << "SrvClient::getName() can't find id " << id << "\n";
	return NULL;
}

int SrvClient::getNb(SrvClient::ID id)
{
	int count = 0;
	for (std::vector<int>::iterator it = nb.begin();
	     it != nb.end(); ++it) {
		if (count == id) {
			return (*it);
		}
		count += 1;
	}
	std::cout << "SrvClient::getNb() can't find id " << id << "\n";
	return -1;
}

void SrvClient::printAllTeam()
{
	int count = 1;
	for (std::vector<const wchar_t *>::iterator it = team.begin();
	     it != team.end(); ++it) {
		std::wcout << "Team " << count << " is \"" << (*it) << "\"\n";
		count += 1;
	}
}

void SrvClient::printAllPlayer()
{
	int count = 1;
	for (std::vector<int>::iterator it = nb.begin();
	     it != nb.end(); ++it) {
		std::wcout << "Team " << count << " are \"" << (*it) << "\"\n";
		count += 1;
	}
}

void SrvClient::addPlayer(SrvClient::ID id)
{
	int count = 0;	
	for (std::vector<int>::iterator it = nb.begin();
	     it != nb.end(); ++it) {
		if (id == count) {
			(*it) += 1;
			return ;
		}
		count += 1;
	}
	std::cout << "SrvClient::addPlayer() can't find id " << id << "\n";
}

int SrvClient::getNbTeam()
{
	return nbTeam;
}

const wchar_t *SrvClient::updateClient(SrvClient::ID id)
{
	int count = 0;
	int number = -1;
	std::string str = "";
	
	for (std::vector<const wchar_t *>::iterator it = team.begin();
	     it != team.end(); ++it) {
		if (count == id) {
			str = wchar_to_string(*it);
		}
		count += 1;
	}
	count = 0;
	for (std::vector<int>::iterator it = nb.begin();
	     it != nb.end(); ++it) {
		if (count == id) {
			number = (*it);
		}
		count += 1;
	}
	if (number == -1) {
		std::cout << "SrvClient::updateClient() can't find id " << id
			  << "\n";
		return L"";
	}
	str = str + " " + std::to_string(number);
	std::cout << "TEST :" << str << "\n";
	std::wstring tmp = std::wstring(str.begin(), str.end());
	wchar_t * olivier = (wchar_t *)malloc(sizeof(wchar_t) * (tmp.size() + 1));
	for (size_t i = 0; i < tmp.size(); ++i)
		olivier[i] = tmp[i];
	olivier[tmp.size()] = 0;
	return olivier;
}

std::vector<std::string>	SrvClient::getVectorTeam()
{
	std::vector<std::string> vec;
	for(auto it = this->team.begin(); it != this->team.end(); ++it) {
		std::wcout << "Team: " << *it << std::endl;
		vec.push_back(wchar_to_string(*it));
	}
	return (vec);
}

