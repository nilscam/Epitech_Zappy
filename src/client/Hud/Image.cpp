//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Image.cpp
//

#include "Image.hpp"

Image::Image(irr::gui::IGUIImage *img, int id)
{
	_id = id;
	image = img;
}

Image::~Image()
{
}

int Image::getId() const
{
	return _id;
}

void Image::setScaleImage(bool scale)
{
	image->setScaleImage(scale);
}
