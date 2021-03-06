//
// EPITECH PROJECT, 2018
// zappy
// File description:
// GUI.cpp
//

#include "GUI.hpp"

GUI::GUI(irr::IrrlichtDevice *dev, irr::video::IVideoDriver *driv)
{
	device = dev;
	env = device->getGUIEnvironment();
	scene = device->getSceneManager();
	driver = driv;
	tableId = 0;
	listBoxId = 0;
	buttonId = 0;
	imageId = 0;
	this->createListBox(Rectangle(LISTBOX_X, LISTBOX_Y, LISTBOX_X2,
				      LISTBOX_Y2),
			    driver->getTexture(PATH_TO_RES PANEL_PNG),
		LISTBOX_PANEL);
	this->createTable(Rectangle(TABLE_X, TABLE_Y, TABLE_X2, TABLE_Y2),
			  driver->getTexture(PATH_TO_RES PANEL_PNG),
		TABLE_PANEL);
			   
	listBox.setVisible(false);
	table.setVisible(false);
	imageManager.setVisible(false, LISTBOX_PANEL);
	imageManager.setVisible(false, TABLE_PANEL);
	this->setFont(PATH_TO_RES GLOBAL_FONT);
	this->addMenu(Rectangle(MENU_X, MENU_Y, MENU_X2, MENU_Y2));
	
	menu.next_song();
}

GUI::~GUI()
{
}

void	GUI::launchGui()
{
	imageManager.setVisible(true, LISTBOX_PANEL);
	imageManager.setVisible(true, TABLE_PANEL);
	listBox.setVisible(true);
	table.setVisible(true);
	this->showTimer();
	scrollBar.setPos(1);
	_posScrollBar = 1;
	device->setResizable(false);
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

ScrollBar GUI::addScrollBar(Rectangle rect)
{
	auto scrollBr = env->addScrollBar(true, rect.get());
	scrollBarId += 1;
	scrollBar = ScrollBar(scrollBr, scrollBarId);
	return scrollBar;
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

StaticText GUI::addStaticText(Rectangle rect, int id)
{
	irr::gui::IGUIStaticText *text = env->addStaticText(L"Blank",
							    rect.get());
	StaticText texte(text, id);
	staticTextManager.addStaticText(texte);
	return texte;
}

Image GUI::addImage(Rectangle rect, irr::video::ITexture *texture, int id,
		    const wchar_t *str)
{
	irr::gui::IGUIImage *image = env->addImage(rect.get());

	image->setImage(texture);
	image->setUseAlphaChannel(true);
	if (str) {
		image->setToolTipText(str);
	}
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
	(void)texture;
	(void)id;
	imageManager.setScaleImage(true, id);
}

void GUI::createListBox(Rectangle rect, irr::video::ITexture *texture, int id)
{
	addImage(rect, texture, id);
	Rectangle listBoxRect(rect.getX() + 100, rect.getY() + 20,
			      rect.getX2() - 100, rect.getY2() - 20);
	addListBox(listBoxRect);
	imageManager.setScaleImage(true, id);
	imageManager.setScaleImage(true, id);
	(void)texture;
	(void)id;
}

void GUI::createScrollbar(Rectangle rect, irr::video::ITexture *texture, int id)
{
	(void)texture;
	(void)id;
	Rectangle scrollbarRect(rect.getX() + 100, rect.getY() + 20,
			      rect.getX2() - 100, rect.getY2() - 20);
	auto scroll = addScrollBar(scrollbarRect);
}

void GUI::addListBoxMessage(const std::string &str, ListBox::MSGtype type)
{
	const wchar_t *text = char_to_wchar(str.c_str());
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

CheckBox GUI::addCheckBox(Rectangle rect, int id)
{
	irr::gui::IGUICheckBox *chk = env->addCheckBox(false, rect.get(), 0, id);
	CheckBox box = CheckBox(chk, id);
	checkBoxManager.addCheckBox(box);
	return box;
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
		 driver->getTexture(PATH_TO_RES PANEL_PNG), MENU_PANEL);
	addImage(Rectangle(x - 4, y - 20, x2 + 4, y2 - 500),
		 driver->getTexture(PATH_TO_RES HEADER_PNG), MENU_HEADER);
	addImage(Rectangle(x - 130, y - 60, x2 + 120, y2 - 440),
		 driver->getTexture(PATH_TO_RES MENU_TITLE_PNG),
		 MENU_MENU_TEXT);
	addImage(Rectangle(x - 160, y - 60, x2 + 90, y2 - 440),
		 driver->getTexture(PATH_TO_RES OPTIONS_TITLE_PNG),
		 MENU_OPTIONS_TEXT);
	addImage(Rectangle(x - 130, y - 60, x2 + 120, y2 - 440),
		 driver->getTexture(PATH_TO_RES CREDITS_TITLE_PNG),
		 MENU_CREDITS_TEXT);

		addImage(Rectangle(765, 350, 1150, 750),
		 driver->getTexture(PATH_TO_RES CREDITS_TEXT_PNG),
		 MENU_CREDITS_IMG);
	imageManager.setVisible(false, MENU_CREDITS_IMG);
	imageManager.setScaleImage(true, MENU_CREDITS_IMG);
		
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
		  L"Ok", MENU_BTN_CANCEL_OPTIONS);
	addButton(Rectangle(x + 90, y + 475, x2 - 90, y2 - 105),
		  Button::CREDITS_CANCEL,
		  L"Cancel", MENU_BTN_CANCEL_CREDITS);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       MENU_BTN_CREDITS);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       MENU_BTN_OPTIONS);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       MENU_BTN_EXIT);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       MENU_BTN_CANCEL_MENU);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       MENU_BTN_CANCEL_OPTIONS);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
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
	
	addStaticText(Rectangle(875, 388, 1300, 448), MENU_OPTIONS_TEXT_MUSIC);
	staticTextManager.setText("Mute sound", MENU_OPTIONS_TEXT_MUSIC);
	staticTextManager.setVisible(false, MENU_OPTIONS_TEXT_MUSIC);
	
	addStaticText(Rectangle(875, 468, 1300, 528),
		      MENU_OPTIONS_TEXT_LISTBOX);
	staticTextManager.setText("Hide Tchat", MENU_OPTIONS_TEXT_LISTBOX);
	staticTextManager.setVisible(false, MENU_OPTIONS_TEXT_LISTBOX);   

	addStaticText(Rectangle(875, 548, 1300, 608), MENU_OPTIONS_TEXT_TABLE);
	staticTextManager.setText("Hide Scoreboard",MENU_OPTIONS_TEXT_TABLE);
	staticTextManager.setVisible(false, MENU_OPTIONS_TEXT_TABLE);   

	addStaticText(Rectangle(875, 628, 1300, 678), MENU_OPTIONS_TEXT_TIMER);
	staticTextManager.setText("Hide Timer",MENU_OPTIONS_TEXT_TIMER);
	staticTextManager.setVisible(false, MENU_OPTIONS_TEXT_TIMER);   
	
	addCheckBox(Rectangle(830, 375, 860, 425),
		    MENU_OPTIONS_CHECKBOX_MUSIC);
	addCheckBox(Rectangle(830, 455, 860, 505),
		    MENU_OPTIONS_CHECKBOX_LISTBOX);
	addCheckBox(Rectangle(830, 535, 860, 585),
		    MENU_OPTIONS_CHECKBOX_TABLE);
	addCheckBox(Rectangle(830, 615, 860, 665),
		    MENU_OPTIONS_CHECKBOX_TIMER);
	
	checkBoxManager.setVisible(false, MENU_OPTIONS_CHECKBOX_LISTBOX);
	checkBoxManager.setVisible(false, MENU_OPTIONS_CHECKBOX_TABLE);
	checkBoxManager.setVisible(false, MENU_OPTIONS_CHECKBOX_TIMER);
	checkBoxManager.setVisible(false, MENU_OPTIONS_CHECKBOX_MUSIC);
	checkBoxManager.check(false, MENU_OPTIONS_CHECKBOX_LISTBOX);
	checkBoxManager.check(false, MENU_OPTIONS_CHECKBOX_TABLE);
	checkBoxManager.check(false, MENU_OPTIONS_CHECKBOX_TIMER);
	checkBoxManager.check(false, MENU_OPTIONS_CHECKBOX_MUSIC);
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
	addButton(Rectangle(1410, 730, 1510, 780),
		  Button::LAUNCH_GAME, L"Start",
		  LAUNCH_GAME);
	addButton(Rectangle(1650, 670, 1750, 720),
		  Button::CHANGE_SKYBOX, L"SkyBox",
		  CHANGE_SKYBOX);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			CHANGE_SKYBOX);
	buttonManager.setScaleImage(true, CHANGE_SKYBOX);
	buttonManager.setVisible(true, CHANGE_SKYBOX);
	
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       LAUNCH_GAME);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       ADD_TEAM1);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       ADD_TEAM2);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       ADD_TEAM3);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
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

void GUI::initInventory(int x, int y, int x2, int y2)
{
	(void)x;
	(void)y;
	(void)x2;
	(void)y2;

	addImage(Rectangle(30, 30, 530, 230),
		 driver->getTexture(PATH_TO_RES PANEL_PNG),
		 INVENTORY_PANEL);
	imageManager.setScaleImage(true, INVENTORY_PANEL);
	imageManager.setVisible(true, INVENTORY_PANEL);
	
	addImage(Rectangle(130, 100, 190, 160),
		 driver->getTexture(PATH_TO_RES FOOD_PNG),
		 INV_IMG_1, L"Food");
	addImage(Rectangle(220, 60, 280, 120),
		 driver->getTexture(PATH_TO_RES LINEMATE_PNG),
		 INV_IMG_2, L"Linemate");
	addImage(Rectangle(300, 60, 360, 120),
		 driver->getTexture(PATH_TO_RES DERAUMERE_PNG),
		 INV_IMG_3, L"Deraumere");
	addImage(Rectangle(380, 60, 440, 120),
		 driver->getTexture(PATH_TO_RES SIBUR_PNG),
		 INV_IMG_4, L"Sibur");
	addImage(Rectangle(220, 140, 280, 200),
		 driver->getTexture(PATH_TO_RES MENDIANE_PNG),
		 INV_IMG_5, L"Mendiane");
	addImage(Rectangle(300, 140, 360, 200),
		 driver->getTexture(PATH_TO_RES PHIRAS_PNG),
		 INV_IMG_6, L"Phiras");
	addImage(Rectangle(380, 140, 440, 200),
		 driver->getTexture(PATH_TO_RES THYSTAME_PNG),
		 INV_IMG_7, L"Thystame");

	imageManager.setScaleImage(true, INV_IMG_1);
	imageManager.setScaleImage(true, INV_IMG_2);
	imageManager.setScaleImage(true, INV_IMG_3);
	imageManager.setScaleImage(true, INV_IMG_4);
	imageManager.setScaleImage(true, INV_IMG_5);
	imageManager.setScaleImage(true, INV_IMG_6);
	imageManager.setScaleImage(true, INV_IMG_7);
	
	addStaticText(Rectangle(180, 150, 230, 210), INV_VALUE_1);
	staticTextManager.setText("0", INV_VALUE_1);

	addStaticText(Rectangle(270, 100, 330, 160), INV_VALUE_2);
	staticTextManager.setText("0", INV_VALUE_2);

	addStaticText(Rectangle(350, 100, 410, 160), INV_VALUE_3);
	staticTextManager.setText("0", INV_VALUE_3);

	addStaticText(Rectangle(430, 100, 490, 160), INV_VALUE_4);
	staticTextManager.setText("0", INV_VALUE_4);

	addStaticText(Rectangle(270, 180, 330, 240), INV_VALUE_5);
	staticTextManager.setText("0", INV_VALUE_5);

	addStaticText(Rectangle(350, 180, 410, 240), INV_VALUE_6);
	staticTextManager.setText("0", INV_VALUE_6);

	addStaticText(Rectangle(430, 180, 490, 240), INV_VALUE_7);
	staticTextManager.setText("0", INV_VALUE_7);

	imageManager.setVisible(false, INVENTORY_PANEL);
	imageManager.setVisible(false, INV_IMG_1);
	imageManager.setVisible(false, INV_IMG_2);
	imageManager.setVisible(false, INV_IMG_3);
	imageManager.setVisible(false, INV_IMG_4);
	imageManager.setVisible(false, INV_IMG_5);
	imageManager.setVisible(false, INV_IMG_6);
	imageManager.setVisible(false, INV_IMG_7);
	staticTextManager.setVisible(false, INV_VALUE_1);
	staticTextManager.setVisible(false, INV_VALUE_2);
	staticTextManager.setVisible(false, INV_VALUE_3);
	staticTextManager.setVisible(false, INV_VALUE_4);
	staticTextManager.setVisible(false, INV_VALUE_5);
	staticTextManager.setVisible(false, INV_VALUE_6);
	staticTextManager.setVisible(false, INV_VALUE_7);
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
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
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
		 driver->getTexture(PATH_TO_RES SRV_PANEL_PNG),
		 MENU_SRV_PANEL);
	addEditBox(L"Port", L"4242",
		   Rectangle(x + 250, y + 180, x2 - 700, y2 - 490),
		   EditBox::PORT);
	addEditBox(L"Width", L"5",
		   Rectangle(x + 250, y + 310, x2 - 700, y2 - 360),
		   EditBox::WIDTH);
	addEditBox(L"Height", L"5",
		   Rectangle(x + 250, y + 440, x2 - 700, y2 - 230),
		   EditBox::HEIGHT);
	addEditBox(L"Client", L"12",
		   Rectangle(x + 620, y + 180, x2 - 330, y2 - 490),
		   EditBox::CLIENT);
	addEditBox(L"Freq", L"1",
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
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			      SRV_FIRST_OK);	
	buttonManager.setVisible(false, SRV_FIRST_OK);	
	servPanel.setVisible(false, EditBox::PORT);
	servPanel.setVisible(false, EditBox::WIDTH);
	servPanel.setVisible(false, EditBox::HEIGHT);
	servPanel.setVisible(false, EditBox::CLIENT);
	servPanel.setVisible(false, EditBox::FREQ);
	servPanel.setVisible(false, EditBox::TEAM);
}

void GUI::initTimer(int x, int y, int x2, int y2)
{
	(void)x;
	(void)y;
	(void)x2;
	(void)y2;
	
	addImage(Rectangle(1282, 30, 1850, 140),
		 driver->getTexture(PATH_TO_RES PANEL_PNG),
		 TIMER_PANEL);
	imageManager.setScaleImage(true, TIMER_PANEL);	
	
	addStaticText(Rectangle(1400, 60, 1600, 150), TIMER_TEXT_1);
	staticTextManager.setText("f = 0", TIMER_TEXT_1);

	addStaticText(Rectangle(1680, 60, 1800, 150), TIMER_TEXT_2);      
	staticTextManager.setText("0", TIMER_TEXT_2);

	createScrollbar(Rectangle(SCROLL_X, SCROLL_Y, SCROLL_X2,
				  SCROLL_Y2), driver->getTexture(PATH_TO_RES));
	imageManager.setVisible(false, TIMER_PANEL);	
	staticTextManager.setVisible(false, TIMER_TEXT_1);
	staticTextManager.setVisible(false, TIMER_TEXT_2);
	scrollBar.setVisible(false);

}

void GUI::showTimer()
{
	imageManager.setVisible(true, TIMER_PANEL);	
	staticTextManager.setVisible(true, TIMER_TEXT_1);
	staticTextManager.setVisible(true, TIMER_TEXT_2);
	scrollBar.setVisible(true);
}

void GUI::updateTimer(int value)
{
	staticTextManager.setText((std::string("f = ") + std::to_string(scrollBar.getPos())).c_str(), TIMER_TEXT_1);
	staticTextManager.setText((std::string(std::to_string(value))).c_str(), TIMER_TEXT_2);
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
	initInventory(0, 0, 0, 0);
	initTimer(0, 0, 0, 0);
	
	addButton(Rectangle(1650, 730, 1750, 780),
		  Button::MENU_OPEN, L"Menu", OPEN_MENU);
	addButton(Rectangle(1530, 730, 1630, 780),
		  Button::NEXT_SONG, L"Next song", NEXT_SONG);

	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       OPEN_MENU);
	buttonManager.setImage(driver->getTexture(PATH_TO_RES BTN_PNG),
			       NEXT_SONG);
	
	buttonManager.setScaleImage(true, OPEN_MENU);
	buttonManager.setScaleImage(true, NEXT_SONG);

	buttonManager.setVisible(true, OPEN_MENU);
	buttonManager.setVisible(true, NEXT_SONG);
	
	initMenu(x, y, x2, y2);

	// imageManager.setVisible(LISTBOX_PANEL, false);
	// imageManager.setVisible(TABLE_PANEL, false);

	menu = Menu(&imageManager, &buttonManager, &servPanel, &soundManager,
		    &staticTextManager, &checkBoxManager, &table, &listBox,
		    &scrollBar);	

	return menu;
}


void GUI::isButtonPressed()
{
	menu.isButtonPressed();
}

bool	GUI::scrollBarPosChanged()
{
	bool	hasChanged = scrollBar.getPos() != _posScrollBar;
	_posScrollBar = scrollBar.getPos();
	return (hasChanged);
}

int		GUI::getPort() const
{
	return menu.getPort();
}

std::shared_ptr<ServerHandler>	GUI::getServerHandler(void) const noexcept
{
	return menu.getServerHandler();
}

void	GUI::playSound(SoundManager::Sound sound)
{
	soundManager.playSound(sound);
}
