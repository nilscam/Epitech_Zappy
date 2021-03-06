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
#include "ScrollBar.hpp"
#include "ImageManager.hpp"
#include "StaticTextManager.hpp"
#include "ServPanel.hpp"
#include "Menu.hpp"
#include "EID.hpp"
#include <string>

#define LISTBOX_X 0
#define LISTBOX_Y 740
#define LISTBOX_X2 650  /* Param for listBox rectangle */
#define LISTBOX_Y2 1000

#define TABLE_X 1300
#define TABLE_Y 785 
#define TABLE_X2 1825 /* Param for table rectangle */
#define TABLE_Y2 1055

#define SCROLL_X 1290
#define SCROLL_Y 80
#define SCROLL_X2 1840 /* Param for SCROLL rectangle */
#define SCROLL_Y2 140

#define MENU_X 730
#define MENU_Y 220
#define MENU_X2 1180 /* Param for all menu components */
#define MENU_Y2 850

#define SRV_X 400
#define SRV_Y 100
#define SRV_X2 1600
#define SRV_Y2 800

#define PATH_TO_RES "./Ress/hud/"

#define GLOBAL_FONT "font.xml"

#define PANEL_PNG "panel.png"
#define HEADER_PNG "menuTitle.png"
#define BTN_PNG "menuItem.png"
#define SRV_PANEL_PNG "srvPanel.png"

#define MENU_TITLE_PNG "menu.png"
#define OPTIONS_TITLE_PNG "options.png"
#define CREDITS_TITLE_PNG "credits.png"

#define CREDITS_TEXT_PNG "credits_cyril.png"

#define FOOD_PNG "inventory/food.png"
#define LINEMATE_PNG "inventory/linemate.png"
#define DERAUMERE_PNG "inventory/deraumere.png"
#define SIBUR_PNG "inventory/sibur.png"
#define MENDIANE_PNG "inventory/mendiane.png"
#define PHIRAS_PNG "inventory/phiras.png"
#define THYSTAME_PNG "inventory/thystame.png"

class GUI
{
public:
	GUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driv);
	~GUI();

	void	launchGui();

	void addListBoxMessage(const std::string &str, /* Add a string to the chat */
			       ListBox::MSGtype = ListBox::DEFAULT);
	
	void createTable(Rectangle rect, irr::video::ITexture *texture, /* Create the table with a panel.png and coressponding enum*/
			 int id = -1);
	void createListBox(Rectangle rect, irr::video::ITexture *texture, /* Create the chat with a panel.png and coressponding enum*/
			   int id = -1);

	void createScrollbar(Rectangle rect, irr::video::ITexture *texture, /* Create the chat with a panel.png and coressponding enum*/
			   int id = -1);

	CheckBox addCheckBox(Rectangle rect, int id = -1);
	Image addImage(Rectangle rect, irr::video::ITexture *texture,
		       int id = -1, const wchar_t *str = NULL);
	Table addTable(Rectangle rect);
	ListBox addListBox(Rectangle rect);
	Button addButton(Rectangle rect, Button::Action action,
			 const wchar_t *str= L"Unknown", int id = -1);
	EditBox addEditBox(const wchar_t *title, const wchar_t *prev,
			   Rectangle rect, int id);
	StaticText addStaticText(Rectangle rect, int id = -1);
	ScrollBar addScrollBar(Rectangle rect);
	Menu addMenu(Rectangle rect);
	void isButtonPressed();
	
	void draw() const;  /* draw all the element in the loop */
	void setFont(const std::string file); /* set the font to be used */
	irr::gui::IGUIEnvironment *get() const;
	
	int getLastImageId() const;
	int getLastButtonId() const;
	
	void initMenu(int x, int y, int x2, int y2);
	void initSrv1(int x, int y, int x2, int y2);
	void initSrv2(int x, int y, int x2, int y2);
	void initClient();
	void initInventory(int x, int y, int x2, int y2);
	void initTimer(int x, int y, int x2, int y2);
	
	void setTableVisible(bool visible);
	void setListBoxVisible(bool visible);
	void updateTimer(int value);
	void showTimer();

	bool	scrollBarPosChanged();
	int		getPort() const;

	std::shared_ptr<ServerHandler>	getServerHandler(void) const noexcept;
	void	playSound(SoundManager::Sound sound);
	
	ButtonManager buttonManager;
	ImageManager imageManager;
	SoundManager soundManager;
	StaticTextManager staticTextManager;
	CheckBoxManager checkBoxManager;
	Table table;
	ListBox listBox;
	ScrollBar	scrollBar;

	ServPanel servPanel;
	Menu menu;
	
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *scene;
	irr::IrrlichtDevice *device;
	irr::gui::IGUIEnvironment *env;	
private:
	int tableId;
	int listBoxId;
	int buttonId;
	int imageId;
	int	_posScrollBar;
	int scrollBarId;

};

#endif
