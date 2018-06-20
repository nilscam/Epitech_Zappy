//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ButtonManager.cpp
//

#include "ButtonManager.hpp"

ButtonManager::ButtonManager()
{
}

ButtonManager::~ButtonManager()
{
}

void ButtonManager::addButton(Button button)
{
	list.push_back(button);
}

void ButtonManager::setVisible(bool visible, int id)
{
	for (std::vector<Button>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setVisible(visible);
			return;
		}
	}
	std::cerr << "ButtonManager::setVisible() can't find id " << id << "\n";
}

void ButtonManager::setImage(irr::video::ITexture *text, int id)
{
	for (std::vector<Button>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setImage(text);
			return;
		}
	}
	std::cerr << "ButtonManager::setImage() can't find id " << id << "\n";
}

void ButtonManager::setScaleImage(bool scale, int id)
{
	for (std::vector<Button>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setScaleImage(scale);
			return;
		}
	}
	std::cerr << "ButtonManager::setScaleImage() can't find id " << id << "\n";
}

void ButtonManager::isButtonPressed()
{
	for (std::vector<Button>::iterator it = list.begin();
	     it != list.end(); ++it) {
		(*it).pressed();
	}
}
				    
