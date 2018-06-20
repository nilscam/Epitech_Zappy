/*
** EPITECH PROJECT, 2018
** IrrlichtDisplay
** File description:
** IrrlichtDisplay
*/

#ifndef IrrlichtDisplay_H_
#define IrrlichtDisplay_H_

#include <irrlicht/irrlicht.h>
#include "Player.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <list>

#include "Map.hpp"
#include "GUI.hpp"

class OldIrrlichtDisplay {
public:
		OldIrrlichtDisplay();
		~OldIrrlichtDisplay();
		void 	Display(Map &map,
						std::map<int, std::shared_ptr<Player>> players,
						std::list<int> idxPlayers,
						std::map<int, Point> eggs,
						std::list<int> idxEggs,
						std::shared_ptr<GUI> gui);
		bool	isDeviceRunning(void);
		irr::IrrlichtDevice		*getDevice(void) const;
private:
	//! Methodes
	void 	init();
	void 	displayMap(Map &map);
	void 	initTexture();
	void 	render(std::shared_ptr<GUI> gui);
	irr::scene::ISceneNode		*create_block(int texture, irr::core::vector3df pos, irr::core::vector3df scale);
	irr::scene::IAnimatedMesh	*create_gem(int texture,
											irr::core::vector3df pos,
											irr::core::vector3df scale);
	irr::scene::IAnimatedMesh	*create_egg(int texture,
											irr::core::vector3df pos,
											irr::core::vector3df scale);
	irr::scene::IAnimatedMesh	*create_mesh(int texture,
											irr::core::vector3df pos,
											irr::core::vector3df scale,
											const irr::io::path& filename);
	irr::scene::ICameraSceneNode	*create_camera();
	void 						create_fx(irr::core::vector3df pos,
										irr::core::vector3df scale);
	void 						create_sky();
	int							random_pos();
	//!--------

	//! Variables
	irr::IrrlichtDevice						*_device;
	irr::video::IVideoDriver				*_driver;
	irr::scene::ISceneManager				*_sceneManager;
	std::map<int, irr::video::ITexture *>	_texture;
};


#endif //IrrlichtDisplay_H_
