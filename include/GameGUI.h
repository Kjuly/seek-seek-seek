#ifndef __GameGUI_h_
#define __GameGUI_h_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "CEGUI.h"
#include "RendererModules/Ogre/CEGUIOgreRenderer.h"
using namespace CEGUI;

class GameGUI
{
public:
	GameGUI();
	~GameGUI();

	bool GUIisVisible();
	bool gameShutDown();
	void toggleGUIVisibility();

	// 部分信息调用
	bool debugModeSetOn() { return mCheckDebugMode; }
	int getRadioBgMusicID() { return mRadioBgMusicID; }
	int getRadioSceneModeID() { return mRadioSceneModeID; };

	// OIS接入
	void injectKeyPressed( const OIS::KeyEvent & evt );
	void injectKeyReleased( const OIS::KeyEvent & evt );
	void injectMouseMoved( const OIS::MouseEvent & evt );
	void injectMousePressed( OIS::MouseButtonID id );
	void injectMouseReleased( OIS::MouseButtonID id );

protected:
	void initGUI();
	void showGUI();
	void hideGUI();

	void initGUICallbackFunctionSet();

	bool toggleDebugMode( const CEGUI::EventArgs & evt ) { mCheckDebugMode = ! mCheckDebugMode; return true; }
	void setRadioBgMusicID( int pID ) { mRadioBgMusicID = pID; }
	void setRadioSceneModeID( int pID ) { mRadioSceneModeID = pID; }

	//---------------------------------
	// Callback Functions.
	bool returnToGame( const CEGUI::EventArgs & evt );
	bool showMenuSet( const CEGUI::EventArgs & evt );
	bool showMenuHelp( const CEGUI::EventArgs & evt );
	bool quit( const CEGUI::EventArgs & evt );

	bool returnToMenuRoot( const CEGUI::EventArgs & evt );
	//---------------------------------

private:
	OgreRenderer	* mRenderer;				// CEGUI 渲染
	Window			* mCEGUIRoot;				// CEGUI根节点
	Window			* mGUIRoot;					// GUI主窗口
	Window			* mInforUIRoot;				// 游戏进行时角色即时信息
	bool			  mGameShutDown;			// 是否退出游戏
	bool			  mCheckDebugMode;			// 是否设置为调试模式
	int				  mRadioBgMusicID;			// 背景音乐ID
	int				  mRadioSceneModeID;		// 环境效果ID
};

#endif // #ifndef __GameGUI_h_
