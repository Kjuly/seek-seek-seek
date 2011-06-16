#include "GameGUI.h"

//------------------------------------------------------------------------
GameGUI::GameGUI() :
	mGameShutDown(false),
	mCheckDebugMode(false),
	mRadioBgMusicID(1),
	mRadioSceneModeID(1)
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
	// ����ͼ�ν���
	mRenderer = & CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets"); // ��������.imageset�ļ�
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
	// OgreTrayImages ΪͼƬ����OgreTrayImages.png
	// ��������ȡͼƬ����겿�֣����õ����
	CEGUI::System::getSingleton().setDefaultMouseCursor("OgreTrayImages","MouseArrow");
	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor() );

	//-------------------------------------------------------------
	CEGUI::WindowManager & winMgr = CEGUI::WindowManager::getSingleton();
//	mGUIRoot = winMgr.createWindow("DefaultWindow","Seek/SheetMain");
//	mGUIRoot->setPosition( CEGUI::UVector2( CEGUI::UDim(0.0,0), CEGUI::UDim(0.0,0) ) );
	//mGUIRoot->setSize( CEGUI::UVector2( CEGUI::UDim(1.0,0), CEGUI::UDim(0.05,0) ) );

	CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");

	mCEGUIRoot = winMgr.createWindow("DefaultWindow","SeekUIRoot");
	mCEGUIRoot->setPosition( CEGUI::UVector2( CEGUI::UDim(0.0,0), CEGUI::UDim(0.0,0) ) );
	mCEGUIRoot->setSize( CEGUI::UVector2( CEGUI::UDim(1.0,0), CEGUI::UDim(1.0,0) ) );
	
//	mGUIRoot = winMgr.createWindow("DefaultWindow","Seek/SheetMain");
	//mGUIRoot->addChildWindow( winMgr.loadWindowLayout("VanillaWindows.layout") );
	//mGUIRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("KjGUIMenu.layout");
	//mGUIRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("GUIMain.layout");
	mGUIRoot = winMgr.loadWindowLayout("GUIMain.layout");
	mGUIRoot->addChildWindow( winMgr.loadWindowLayout("GUIMain_MenuSet.layout") );	// ���ò˵�
	mGUIRoot->addChildWindow( winMgr.loadWindowLayout("GUIMain_MenuHelp.layout") ); // �����˵�

	CEGUI::ImagesetManager::getSingleton().create("InforUISet.imageset");
	mInforUIRoot = winMgr.createWindow("DefaultWindow","CharacterInforUIRoot");
	mInforUIRoot->setPosition( CEGUI::UVector2( CEGUI::UDim(0.0,0), CEGUI::UDim(0.0,0) ) );
	mInforUIRoot->setSize( CEGUI::UVector2( CEGUI::UDim(1.0,0), CEGUI::UDim(1.0,0) ) );
	mInforUIRoot->addChildWindow( winMgr.loadWindowLayout("InforUI_bot.layout") );	// �ײ���ɫ��Ϣ
	mInforUIRoot->addChildWindow( winMgr.loadWindowLayout("InforUI_top.layout") );	// ������Ϣ

	// ������Ҫʹ�õı���ͼƬ	
/*	CEGUI::ImagesetManager::getSingleton().createFromImageFile("InforUISet", "InforUI.png");
	//mGUIRoot = winMgr.createWindow("TaharezLook/StaticImage","background_wnd");                         //-------
	//mGUIRoot = winMgr.createWindow("Vanilla/StaticImage");
	CEGUI::Window * mInforUIAvatarSintel = winMgr.createWindow("OgreTray/StaticImage");
	// set area rectangle
//	mInforUIAvatarSintel->setArea( CEGUI::URect(cegui_reldim(0), cegui_reldim(0), cegui_reldim(1), cegui_reldim(1)) );
	mInforUIAvatarSintel->setPosition( CEGUI::UVector2(cegui_reldim(0), cegui_reldim(0)) );
	mInforUIAvatarSintel->setSize( CEGUI::UVector2(cegui_reldim(1), cegui_reldim(1)) );
	// disable frame & standard background
	mInforUIAvatarSintel->setProperty("FrameEnabled","false");
	mInforUIAvatarSintel->setProperty("BackgroundEnabled","false");
	mInforUIAvatarSintel->setProperty("Image", "set:InforUISet image:avatarSinter");
	mInforUIAvatarSintel->setProperty("Visible","true");
	mInforUIAvatarSintel->activate();

	mInforUIRoot->addChildWindow( mInforUIAvatarSintel );*/

	mCEGUIRoot->addChildWindow( mGUIRoot );
	mCEGUIRoot->addChildWindow( mInforUIRoot );
	CEGUI::System::getSingleton().setGUISheet( mCEGUIRoot );

	initGUICallbackFunctionSet(); // ��ʼ��GUI�ص�����

	//mGUIRoot->activate();

	// ��ʾInforUI
	mCEGUIRoot->show();
	mInforUIRoot->show();
	//------------------------------
	// ����GUI
	CEGUI::MouseCursor::getSingleton().hide();
	mGUIRoot->hide();
	mGUIRoot->getChild("RootBackground")->disable();
	mGUIRoot->getChild("MenuBack")->hide(); // �Ӳ˵��ķ��ذ�ť
	mGUIRoot->getChild("MenuSet")->hide();
	mGUIRoot->getChild("MenuHelp")->hide();
}
//------------------------------------------------------------------------
bool GameGUI::GUIisVisible()
{
	return mGUIRoot->isVisible();
}
//------------------------------------------------------------------------
void GameGUI::showGUI()
{
	mInforUIRoot->disable();
	mInforUIRoot->hide();

	mGUIRoot->activate();
	mGUIRoot->show();
	CEGUI::MouseCursor::getSingleton().show();
}
//------------------------------------------------------------------------
void GameGUI::hideGUI()
{
	// ���ص�ǰ��ʾ���Ӳ˵������ذ�ť
	if( mGUIRoot->getChild("MenuSet")->isVisible() ) mGUIRoot->getChild("MenuSet")->hide();
	if( mGUIRoot->getChild("MenuHelp")->isVisible() ) mGUIRoot->getChild("MenuHelp")->hide();
	if( mGUIRoot->getChild("MenuBack")->isVisible() ) mGUIRoot->getChild("MenuBack")->hide();

	// �����ص����˵��ָ���ʾ״̬
	if( ! mGUIRoot->getChild("MenuRoot")->isVisible() ) mGUIRoot->getChild("MenuRoot")->show();
	//mGUIRoot->deactivate();
	mGUIRoot->hide();
	CEGUI::MouseCursor::getSingleton().hide();

	mInforUIRoot->show();
	mInforUIRoot->enable();
}
//------------------------------------------------------------------------
void GameGUI::toggleGUIVisibility()
{
	mGUIRoot->isVisible() ? hideGUI() : showGUI();
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
//------------------------------------------------------------------------
void GameGUI::initGUICallbackFunctionSet()
{
	// ������Ϸ
	mGUIRoot->getChild("MenuRoot")->getChild("MenuRoot/But_ReturnToGame")->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::returnToGame, this ) );
	// ����
	mGUIRoot->getChild("MenuRoot")->getChild("MenuRoot/But_Set")->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::showMenuSet, this ) );
	// ����
	mGUIRoot->getChild("MenuRoot")->getChild("MenuRoot/But_Help")->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::showMenuHelp, this ) );
	// �뿪��Ϸ
	mGUIRoot->getChild("MenuRoot")->getChild("MenuRoot/But_Quit")->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::quit, this ) );
	//mGUIRoot->getChild("RootWindow/MainMenu/But_Quit")->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::quit, this ) );
	
	// �Ӳ˵����ذ�ť
	mGUIRoot->getChild("MenuBack")->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::returnToMenuRoot, this ) );


	// ���ò˵����лص�
	//CEGUI::Window * menuSetRoot = mGUIRoot->getChild("MenuSet");
	//mGUIRoot->getChild("MenuSet")->getChild("MenuSet/Tab_3")->getChild("MenuSet/Tab_3/DebugButton")->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( & GameGUI::toggleDebugMode, this ) );
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Callback Functions.
//------------------------------------------------------------------------
bool GameGUI::returnToGame( const CEGUI::EventArgs & evt )
{
	hideGUI();
	return true;
}
//------------------------------------------------------------------------
bool GameGUI::showMenuSet( const CEGUI::EventArgs & evt )
{
	mGUIRoot->getChild("MenuRoot")->hide();
	mGUIRoot->getChild("MenuSet")->show();
	mGUIRoot->getChild("MenuBack")->show();
	return true;
}
//------------------------------------------------------------------------
bool GameGUI::showMenuHelp( const CEGUI::EventArgs & evt )
{
	mGUIRoot->getChild("MenuRoot")->hide();
	mGUIRoot->getChild("MenuHelp")->show();
	mGUIRoot->getChild("MenuBack")->show();
	return true;
}
//------------------------------------------------------------------------
bool GameGUI::quit( const CEGUI::EventArgs & evt )
{
	mGameShutDown = true;
	return true;
}
//------------------------------------------------------------------------
bool GameGUI::returnToMenuRoot( const CEGUI::EventArgs & evt )
{
	if( mGUIRoot->getChild("MenuSet")->isVisible() ) mGUIRoot->getChild("MenuSet")->hide();
	if( mGUIRoot->getChild("MenuHelp")->isVisible() ) mGUIRoot->getChild("MenuHelp")->hide();

	mGUIRoot->getChild("MenuBack")->hide(); // �����Ӳ˵��ķ��ذ�ť
	mGUIRoot->getChild("MenuRoot")->show();	// ��ʾ���˵�
	return true;
}
//------------------------------------------------------------------------
