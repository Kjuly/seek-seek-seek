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

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	// select the skin
	//CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");

	// set the default mouse cursor
	// the 1st parameter specifies the Imageset and the 2nd one specifies the name of the image to use from that.
	//CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook","MouseArrow");
	CEGUI::System::getSingleton().setDefaultMouseCursor("Vanilla-Images","MouseArrow");
	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor() );

	// set font
	CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");

	//-------------------------------------------------------------
	CEGUI::WindowManager & winMgr = CEGUI::WindowManager::getSingleton();
	//mSheetMain = GUIWinMgr.createWindow("DefaultWindow","Seek/SheetMain");
	// 加载需要使用的背景图片	
	CEGUI::ImagesetManager::getSingleton().createFromImageFile("BackgroundImage", "GPN-2000-001437.tga");
	mSheetMain = winMgr.createWindow("Vanilla/StaticImage");
	// set area rectangle
	mSheetMain->setArea( CEGUI::URect(cegui_reldim(0), cegui_reldim(0), cegui_reldim(1), cegui_reldim(1)) );
	// disable frame & standard background
	mSheetMain->setProperty("FrameEnabled","false");
	mSheetMain->setProperty("BackgroundEnabled","false");
	// set the bg image
	mSheetMain->setProperty("Image","set:BackgroundImage image::full_image");

	//CEGUI::Window * quit = GUIWinMgr.createWindow("TaharezLook/Button","Seek/QuitButton");
	CEGUI::Window * quit = winMgr.createWindow("Vanilla/Button","Seek/QuitButton");
	quit->setText("Quit");
	// width,height; UDim:1:relativ,%; 2:absolute,pix;
	// in this case: 15%width & 5%height compared to Window
	quit->setSize( CEGUI::UVector2( CEGUI::UDim(0.15,0), CEGUI::UDim(0.05,0) ) );
	quit->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::quit, this ) );

	mSheetMain->addChildWindow( quit );
	CEGUI::System::getSingleton().setGUISheet( mSheetMain );

	mSheetMain->activate();

	//------------------------------
	// 隐藏GUI
	mSheetMain->hide();
	CEGUI::MouseCursor::getSingleton().hide();
}
//------------------------------------------------------------------------
void GameGUI::showGUI()
{
	mSheetMain->show();
	CEGUI::MouseCursor::getSingleton().show();
}
//------------------------------------------------------------------------
void GameGUI::hideGUI()
{
	mSheetMain->hide();
	CEGUI::MouseCursor::getSingleton().hide();
}
//------------------------------------------------------------------------
void GameGUI::toggleGUIVisibility()
{
	mSheetMain->isVisible() ? hideGUI() : showGUI();
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

