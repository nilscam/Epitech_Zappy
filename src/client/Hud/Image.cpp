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

void Image::setText(const wchar_t *str)
{
	image->setToolTipText(str);
}

void Image::setScaleImage(bool scale)
{
	image->setScaleImage(scale);
}

void Image::setVisible(bool visible)
{
	image->setVisible(visible);
}
