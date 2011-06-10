/*
 *	   FILENAME: GameMap.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	游戏地图，为游戏创建基本地图，以及在地图上的场景物
 *				的创建等。
 * ------------------------------------------------------------------------
 */


#ifndef __GameMap_h_
#define __GameMap_h_

#include <OISEvents.h>       // 只是一张floor >>> 4-10-2038
#include <OISInputManager.h> // 只是一张floor >>> 4-10-2038
#include <OISKeyboard.h>     // 只是一张floor >>> 4-10-2038
#include <OISMouse.h>        // 只是一张floor >>> 4-10-2038

#include <SdkTrays.h>
#include <SdkCameraMan.h>    // 只是一张floor >>> 4-10-2038

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

#include "DotSceneLoader.h"		// .scene file Loader

class GameMap// : public GameBase
{
public:
    GameMap(void);
    GameMap( Ogre::SceneManager * pSceneMgr, Ogre::Light * pLight );
    virtual ~GameMap(void);

	Ogre::Entity * getMapEnt() { return mTerrain; }

//protected:
    virtual void cleanMap(void);
    virtual void initMap( Ogre::SceneManager * pSceneMgr, Ogre::Light * pLight );
    //virtual void createFrameListener(void);
    virtual void createFrameListener( OgreBites::SdkTrayManager * pTrayMgr );
    //virtual void frameRenderingQueued(void);
    virtual void frameRenderingQueued( OgreBites::SdkTrayManager * pTrayMgr );
    //virtual void frameRenderingQueued( const Ogre::FrameEvent & evt );

private:
	Ogre::SceneManager			* mSceneMgr;
    Ogre::TerrainGlobalOptions	* mTerrainGlobals;
    Ogre::TerrainGroup			* mTerrainGroup;
    bool						  mTerrainsImported;
    OgreBites::Label			* mInfoLabel;

    void defineTerrain( long x, long y );
    void initBlendMaps( Ogre::Terrain * terrain );
    void configureTerrainDefaults( Ogre::SceneManager * pSceneMgr, Ogre::Light * pLight );

	Ogre::Entity * mTerrain;
};

#endif // #ifndef __GameMap_h_
