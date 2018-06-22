//
// Created by baptiste roubieu on 19/06/2018.
//

#ifndef IrrlichtDisplay_H_
#define IrrlichtDisplay_H_

#include <irrlicht/irrlicht.h>
#include <iostream>
#include <map>


class IrrlichtDisplay {
public:
		IrrlichtDisplay();
		~IrrlichtDisplay();
		void 	Display();
		bool	isDeviceRunning(void);
private:
	//! Methodes
	void 	init();
	void 	displayMap();
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

	struct          s_map
	{
		int	x;
		int y;
		// bool egs;
		// bool incentation;
		int	food;
		int stone1;
		int stone2;
		int stone3;
		int stone4;
		int stone5;
		int stone6;
	};
};


#endif //IrrlichtDisplay_H_
