//
// EPITECH PROJECT, 2018
// zappy
// File description:
// GUI.cpp
//

#include "GUI.hpp"

GUI::GUI(irr::IrrlichtDevice *device)
{
	_device = device;
	env = device->getGUIEnvironment();
	_driver = device->getVideoDriver();
	_scene = device->getSceneManager();
	tableId = 0;
	listBoxId = 0;
	buttonId = 0;
	imageId = 0;
	this->setFont(PATH_TO_RES GLOBAL_FONT);
	this->createListBox(Rectangle(LISTBOX_X, LISTBOX_Y, LISTBOX_X2, LISTBOX_Y2), PATH_TO_RES RES_PANEL);
	this->createTable(Rectangle(TABLE_X, TABLE_Y, TABLE_X2, TABLE_Y2), PATH_TO_RES RES_PANEL);
	device->setResizable(false);
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

Image GUI::addImage(Rectangle rect, const std::string &path, int id)
{
	irr::gui::IGUIImage *image = env->addImage(rect.get());
	image->setImage(_driver->getTexture(path.c_str()));
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

void GUI::createTable(Rectangle rect, const std::string &path, int id)
{
	addImage(rect, path, id);
	Rectangle tableRect(rect.getX() + 80, rect.getY() + 15,
			    rect.getX2() - 75, rect.getY2() - 13);
	addTable(tableRect);
	table.initTable();
	imageManager.setScaleImage(true, getLastImageId());
}

void GUI::createListBox(Rectangle rect, const std::string &path, int id)
{
	addImage(rect, path, id);
	Rectangle listBoxRect(rect.getX() + 100, rect.getY() + 20,
			      rect.getX2() - 100, rect.getY2() - 20);
	addListBox(listBoxRect);
	imageManager.setScaleImage(true, getLastImageId());
}

void GUI::addListBoxMessage(const std::string &str, ListBox::MSGtype type)
{
	const wchar_t *text = this->getWC(str.c_str());
	listBox.addText(text, type);
	delete text;
}

int GUI::getLastImageId() const
{
	return imageId;		
}

int GUI::getLastButtonId() const
{
	return buttonId;
}

const wchar_t *GUI::getWC(const char *str)
{
    const size_t cSize = strlen(str) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, str, cSize);
    return (wc);
}