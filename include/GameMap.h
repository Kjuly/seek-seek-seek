/*
 *	   FILENAME: GameMap.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	��Ϸ��ͼ��Ϊ��Ϸ����������ͼ���Լ��ڵ�ͼ�ϵĳ�����
 *				�Ĵ����ȡ�
 * ------------------------------------------------------------------------
 */


#ifndef __GameMap_h_
#define __GameMap_h_

#include <OISEvents.h>       // ֻ��һ��floor >>> 4-10-2038
#include <OISInputManager.h> // ֻ��һ��floor >>> 4-10-2038
#include <OISKeyboard.h>     // ֻ��һ��floor >>> 4-10-2038
#include <OISMouse.h>        // ֻ��һ��floor >>> 4-10-2038

#include <SdkTrays.h>
#include <SdkCameraMan.h>    // ֻ��һ��floor >>> 4-10-2038

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
