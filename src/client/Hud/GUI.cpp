//
// EPITECH PROJECT, 2018
// zappy
// File description:
// GUI.cpp
//

#include "GUI.hpp"

GUI::GUI(irr::IrrlichtDevice *device)
{
	env = device->getGUIEnvironment();
	tableId = 0;
	listBoxId = 0;
	buttonId = 0;
	imageId = 0;
}

GUI::~GUI()
{
}

void GUI::draw() const
{
	env->drawAll();
}

void GUI::setFont(const std::string file)
{
	irr::gui::IGUISkin *Skin = env->getSkin();
	irr::gui::IGUIFont *Font = env->getFont(file.c_str());
	Skin->setFont(Font);
	env->setSkin(Skin);
}

Table GUI::addTable(Rectangle rect)
{
	irr::gui::IGUITable *tabl = env->addTable(rect.get());
	tableId += 1;
	table = Table(tabl, tableId);
	std::cout << "LA" << "\n";
	return table;
}

ListBox GUI::addListBox(Rectangle rect)
{
	irr::gui::IGUIListBox *listBx = env->addListBox(rect.get());
	listBoxId += 1;
	listBox = ListBox(listBx, listBoxId);
	return listBox;
}

Button GUI::addButton(Rectangle rect, Button::Action action,
		      const wchar_t *str, int id)
{
	irr::gui::IGUIButton *button = env->addButton(rect.get(), 0, 0, str);	
	buttonId += 1;
	Button butt(button, action, id == -1 ? buttonId : id);
	buttonManager.addButton(butt);
	return butt;
}

Image GUI::addImage(Rectangle rect, irr::video::ITexture *texture, int id)
{
	irr::gui::IGUIImage *image = env->addImage(rect.get());
	image->setImage(texture);
	image->setUseAlphaChannel(true);
	imageId += 1;
	Image img(image, id == -1 ? imageId : id);
	imageManager.addImage(img);
	return img;
}

irr::gui::IGUIEnvironment *GUI::get() const
{
	return env;
}

void GUI::createTable(Rectangle rect, irr::video::ITexture *texture, int id)
{
	addImage(rect, texture, id);
	Rectangle tableRect(rect.getX() + 80, rect.getY() + 15,
			    rect.getX2() - 75, rect.getY2() - 13);
	addTable(tableRect);
	table.initTable();
	imageManager.setScaleImage(true, getLastImageId());
}

void GUI::createListBox(Rectangle rect, irr::video::ITexture *texture, int id)
{
	addImage(rect, texture, id);
	Rectangle listBoxRect(rect.getX() + 100, rect.getY() + 20,
			      rect.getX2() - 100, rect.getY2() - 20);
	addListBox(listBoxRect);
	imageManager.setScaleImage(true, getLastImageId());
}

void GUI::addListBoxMessage(const wchar_t *str, ListBox::MSGtype type)
{
	listBox.addText(str, type);
}

int GUI::getLastImageId() const
{
	return imageId;		
}

int GUI::getLastButtonId() const
{
	return buttonId;
}

