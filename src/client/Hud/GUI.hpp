//
// EPITECH PROJECT, 2018
// zappy
// File description:
// GUI.hpp
//

#ifndef GUI_HPP
#define GUI_HPP

#include "include.hpp"
#include "Rectangle.hpp"
#include "Table.hpp"
#include "ListBox.hpp"
#include "ButtonManager.hpp"
#include "ImageManager.hpp"
#include <string>

#define LISTBOX_X 0
#define LISTBOX_Y 740
#define LISTBOX_X2 650  /* Param for listBox rectangle */
#define LISTBOX_Y2 1000

#define TABLE_X 1300
#define TABLE_Y 785 
#define TABLE_X2 1825 /* Param for table rectangle */
#define TABLE_Y2 955

#define RES_PANEL "panel.png"
#define GLOBAL_FONT "font.xml"

class GUI
{
public:
	enum ID {
		NONE = 100, LISTBOX, TABLE, MENU_HEADER, MENU_TITLE, MENU_PANEL,
		MENU_BTN_EXIT, MENU_BTN_CANCEL, MENU_BTN_OPTIONS,
		MENU_BTN_CREDITS
	};
	GUI(irr::IrrlichtDevice *device);
	~GUI();

	void addListBoxMessage(const wchar_t *str, /* Add a string to the chat */
			       ListBox::MSGtype = ListBox::DEFAULT);
	
	void createTable(Rectangle rect, irr::video::ITexture *texture, /* Create the table with a panel.png and coressponding enum*/
			 int id = -1);
	void createListBox(Rectangle rect, irr::video::ITexture *texture, /* Create the chat with a panel.png and coressponding enum*/
			   int id = -1);
	
	Image addImage(Rectangle rect, irr::video::ITexture *texture,
		       int id = -1);
	Table addTable(Rectangle rect);
	ListBox addListBox(Rectangle rect);
	Button addButton(Rectangle rect, Button::Action action,
			 const wchar_t *str= L"Unknown", int id = -1);
	void draw() const;  /* draw all the element in the loop */
	void setFont(const std::string file); /* set the font to be used */
	irr::gui::IGUIEnvironment *get() const;
	
	int getLastImageId() const;
	int getLastButtonId() const;
	
	void setTableVisible(bool visible);
	void setListBoxVisible(bool visible);
	
	ButtonManager buttonManager;
	ImageManager imageManager;
	Table table;
	ListBox listBox;      
private:
	int tableId;
	int listBoxId;
	int buttonId;
	int imageId;
	irr::gui::IGUIEnvironment *env;
};

#endif
