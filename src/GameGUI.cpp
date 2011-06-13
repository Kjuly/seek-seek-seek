#include "GameGUI.h"

//------------------------------------------------------------------------
GameGUI::GameGUI() :
	mGameShutDown(false)
{
	initGUI();
}
//------------------------------------------------------------------------
GameGUI::~GameGUI()
{
}
//------------------------------------------------------------------------
void GameGUI::initGUI()
{
	// 创建图形界面
	mRenderer = & CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets"); // 加载所有.imageset文件
	// OR: CEGUI::ImagesetManager::getSingleton().createImageset("myImageset.imageset");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	//--------------------------
	// select the skin
	CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");

	//--------------------------
	// set the default mouse cursor
	// the 1st parameter specifies the Imageset and the 2nd one specifies the name of the image to use from that.
	//CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook","MouseArrow");					  //-------
	//CEGUI::System::getSingleton().setDefaultMouseCursor("Vanilla-Images","MouseArrow");
	// OgreTrayImages 为图片名称OgreTrayImages.png
	// 两步：获取图片中鼠标部分，设置到鼠标
	CEGUI::System::getSingleton().setDefaultMouseCursor("OgreTrayImages","MouseArrow");
	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor() );

	//-------------------------------------------------------------
//	CEGUI::WindowManager & winMgr = CEGUI::WindowManager::getSingleton();
//	mGUIRoot = winMgr.createWindow("DefaultWindow","Seek/SheetMain");
//	mGUIRoot->setPosition( CEGUI::UVector2( CEGUI::UDim(0.0,0), CEGUI::UDim(0.0,0) ) );
	//mGUIRoot->setSize( CEGUI::UVector2( CEGUI::UDim(1.0,0), CEGUI::UDim(0.05,0) ) );

	// 加载需要使用的背景图片	
//	CEGUI::ImagesetManager::getSingleton().createFromImageFile("BackgroundImage", "GPN-2000-001437.tga");
	//mGUIRoot = winMgr.createWindow("TaharezLook/StaticImage","background_wnd");                         //-------
	//mGUIRoot = winMgr.createWindow("Vanilla/StaticImage");
//	mGUIRoot = winMgr.createWindow("OgreTray/StaticImage");
	// set area rectangle
//	mGUIRoot->setArea( CEGUI::URect(cegui_reldim(0), cegui_reldim(0), cegui_reldim(1), cegui_reldim(1)) );
	// disable frame & standard background
//	mGUIRoot->setProperty("FrameEnabled","false");
//	mGUIRoot->setProperty("BackgroundEnabled","false");
//	mGUIRoot->setProperty("Image", "set:BackgroundImage image::full_image");


	CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");
	
	//mGUIRoot->addChildWindow( winMgr.loadWindowLayout("VanillaWindows.layout") );
	mGUIRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("KjGUIMenu.layout");
	CEGUI::System::getSingleton().setGUISheet( mGUIRoot );

	//------------------------------
	// 为离开按钮创建监听器
	mGUIRoot->getChild(1)->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::quit, this ) );

	mGUIRoot->activate();

	//------------------------------
	// 隐藏GUI
	mGUIRoot->hide();
	CEGUI::MouseCursor::getSingleton().hide();
}
//------------------------------------------------------------------------
void GameGUI::showGUI()
{
	//mGUIRoot->activate();
	mGUIRoot->show();
	CEGUI::MouseCursor::getSingleton().show();
}
//------------------------------------------------------------------------
void GameGUI::hideGUI()
{
	mGUIRoot->hide();
	CEGUI::MouseCursor::getSingleton().hide();
}
//------------------------------------------------------------------------
void GameGUI::toggleGUIVisibility()
{
	mGUIRoot->isVisible() ? hideGUI() : showGUI();
}
//------------------------------------------------------------------------
bool GameGUI::quit( const CEGUI::EventArgs & evt )
{
	mGameShutDown = true;
	return true;
}
//------------------------------------------------------------------------
bool GameGUI::gameShutDown()
{
	return mGameShutDown;
}

//------------------------------------------------------------------------
void GameGUI::injectKeyPressed( const OIS::KeyEvent & evt )
{
	CEGUI::System & sys = CEGUI::System::getSingleton();
	sys.injectKeyDown( evt.key );
	sys.injectChar( evt.key );
}
//------------------------------------------------------------------------
void GameGUI::injectKeyReleased( const OIS::KeyEvent & evt )
{
	CEGUI::System::getSingleton().injectKeyUp( evt.key );
}
//------------------------------------------------------------------------
void GameGUI::injectMouseMoved( const OIS::MouseEvent & evt )
{
	CEGUI::System & sys = CEGUI::System::getSingleton();
	sys.injectMouseMove( evt.state.X.rel, evt.state.Y.rel );

	if( evt.state.Z.rel )
		sys.injectMouseWheelChange( evt.state.Z.rel / 120.0f );
}
//------------------------------------------------------------------------
CEGUI::MouseButton convertButton( OIS::MouseButtonID buttonID )
{
	switch( buttonID )
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;
	case OIS::MB_Right:
		return CEGUI::RightButton;
	case OIS::MB_Middle:
		return CEGUI::MiddleButton;
	default:
		return CEGUI::LeftButton;
	}
}
// ---------------------------------------------------------------------
void GameGUI::injectMousePressed( OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonDown( convertButton(id) );
}
//------------------------------------------------------------------------
void GameGUI::injectMouseReleased( OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonUp( convertButton(id) );
}
//------------------------------------------------------------------------

