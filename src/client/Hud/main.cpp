#include "include.hpp"
#include "Rectangle.hpp"
#include "GUI.hpp"
#include <iostream>

int test_hud()
{
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL,
							irr::core::dimension2d<irr::u32>(1920, 1080));

	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::scene::ISceneManager *scene = device->getSceneManager();
	
	GUI gui(device);
	
	std::vector<std::string> vec;
	
	vec.push_back("Aizen");
	vec.push_back("Barragan");
	vec.push_back("Ichigo");
	vec.push_back("Rukia");
	vec.push_back("Orihime");
	vec.push_back("Gin");       	
	vec.push_back("Ulquiorra");
	vec.push_back("Urahara");
	vec.push_back("Shinji");
	gui.table.addTeamName(vec);

	// std::string str("LOL");
	// gui.table.addTeamName({{str}});	
	// gui.table.addTeamName({{"TEST"}});
	// gui.table.addTeamName({{"a"}});
	// gui.table.addTeamName({{"b"}});
	// gui.table.addTeamName({{"c"}});
	// gui.table.addTeamName({{"d"}});
	// gui.table.addTeamName({{"e"}});
	gui.table.setValue(1, 2, "12");
	gui.table.setValue(1, 2, "13");
	gui.table.setValue(1, 2, "14");
	gui.table.setValue("Level 3", "TEST", "99");
	
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL", ListBox::SYSTEM);
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL", ListBox::SYSTEM);	
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL");
	gui.addListBoxMessage("TROLOL", ListBox::SYSTEM);
	gui.addListBoxMessage("TROLOL");
	
	while (device->run() && driver)
	{
		driver->beginScene(true, true, irr::video::SColor(255,200,255,255));		
		scene->drawAll();
		gui.draw();
		driver->endScene();
	}
	return (0);
}
