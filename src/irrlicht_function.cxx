#include <irrlicht/irrlicht.h>
#include "trackball.h"
#include "CSceneGcodeNode.h"
#include "gcodeobjet.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


int render(Gcodeobjet* model)
{

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, 
	                                      false, false, false, 0);

	if (!device)
	{
		return 1;
	}

	IVideoDriver *driver = device->getVideoDriver ();
	ISceneManager *scenemanager = device->getSceneManager ();
	IGUIEnvironment *guienv = device->getGUIEnvironment ();
	ICursorControl *cursor = device->getCursorControl();


	// curseur
	cursor->setVisible(true);

	
	//camera
	ICameraSceneNode *camera = scenemanager->addCameraSceneNode(0,
	                                                            vector3df(40.0f, 40.0f, 40.0f),
	                                                            vector3df(0.0f, 0.0f, 0.0f));
	ISceneNodeAnimator *animator = new CSceneNodeAnimatorCameraTrackball(driver, device->getCursorControl(), 50, 2, 3);
	camera->addAnimator(animator);


	//objet
	CSceneGcodeNode* node = new CSceneGcodeNode (scenemanager->getRootSceneNode(), scenemanager);
	node->getGcode (model);
	camera->setTarget (node->getBoundingBox ().getCenter ());
	node->getMaterial(0).Shininess = 25.0f;

	//lumière
	scenemanager->setAmbientLight(SColorf(0.2,0.2,0.2));
	ILightSceneNode* light = scenemanager->addLightSceneNode(camera, vector3df(0.0f,0.0f,0.0f), SColorf(0.6f,0.6f,0.6f,0.0f), 25.0f);
	light->getLightData().SpecularColor = SColorf(0.1f,0.1f,0.1f,0.0f);
	
	while (device->run())
	{
		driver->beginScene(true, true, SColor(0, 255, 255, 255));
		scenemanager->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();
	animator->drop();
	node->drop();

	return 0;
}
