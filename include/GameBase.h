/*
 *	   FILENAME: GameBase.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	��Ϸ��ܵ���ײ����ã��������ڵĳ�ʼ������Ϸ��Դ��
 *				���á���������ӽǵĴ������Լ����̺�������������ȡ�
 *					���к�������Ϊ�麯������SeekSeekSeek��̳С�
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

#include "LoadingBar.h"	// ���ؽ�����
#include "CEGUI.h"									// CEGUI
#include "RendererModules/Ogre/CEGUIOgreRenderer.h"
#include "GameGUI.h"

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
    bool						  mShutDown;		 // ͨ�����̿����˳���Ϸ

    //OIS Input devices
    OIS::InputManager	* mInputManager;
    OIS::Mouse			* mMouse;
    OIS::Keyboard		* mKeyboard;

	LoadingBar			  mLoadingBar;	// Loging Bar
	GameGUI				* mGUIMgr;					// GUI������
};

#endif // #ifndef __GameBase_h_
