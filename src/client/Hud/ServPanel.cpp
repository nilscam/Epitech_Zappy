//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ServPanel.hpp
//

#include "ServPanel.hpp"

ServPanel::ServPanel()
{
}

ServPanel::~ServPanel()
{
}

void ServPanel::setVisible(bool visible, int id)
{
	for (std::vector<EditBox>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if (id == (*it).getId()) {
			(*it).setVisible(visible);
			return;
		}
	}
	std::cout << "ServPanel::setVisible() can't find id " << id << "\n";
}

void ServPanel::setString(int id)

{
	for (std::vector<EditBox>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			if (id == EditBox::PORT)
				port = (*it).getText();
			else if (id == EditBox::WIDTH)
				width = (*it).getText();
			else if (id == EditBox::HEIGHT)
				height = (*it).getText();
			else if (id == EditBox::CLIENT)
				client = (*it).getText();
			else if (id == EditBox::FREQ)
				freq = (*it).getText();
			else if (id == EditBox::TEAM)
				team = (*it).getText();
			else if (id == EditBox::NAME1 || id == EditBox::NAME2 ||
				 id == EditBox::NAME3 || id == EditBox::NAME4)
				srvClient.addClient((*it).getText());
			return;
		}			
	}
	std::cout << "ServPanel::setString() can't find id " << id << "\n";
}

void ServPanel::addEditBox(EditBox editBox)
{
	list.push_back(editBox);
}

const wchar_t *ServPanel::getText(int id)
{
	for (std::vector<EditBox>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if (id == (*it).getId())
			return (*it).getText();
	}
	return (L"ServPanel::getText() can't find id");
}
