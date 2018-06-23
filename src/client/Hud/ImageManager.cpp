//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ImageManager.cpp
//

#include "ImageManager.hpp"

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

void ImageManager::addImage(Image img)
{
	list.push_back(img);
}

void ImageManager::setScaleImage(bool scale, int id)
{
	for (std::vector<Image>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setScaleImage(scale);
			return;
		}
	}
	std::cerr << "ImageManager::setScaleImage() can't find id " << id << "\n";
}

void ImageManager::setVisible(bool scale, int id)
{
	for (std::vector<Image>::iterator it = list.begin();
	     it != list.end(); ++it) {
		if ((*it).getId() == id) {
			(*it).setVisible(scale);
			return;
		}
	}
	std::cerr << "ImageManager::setVisible() can't find id " << id << "\n";
}
