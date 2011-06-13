/*
 *	   FILENAME: GameBase.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	游戏框架的最底层设置，包括窗口的初始化、游戏资源的
 *				调用、照相机和视角的创建，以及键盘和鼠标的输入监听等。
 *					所有函数定义为虚函数，由SeekSeekSeek类继承。
 * ------------------------------------------------------------------------
 */

#ifndef __GameBase_h_
#define __GameBase_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

//#include "LoadingBar.h"	// 加载进度条

class GameBase :
	public Ogre::FrameListener,
	public Ogre::WindowEventListener,
	public OIS::KeyListener,
	public OIS::MouseListener,
	public OgreBites::SdkTrayListener
{
public:
    GameBase(void);
    virtual ~GameBase(void);

    virtual void go(void);

protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void setupResources(void);
    virtual void loadResources(void);
    virtual void chooseSceneManager(void);
    virtual void createFrameListener(void);
    virtual void createResourceListener(void);

    virtual void createScene(void)		= 0;
	virtual void createCamera(void)		= 0;
	virtual void createViewports(void)	= 0;
    virtual void destroyScene(void);

    // Ogre::FrameListener
    //virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    //virtual bool frameEnded(const Ogre::FrameEvent& evt) = 0;

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent & evt );
    virtual bool keyReleased( const OIS::KeyEvent & evt );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent & evt );
    virtual bool mousePressed( const OIS::MouseEvent & evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent & evt, OIS::MouseButtonID id );

    // Ogre::WindowEventListener | Adjust mouse clipping area
    virtual void windowResized( Ogre::RenderWindow * rw );
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed( Ogre::RenderWindow * rw );

    Ogre::Root			* mRoot;
    Ogre::Camera		* mCamera;
    Ogre::SceneManager	* mSceneMgr;
    Ogre::RenderWindow	* mWindow;
	Ogre::Light			* mLight;
	Ogre::Viewport		* mViewport;

    Ogre::String		  mResourcesCfg;
    Ogre::String		  mPluginsCfg;

    // OgreBites
    OgreBites::SdkCameraMan		* mCameraMan;        // basic camera controller
    bool						  mShutDown;		 // 通过键盘控制退出游戏

    //OIS Input devices
    OIS::InputManager	* mInputManager;
    OIS::Mouse			* mMouse;
    OIS::Keyboard		* mKeyboard;

	//LoadingBar			  mLoadingBar;	// Loging Bar
};

#endif // #ifndef __GameBase_h_
