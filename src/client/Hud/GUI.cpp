//
// EPITECH PROJECT, 2018
// zappy
// File description:
// GUI.cpp
//

#include "GUI.hpp"

GUI::GUI(irr::IrrlichtDevice *dev)
{
	device = dev;
	env = device->getGUIEnvironment();
	scene = device->getSceneManager();
	driver = device->getVideoDriver();
	
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

EditBox GUI::addEditBox(const wchar_t *str, const wchar_t *preview,
			Rectangle rect, int id)
{	
	irr::gui::IGUIEditBox *edt = env->addEditBox(preview, rect.get());
        Rectangle txtRect(rect.getX(), rect.getY() - 25,
			  rect.getX2(), rect.getY2() - 25);
	irr::gui::IGUIStaticText *txt = env->addStaticText(str, txtRect.get());

	EditBox box = EditBox(edt, txt, id);
	servPanel.addEditBox(box);
	return box;
}

void GUI::initMenu(int x, int y, int x2, int y2)
{
	addImage(Rectangle(x, y, x2, y2),
		 driver->getTexture(RESSOURCE PANEL_PNG), MENU_PANEL);
	addImage(Rectangle(x - 4, y - 20, x2 + 4, y2 - 500),
		 driver->getTexture(RESSOURCE HEADER_PNG), MENU_HEADER);
	addImage(Rectangle(x - 130, y - 60, x2 + 120, y2 - 440),
		 driver->getTexture(RESSOURCE MENU_TITLE_PNG),
		 MENU_MENU_TEXT);
	addImage(Rectangle(x - 160, y - 60, x2 + 90, y2 - 440),
		 driver->getTexture(RESSOURCE OPTIONS_TITLE_PNG),
		 MENU_OPTIONS_TEXT);
	addImage(Rectangle(x - 130, y - 60, x2 + 120, y2 - 440),
		 driver->getTexture(RESSOURCE CREDITS_TITLE_PNG),
		 MENU_CREDITS_TEXT);
	
	addButton(Rectangle(x + 90, y + 175, x2 - 90, y2 - 405),
		  Button::OPTIONS_OPEN, L"Options", MENU_BTN_OPTIONS);
	addButton(Rectangle(x + 90, y + 275, x2 - 90, y2 - 305),
		  Button::CREDITS_OPEN, L"Credits", MENU_BTN_CREDITS);
	addButton(Rectangle(x + 90, y + 375, x2 - 90, y2 - 205),
		  Button::EXIT, L"Exit", MENU_BTN_EXIT);
	addButton(Rectangle(x + 90, y + 475, x2 - 90, y2 - 105),
		  Button::MENU_CANCEL, L"Cancel", MENU_BTN_CANCEL_MENU);
	addButton(Rectangle(x + 90, y + 475, x2 - 90, y2 - 105),
		  Button::OPTIONS_CANCEL,
		  L"Cancel", MENU_BTN_CANCEL_OPTIONS);
	addButton(Rectangle(x + 90, y + 475, x2 - 90, y2 - 105),
		  Button::CREDITS_CANCEL,
		  L"Cancel", MENU_BTN_CANCEL_CREDITS);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       MENU_BTN_CREDITS);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       MENU_BTN_OPTIONS);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       MENU_BTN_EXIT);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       MENU_BTN_CANCEL_MENU);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       MENU_BTN_CANCEL_OPTIONS);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       MENU_BTN_CANCEL_CREDITS);
	buttonManager.setScaleImage(true, MENU_BTN_OPTIONS);
	buttonManager.setScaleImage(true, MENU_BTN_CREDITS);
	buttonManager.setScaleImage(true, MENU_BTN_EXIT);	
	buttonManager.setScaleImage(true, MENU_BTN_CANCEL_MENU);
	buttonManager.setScaleImage(true, MENU_BTN_CANCEL_OPTIONS);
	buttonManager.setScaleImage(true, MENU_BTN_CANCEL_CREDITS);
	buttonManager.setVisible(false, MENU_BTN_OPTIONS);
	buttonManager.setVisible(false, MENU_BTN_CREDITS);
	buttonManager.setVisible(false, MENU_BTN_EXIT);
	buttonManager.setVisible(false, MENU_BTN_CANCEL_MENU);
	buttonManager.setVisible(false, MENU_BTN_CANCEL_OPTIONS);
	buttonManager.setVisible(false, MENU_BTN_CANCEL_CREDITS);
	imageManager.setScaleImage(true, MENU_PANEL);
	imageManager.setScaleImage(true, MENU_HEADER);
	imageManager.setScaleImage(true, MENU_MENU_TEXT);
	imageManager.setScaleImage(true, MENU_OPTIONS_TEXT);
	imageManager.setScaleImage(true, MENU_CREDITS_TEXT);
	imageManager.setVisible(false, MENU_PANEL);
	imageManager.setVisible(false, MENU_HEADER);
	imageManager.setVisible(false, MENU_MENU_TEXT);
	imageManager.setVisible(false, MENU_OPTIONS_TEXT);
	imageManager.setVisible(false, MENU_CREDITS_TEXT);
}

void GUI::initClient()
{
      	addButton(Rectangle(670, 750,  950, 850),
		  Button::ADD_TEAM1, L"",
		  ADD_TEAM1);
	addButton(Rectangle(1000, 750,  1280, 850),
		  Button::ADD_TEAM2, L"",
		  ADD_TEAM2);
	addButton(Rectangle(670, 890,  950, 990),
		  Button::ADD_TEAM3, L"",
		  ADD_TEAM3);
	addButton(Rectangle(1000, 890,  1280, 990),
		  Button::ADD_TEAM4, L"",
		  ADD_TEAM4);
	addButton(Rectangle(1535, 730, 1635, 780),
		  Button::LAUNCH_GAME, L"Start",
		  LAUNCH_GAME);
	
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       LAUNCH_GAME);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       ADD_TEAM1);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       ADD_TEAM2);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       ADD_TEAM3);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       ADD_TEAM4);

	buttonManager.setVisible(false, LAUNCH_GAME);
	buttonManager.setVisible(false, ADD_TEAM1);
	buttonManager.setVisible(false, ADD_TEAM2);
	buttonManager.setVisible(false, ADD_TEAM3);
	buttonManager.setVisible(false, ADD_TEAM4);
	buttonManager.setScaleImage(true, LAUNCH_GAME);
	buttonManager.setScaleImage(true, ADD_TEAM1);
	buttonManager.setScaleImage(true, ADD_TEAM2);
	buttonManager.setScaleImage(true, ADD_TEAM3);
	buttonManager.setScaleImage(true, ADD_TEAM4);
}
	

void GUI::initSrv2(int x, int y, int x2, int y2)
{
	addEditBox(L"Team 1", L"Melee",
		   Rectangle(x + 250, y + 230, x2 - 700, y2 - 440),
		   EditBox::NAME1);
	addEditBox(L"Team 2", L"Brawl",
		   Rectangle(x + 250, y + 360, x2 - 700, y2 - 310),
		   EditBox::NAME2);
	addEditBox(L"Team 3", L"Smash4",
		   Rectangle(x + 620, y + 230, x2 - 330, y2 - 440),
		   EditBox::NAME3);
	addEditBox(L"Team 4", L"Ultimate",
		   Rectangle(x + 620, y + 360, x2 - 330, y2 - 310),
		   EditBox::NAME4);
	addButton(Rectangle(x + 520, y + 470,  x2 - 600, y2 - 180),
		  Button::SRV_SECOND_OK, L"Ok", SRV_SECOND_OK);
	buttonManager.setScaleImage(true, SRV_SECOND_OK);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			      SRV_SECOND_OK);	
	buttonManager.setVisible(false, SRV_SECOND_OK);	
	servPanel.setVisible(false, EditBox::NAME1);
	servPanel.setVisible(false, EditBox::NAME2);
	servPanel.setVisible(false, EditBox::NAME3);
	servPanel.setVisible(false, EditBox::NAME4);
}

void GUI::initSrv1(int x, int y, int x2, int y2)
{
	addImage(Rectangle(x, y, x2, y2),
		 driver->getTexture(RESSOURCE SRV_PANEL_PNG),
		 MENU_SRV_PANEL);
	addEditBox(L"Port", L"127.0.0.1",
		   Rectangle(x + 250, y + 180, x2 - 700, y2 - 490),
		   EditBox::PORT);
	addEditBox(L"Width", L"20",
		   Rectangle(x + 250, y + 310, x2 - 700, y2 - 360),
		   EditBox::WIDTH);
	addEditBox(L"Height", L"20",
		   Rectangle(x + 250, y + 440, x2 - 700, y2 - 230),
		   EditBox::HEIGHT);
	addEditBox(L"Client", L"12",
		   Rectangle(x + 620, y + 180, x2 - 330, y2 - 490),
		   EditBox::CLIENT);
	addEditBox(L"Freq", L"100",
		   Rectangle(x + 620, y + 310, x2 - 330, y2 - 360),
		   EditBox::FREQ);
	addEditBox(L"Team", L"4",
		   Rectangle(x + 620, y + 440, x2 - 330, y2 - 230),
		   EditBox::TEAM);
	addButton(Rectangle(x + 520, y + 470,  x2 - 600, y2 - 180),
		  Button::SRV_FIRST_OK, L"Ok", SRV_FIRST_OK);
	
	imageManager.setScaleImage(true, MENU_SRV_PANEL);
	imageManager.setVisible(false, MENU_SRV_PANEL);
	buttonManager.setScaleImage(true, SRV_FIRST_OK);
	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			      SRV_FIRST_OK);	
	buttonManager.setVisible(false, SRV_FIRST_OK);	
	servPanel.setVisible(false, EditBox::PORT);
	servPanel.setVisible(false, EditBox::WIDTH);
	servPanel.setVisible(false, EditBox::HEIGHT);
	servPanel.setVisible(false, EditBox::CLIENT);
	servPanel.setVisible(false, EditBox::FREQ);
	servPanel.setVisible(false, EditBox::TEAM);
}

Menu GUI::addMenu(Rectangle rect)
{
	int x = rect.getX();
	int y = rect.getY();
	int x2 = rect.getX2();
	int y2 = rect.getY2();

	initSrv1(SRV_X, SRV_Y, SRV_X2, SRV_Y2);
	initSrv2(SRV_X, SRV_Y, SRV_X2, SRV_Y2);
	initClient();
	addButton(Rectangle(1650, 730, 1750, 780),
		  Button::MENU_OPEN, L"Menu", OPEN_MENU);

	buttonManager.setImage(driver->getTexture(RESSOURCE BTN_PNG),
			       OPEN_MENU);
	
	buttonManager.setScaleImage(true, OPEN_MENU);

	buttonManager.setVisible(true, OPEN_MENU);
	
	initMenu(x, y, x2, y2);
	menu = Menu(&imageManager, &buttonManager, &servPanel);	

	return menu;
}


void GUI::isButtonPressed()
{
	menu.isButtonPressed();
}
