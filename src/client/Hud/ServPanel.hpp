//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ServPanel.hpp
//

#ifndef SERVPANEL_HPP
#define SERVPANEL_HPP

#include "include.hpp"
#include "EditBox.hpp"
#include "SrvClient.hpp"
#include <iostream>
#include <vector>

class ServPanel
{
public:
	ServPanel();
	~ServPanel();
	void setVisible(bool visible, int id);
	void setString(int id);
	void addEditBox(EditBox editBox);
	
	const wchar_t *getText(int id);
	const wchar_t *port;
	const wchar_t *width;
	const wchar_t *height;
	const wchar_t *client;
	const wchar_t *freq;
	const wchar_t *team;

	SrvClient srvClient;
private:
	std::vector<EditBox> list;
};

#endif
