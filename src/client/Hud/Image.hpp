//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Image.hpp
//

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "include.hpp"

class Image
{
public:
	Image(irr::gui::IGUIImage *img, int id);
	~Image();
	int getId() const;
	void setScaleImage(bool scale);
private:
	int _id;
	irr::gui::IGUIImage *image;	
};

#endif
