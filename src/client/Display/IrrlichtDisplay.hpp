/*
** EPITECH PROJECT, 2018
** IrrlichtDisplay
** File description:
** IrrlichtDisplay
*/

#ifndef IrrlichtDisplay_H_
#define IrrlichtDisplay_H_

#include <irrlicht/irrlicht.h>
#include <iostream>
#include <map>

#include "Map.hpp"

class IrrlichtDisplay {
public:
		IrrlichtDisplay();
		~IrrlichtDisplay();
		void 	Display(Map &map);
		bool	isDeviceRunning(void);
private:
	//! Methodes
	void 	init();
	void 	displayMap(Map &map);
	void 	initTexture();
	void 	render();
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
