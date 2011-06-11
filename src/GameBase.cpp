#include "GameBase.h"

//-------------------------------------------------------------------------
GameBase::GameBase(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCameraMan(0),
    mDetailsPanel(0),
	mGUIWasVisible(false),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0)
{
}
//-------------------------------------------------------------------------
GameBase::~GameBase(void)
{
    if (mCameraMan) delete mCameraMan;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener( mWindow, this );
    windowClosed( mWindow );
    delete mRoot;
}
//-------------------------------------------------------------------------
void GameBase::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg	  = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg   = "plugins.cfg";
#endif

	// 1-8. Startup Process.
    if (!setup())
        return;

	// 9. Start the render loop.
    mRoot->startRendering();

    // clean up
    destroyScene();
}
//-------------------------------------------------------------------------
bool GameBase::setup(void)
{
	// 1. Create the Root object.
    mRoot = new Ogre::Root(mPluginsCfg);

	// 2. Define the resources that Ogre will use.
    setupResources();

	// 3. Choose and set up the RenderSystem(that is, DirectX, OpenGL, etc).
	// 4. Create the RenderWindow(the Window which Ogre resides in).
    bool carryOn = configure();	// 配置窗口
    if (!carryOn) return false;

    chooseSceneManager();

	// Camera & Viewports
	createCamera();
	createViewports();

    // Set default mipmap level (NB some APIs ignore this)
	// 设置缺省 mipmap 等级
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// 5. Initialize the resources that you are going to use.
    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

	// 6. Create a scene using those resources.
    // Create the scene
    createScene();

	// 7. Set up any third party libraries and plugins.
	// 8. Create any number of frame listeners.
    createFrameListener();

    return true;
};
//-------------------------------------------------------------------------
bool GameBase::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------
void GameBase::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------
void GameBase::loadResources(void)
{
	//--------------------------------
	// 开始加载
//	mLoadingBar.start( mWindow, 1, 1, 0.5 );

	mSceneMgr->clearSpecialCaseRenderQueues();
	mSceneMgr->addSpecialCaseRenderQueue( RENDER_QUEUE_OVERLAY );
	mSceneMgr->setSpecialCaseRenderQueueMode( SceneManager::SCRQM_INCLUDE );

	//-----------------------------------
	// load all resources.
    //Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Popular");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
	//-----------------------------------

	mSceneMgr->clearSpecialCaseRenderQueues();
	mSceneMgr->setSpecialCaseRenderQueueMode( SceneManager::SCRQM_EXCLUDE );

	//--------------------------------
	// 加载结束
//	mLoadingBar.finish();
}
//-------------------------------------------------------------------------
void GameBase::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------
void GameBase::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

//    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
//    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT); // 显示右下角的OGRE Logo
//    mTrayMgr->hideCursor(); // 隐藏鼠标箭头

    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------
void GameBase::destroyScene(void)
{
}
//-------------------------------------------------------------------------
void GameBase::createResourceListener(void)
{
	mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------
/*bool GameBase::frameStarted(const Ogre::FrameEvent& evt)
{
}*/
//-------------------------------------------------------------------------
bool GameBase::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

/*    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
    }
*/
    return true;
}
//-------------------------------------------------------------------------
/*bool GameBase::frameEnded(const Ogre::FrameEvent& evt)
{
}*/
//-------------------------------------------------------------------------
bool GameBase::keyPressed( const OIS::KeyEvent &evt )
{
    //if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    mCameraMan->injectKeyDown(evt);
    return true;
}
//-------------------------------------------------------------------------
bool GameBase::keyReleased( const OIS::KeyEvent & evt )
{
    mCameraMan->injectKeyUp(evt);
    return true;
}
//-------------------------------------------------------------------------
bool GameBase::mouseMoved( const OIS::MouseEvent & evt )
{
	return true;
}
//-------------------------------------------------------------------------
bool GameBase::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	return true;
}
//-------------------------------------------------------------------------
bool GameBase::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	return true;
}
//-------------------------------------------------------------------------
//Adjust mouse clipping area
void GameBase::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
//-------------------------------------------------------------------------
//Unattach OIS before window shutdown (very important under Linux)
void GameBase::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
//-------------------------------------------------------------------------
