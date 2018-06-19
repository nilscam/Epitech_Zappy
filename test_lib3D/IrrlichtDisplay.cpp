//
// Created by baptiste roubieu on 19/06/2018.
//

#include "IrrlichtDisplay.hpp"

#define TEXTURE_BASE			"./model/wood.jpg"
#define IRON_BOX				"./model/iron_box.png"
#define GRASS					"./model/grass.jpg"
#define PURPLE_GEM				"./model/PowerGem/purplegem.png"
#define PINK_GEM				"./model/PowerGem/pinkgem.png"
#define RED_GEM					"./model/Gem1/Red.png"
#define GREEN_GEM				"./model/Gem1/Green.png"
#define	YELLOW_GEM				"./model/Gem1/Yellow.png"
#define BLUE_GEM				"./model/Gem1/Blue.png"
#define YOSHI_EGG				"./model/Egg/YoshSS00.png"

#define TEXTURE_BASE_IDX		0
#define IRON_BOX_IDX			1
#define	GRASS_IDX				2
#define PURPLE_GEM_IDX			3
#define PINK_GEM_IDX			4
#define RED_GEM_IDX				5
#define GREEN_GEM_IDX			6
#define	YELLOW_GEM_IDX			7
#define BLUE_GEM_IDX			8
#define YOSHI_EGG_IDX			9

IrrlichtDisplay::IrrlichtDisplay() {
	this->init();
	this->initTexture();
	this->create_camera();
	this->create_sky();
	_device->setWindowCaption(L"Zappy");
}

IrrlichtDisplay::~IrrlichtDisplay() {
	_device->drop();
}

void IrrlichtDisplay::Display() {
	displayMap();
	render();
}

void IrrlichtDisplay::init() {
	_device = irr::createDevice(    // creation du device
			irr::video::EDT_OPENGL,                           // API = OpenGL
			irr::core::dimension2d<irr::u32>(800, 800),        // taille fenetre 640x480p
			32);                                              // 32 bits par pixel
	_driver = _device->getVideoDriver();                 // creation du driver video
	_sceneManager = _device->getSceneManager();          // creation du scene manager
	_device->getCursorControl()->setVisible(true); //vision du curseur
}

void	IrrlichtDisplay::initTexture()
{
	_texture[TEXTURE_BASE_IDX] = this->_driver->getTexture(TEXTURE_BASE);
	_texture[IRON_BOX_IDX] = this->_driver->getTexture(IRON_BOX);
	_texture[GRASS_IDX] = this->_driver->getTexture(GRASS);
	_texture[PURPLE_GEM_IDX] = this->_driver->getTexture(PURPLE_GEM);
	_texture[PINK_GEM_IDX] = this->_driver->getTexture(PINK_GEM);
	_texture[RED_GEM_IDX] = this->_driver->getTexture(RED_GEM);
	_texture[GREEN_GEM_IDX] = this->_driver->getTexture(GREEN_GEM);
	_texture[YELLOW_GEM_IDX] = this->_driver->getTexture(YELLOW_GEM);
	_texture[BLUE_GEM_IDX] = this->_driver->getTexture(BLUE_GEM);
	_texture[YOSHI_EGG_IDX] = this->_driver->getTexture(YOSHI_EGG);
}

irr::scene::ISceneNode *IrrlichtDisplay::create_block(
		int texture,
		irr::core::vector3df pos,
		irr::core::vector3df scale
) {
	irr::scene::ISceneNode *block = _sceneManager->addCubeSceneNode();
	block->setPosition(pos);
	block->setScale(scale);
	block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	block->setMaterialTexture(0, _texture[texture]);
	return block;
}

void IrrlichtDisplay::displayMap() {
	s_map map[20];

	for(auto i = 0; i < 20; ++i) {
		for (auto x = 0; x <= 5; ++x) {
			for (auto y = 0; y <= 4; ++y) {
				map[i].x = x;
				map[i].y = y;
				// map[i].egs = true;
				// map[i].incentation = false;
				map[i].stone1 = rand() % 3;
				map[i].stone2 = rand() % 3;
				map[i].stone3 = rand() % 3;
				map[i].stone4 = rand() % 3;
				map[i].stone5 = rand() % 3;
				map[i].stone6 = rand() % 3;
				i += 1;
			}

		}
	}

	float x_pos = 50;
	float y_pos = 50;

	for (int i = 0 ; i < 20; i++) {
		x_pos = (map[i].x + 1) * 50;
		y_pos = (map[i].y + 1) * 50;

		create_block(IRON_BOX_IDX, {x_pos, 0, y_pos}, {5, 5, 5});
		create_gem(PURPLE_GEM_IDX, {x_pos + random_pos(), 28, y_pos - random_pos()} , {0.1, 0.1, 0.1});
		create_gem(GREEN_GEM_IDX, {x_pos - random_pos(), 28, y_pos}, {0.1, 0.1, 0.1});
		create_gem(YELLOW_GEM_IDX, {x_pos, 28, y_pos + random_pos()}, {0.1, 0.1, 0.1});
		create_gem(BLUE_GEM_IDX, {x_pos + random_pos(), 28, y_pos}, {0.1, 0.1, 0.1});
		create_gem(PINK_GEM_IDX, {x_pos, 28, y_pos}, {0.1, 0.1, 0.1});
		create_gem(RED_GEM_IDX, {x_pos - random_pos(), 28, y_pos + random_pos()}, {0.1, 0.1, 0.1});

		auto posx_egg = x_pos + random_pos();
		auto posy_egg = y_pos - random_pos();
		create_egg(YOSHI_EGG_IDX, {posx_egg, 27.5, posy_egg}, {0.1, 0.1, 0.1});
		create_fx({posx_egg, 27.5, posy_egg}, {20.0, 20.0, 20.0});
	}
}

irr::scene::IAnimatedMesh *IrrlichtDisplay::create_gem(int texture,
													   irr::core::vector3df pos,
													   irr::core::vector3df scale) {
	irr::scene::IAnimatedMesh* gem = create_mesh(texture, pos, scale, "./model/PowerGem/gem.dae");
	return (gem);
}

irr::scene::IAnimatedMesh *IrrlichtDisplay::create_egg(int texture, irr::core::vector3df pos, irr::core::vector3df scale) {
	irr::scene::IAnimatedMesh* egg = create_mesh(texture, pos, scale, "./model/Egg/YoshiEgg.obj");
	//irr::scene::ISceneNodeAnimator* ani= _sceneManager->createRotationAnimator(irr::core::vector3df(0,1,0));
	/*egg->addAnimator(ani);
	ani->drop();*/
	return (egg);
}

irr::scene::IAnimatedMesh *IrrlichtDisplay::create_mesh(int texture, irr::core::vector3df pos, irr::core::vector3df scale,
							 const irr::io::path &filename) {
	irr::scene::IAnimatedMesh* mesh =_sceneManager->getMesh(filename);
	auto my_mesh = _sceneManager->addMeshSceneNode(mesh->getMesh(0));
	my_mesh->setPosition(pos);
	my_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	my_mesh->setScale(scale);
	my_mesh->setMaterialTexture(0, _texture[texture]);
	return (mesh);
}

irr::scene::ICameraSceneNode *IrrlichtDisplay::create_camera() {
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

	irr::scene::ICameraSceneNode* camera = _sceneManager->addCameraSceneNodeFPS(0, 1.0 , 1.0f, -1, keyMap, 5);
	return (camera);
}

void IrrlichtDisplay::render() {
	while (_device->run()) {
		_driver->beginScene(true, true, irr::video::SColor(0, 135, 206, 235));
		_sceneManager->drawAll();
		_driver->endScene();
	}
}

void IrrlichtDisplay::create_fx(irr::core::vector3df pos, irr::core::vector3df scale) {

	irr::scene::IVolumeLightSceneNode * n = _sceneManager->addVolumeLightSceneNode(0, -1, 32, 32,
																				  irr::video::SColor(0, 255, 255, 255),
																				  irr::video::SColor(0, 0, 0, 0));

	if (n)
	{
		n->setScale(scale);
		n->setPosition(pos);
		irr::core::array<irr::video::ITexture*> textures;
		for (irr::s32 g=7; g > 0; --g)
		{
			irr::core::stringc tmp;
			tmp = "./model/portal";
			tmp += g;
			tmp += ".bmp";
			irr::video::ITexture* t = _driver->getTexture( tmp.c_str() );
			textures.push_back(t);
		}

		// create texture animator
		irr::scene::ISceneNodeAnimator* glow = _sceneManager->createTextureAnimator(textures, 150);
		n->addAnimator(glow);
		glow->drop();
	}
}

int	IrrlichtDisplay::random_pos()
{
	int pos;
	pos = rand() % 20;
	return (pos);
}

void IrrlichtDisplay::create_sky() {
	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

	_sceneManager->addSkyBoxSceneNode(
			_driver->getTexture("./model/irrlicht2_up.jpg"),
			_driver->getTexture("./model/irrlicht2_dn.jpg"),
			_driver->getTexture("./model/irrlicht2_lf.jpg"),
			_driver->getTexture("./model/irrlicht2_rt.jpg"),
			_driver->getTexture("./model/irrlicht2_ft.jpg"),
			_driver->getTexture("./model/irrlicht2_bk.jpg"));

	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

}

bool	IrrlichtDisplay::isDeviceRunning(void)
{
	return (this->_device->run());
}

int main(void)
{
	IrrlichtDisplay display;
	while (display.isDeviceRunning()) {
		display.Display();
	}
	return (0);
}