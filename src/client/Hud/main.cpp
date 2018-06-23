#include "include.hpp" /* Include Irrklang */
#include "Rectangle.hpp"
#include "GUI.hpp" 
#include <iostream>

#define PATH_TO_RES "../Res/"

int main()
{
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL,
							irr::core::dimension2d<irr::u32>(1920, 1080));
	
	GUI gui(device);	       

	gui.createListBox(Rectangle(LISTBOX_X, LISTBOX_Y, LISTBOX_X2,
				    LISTBOX_Y2),
			  gui.driver->getTexture(PATH_TO_RES PANEL_PNG));

	gui.createTable(Rectangle(TABLE_X, TABLE_Y, TABLE_X2, TABLE_Y2),
			gui.driver->getTexture(PATH_TO_RES PANEL_PNG));
	
	std::vector<const wchar_t *> vec;
	
	vec.push_back(L"Aizen");
	vec.push_back(L"Barragan");
	vec.push_back(L"Ichigo");
	vec.push_back(L"Rukia");
	vec.push_back(L"Orihime");
	vec.push_back(L"Gin");       	
	vec.push_back(L"Ulquiorra");
	vec.push_back(L"Urahara");
	vec.push_back(L"Shinji");

	gui.table.addTeamName(vec);	

	gui.table.setValue(2, 3, L"12");

	gui.table.setValue(L"Level 3", L"Gin", L"99");
	
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL", ListBox::SYSTEM);
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL", ListBox::SYSTEM);	
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL");
	gui.addListBoxMessage(L"TROLOL", ListBox::SYSTEM);
	gui.addListBoxMessage(L"TROLOL");
	
	gui.setFont(PATH_TO_RES "font.xml");
	
	gui.addMenu(Rectangle(MENU_X, MENU_Y, MENU_X2, MENU_Y2));
	gui.menu.server_open();

//	scene->addCameraSceneNodeFPS();	
	gui.device->setResizable(false);
	while (gui.device->run() && gui.driver)
	{
		gui.driver->beginScene(true, true,
				       irr::video::SColor(255,200,255,255));
		gui.isButtonPressed();
		gui.scene->drawAll();
		gui.draw();
		gui.driver->endScene();
	}
}
