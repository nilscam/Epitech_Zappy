//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ImageManager.hpp
//

#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

#include "include.hpp"
#include "Image.hpp"
#include <iostream>
#include <vector>

class ImageManager
{
public:
	ImageManager();
	~ImageManager();
	void addImage(Image img);
	void setScaleImage(bool scale, int id);	
private:
	std::vector<Image> list;	
};

#endif
