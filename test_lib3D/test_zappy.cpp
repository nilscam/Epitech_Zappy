//
// Created by baptiste roubieu on 13/06/2018.
//

//
// Created by baptiste roubieu on 02/06/2018.
//

#include <iostream>
#include "irrlicht/irrlicht.h"

#define TEXTURE_BASE			"./model/wood.jpg"
#define IRON_BOX				"./model/iron_box.png"
#define GRASS				"./model/grass.jpg"


struct          s_map
{
	int	x;
	int y;
	bool egs;
	bool incentation;
	bool stone1;
	bool stone2;
	bool stone3;
	bool stone4;
	bool stone5;
	bool stone6;
};


void		created_fire(float x, float y, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager)
{
	irr::scene::IParticleSystemSceneNode* ps =
			sceneManager->addParticleSystemSceneNode(false);

	irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7), // emitter size
			irr::core::vector3df(0.0f,0.06f,0.0f),   // initial direction
			80,100,                             // emit rate
			irr::video::SColor(0,255,255,255),       // darkest color
			irr::video::SColor(0,255,255,255),       // brightest color
			800,2000,0,                         // min and max age, angle
			irr::core::dimension2df(10.f,10.f),         // min size
			irr::core::dimension2df(20.f,20.f));        // max size

	ps->setEmitter(em); // this grabs the emitter
	em->drop(); // so we can drop it here without deleting it

	irr::scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

	ps->addAffector(paf); // same goes for the affector
	paf->drop();

	ps->setPosition(irr::core::vector3df(x, 0, y));
	ps->setScale(irr::core::vector3df(2,2,2));
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("../model/fire.bmp"));
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void testBaptiste() {
	irr::IrrlichtDevice *device = irr::createDevice(    // creation du device
			irr::video::EDT_OPENGL,                           // API = OpenGL
			irr::core::dimension2d<irr::u32>(800, 800),        // taille fenetre 640x480p
			32);                                              // 32 bits par pixel
	irr::video::IVideoDriver *driver = device->getVideoDriver();                 // creation du driver video
	irr::scene::ISceneManager *sceneManager = device->getSceneManager();          // creation du scene manager
	device->getCursorControl()->setVisible(true);


	s_map map[20];

	for(auto i = 0; i < 20; ++i) {
		for (auto x = 0; x <= 5; ++x) {
			for (auto y = 0; y <= 4; ++y) {
				map[i].x = x;
				map[i].y = y;
				map[i].egs = true;
				map[i].incentation = false;
				map[i].stone1 = true;
				map[i].stone2 = true;
				map[i].stone3 = true;
				map[i].stone4 = true;
				map[i].stone5 = true;
				map[i].stone6 = true;
				i += 1;
				//std::cout << "x: '" << map[i].x << "' ";
				//std::cout << "y: '" << map[i].y << "'" << std::endl;
			}

		}
	}

	float x_pos = 50;
	float y_pos = 50;

	for (int i = 0 ; i < 20; i++)
	{
		//std::cout << "x: '" << map[i].x << "' ";
		//std::cout << "y: '" << map[i].y << "' " << std::endl;
		x_pos = (map[i].x + 1) * 50;
		y_pos = (map[i].y + 1) * 50;

		irr::scene::ISceneNode *block = sceneManager->addCubeSceneNode();
		block->setPosition({x_pos, 0, y_pos});
		block->setScale({5, 5, 5});
		block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		block->setMaterialTexture(0, driver->getTexture(IRON_BOX));

		irr::scene::IAnimatedMesh* mesh = sceneManager->getMesh("./model/PowerGem/gem.dae");
		auto gem = sceneManager->addMeshSceneNode(mesh->getMesh(0));
		gem->setPosition(irr::core::vector3df(static_cast<irr::f32>(x_pos + 5), 28, static_cast<irr::f32>(y_pos + 5)));
		gem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		gem->setScale({0.1, 0.1, 0.1});
		gem->setMaterialTexture(0, driver->getTexture("./model/PowerGem/pinkgem.png"));

		irr::scene::IAnimatedMesh* mesh1 = sceneManager->getMesh("./model/Gem1/LaGem.obj");
		auto gem1 = sceneManager->addMeshSceneNode(mesh->getMesh(0));
		gem1->setPosition(irr::core::vector3df(x_pos + 10, 28, y_pos));
		gem1->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		gem1->setScale({0.1, 0.1, 0.1});
		gem1->setMaterialTexture(0, driver->getTexture("./model/Gem1/Green.png"));

		irr::scene::IAnimatedMesh* mesh2 = sceneManager->getMesh("./model/PowerGem/gem.dae");
		auto gem2 = sceneManager->addMeshSceneNode(mesh->getMesh(0));
		gem2->setPosition(irr::core::vector3df(x_pos, 28, y_pos));
		gem2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		gem2->setScale({0.1, 0.1, 0.1});
		gem2->setMaterialTexture(0, driver->getTexture("./model/PowerGem/purplegem.png"));

		irr::scene::IAnimatedMesh* mesh3= sceneManager->getMesh("./model/Gem1/LaGem.obj");
		auto gem3 = sceneManager->addMeshSceneNode(mesh->getMesh(0));
		gem3->setPosition(irr::core::vector3df(x_pos, 28, y_pos + 10));
		gem3->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		gem3->setScale({0.1, 0.1, 0.1});
		gem3->setMaterialTexture(0, driver->getTexture("./model/Gem1/Red.png"));

		irr::scene::IAnimatedMesh* mesh4= sceneManager->getMesh("./model/Gem1/LaGem.obj");
		auto gem4 = sceneManager->addMeshSceneNode(mesh->getMesh(0));
		gem4->setPosition(irr::core::vector3df(x_pos + 20, 28, y_pos + 10));
		gem4->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		gem4->setScale({0.1, 0.1, 0.1});
		gem4->setMaterialTexture(0, driver->getTexture("./model/Gem1/Blue.png"));

////// Seconde facon de faire

		irr::scene::IAnimatedMeshSceneNode* mesh5 = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("./model/Gem1/LaGem.obj"));
		mesh5->setPosition(irr::core::vector3df(x_pos, 28, y_pos + 20));
		mesh5->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		mesh5->setScale({0.1, 0.1, 0.1});
		mesh5->setMaterialTexture(0, driver->getTexture("./model/Gem1/Yellow.png"));

		irr::scene::IAnimatedMeshSceneNode* egg = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("./model/Egg/YoshiEgg.obj"));
		egg->setPosition(irr::core::vector3df(x_pos - 20, 27.5, y_pos - 15));
		egg->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		egg->setScale({0.1, 0.1, 0.1});
		egg->setMaterialTexture(0, driver->getTexture("./model/Egg/YoshSS00.png"));
		irr::scene::ISceneNodeAnimator* ani= sceneManager->createRotationAnimator(irr::core::vector3df(0,1,0));
		egg->addAnimator(ani);
		ani->drop();

	}

	irr::scene::IAnimatedMeshSceneNode* Jack = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("./model/JDJak/jak.obj"));
	Jack->setPosition(irr::core::vector3df(x_pos, 27.5, y_pos));
	Jack->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	Jack->setScale({1, 1, 1});

	irr::scene::IAnimatedMeshSceneNode* Daxter = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("./model/Daxter/DaxterPants/Daxterpants.obj"));
	Daxter->setPosition(irr::core::vector3df(x_pos - 50, 27.5, y_pos));
	Daxter->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	Daxter->setScale({0.6, 0.6, 0.6});

	driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

	sceneManager->addSkyBoxSceneNode(
			driver->getTexture("./model/irrlicht2_up.jpg"),
			driver->getTexture("./model/irrlicht2_dn.jpg"),
			driver->getTexture("./model/irrlicht2_lf.jpg"),
			driver->getTexture("./model/irrlicht2_rt.jpg"),
			driver->getTexture("./model/irrlicht2_ft.jpg"),
			driver->getTexture("./model/irrlicht2_bk.jpg"));

	driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

	//gem->setPosition({800, 0, 300});
	/*irr::scene::ISceneNode *block = sceneManager->addCubeSceneNode();
	block->setPosition({0, 0, 0});
	block->setScale({10, 10, 10});
	block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	block->setMaterialTexture(0, driver->getTexture(IRON_BOX));*/



	irr::SKeyMap keyMap[5];                             // re-assigne les commandes
	keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
	keyMap[0].KeyCode = irr::KEY_KEY_Z;                 // w
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
	keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
	keyMap[2].KeyCode = irr::KEY_KEY_Q;                 // a
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
	keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
	keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
	keyMap[4].KeyCode = irr::KEY_SPACE;                 // barre espace

	sceneManager->addCameraSceneNodeFPS(0, 1.0 , 1.0f, -1, keyMap, 5);

	/*	 RENDU */
	while (device->run()) {                         // la boucle de rendu
		device->setWindowCaption(L"BOmBiBOOM");
		driver->beginScene(true, true, irr::video::SColor(0, 135, 206, 235));
		//driver->beginScene(true, true, irr::video::SColor(0,255,255,255));
		//driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
		sceneManager->drawAll();                         // calcule le rendu
		driver->endScene();                              // affiche le rendu
	}
	device->drop();
}

int main(void)
{
	testBaptiste();
	return (0);
}