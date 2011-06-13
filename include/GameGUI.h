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

	//---------------------------------
	// Callback Functions.
	bool returnToGame( const CEGUI::EventArgs & evt );
	bool quit( const CEGUI::EventArgs & evt );

private:
	OgreRenderer	* mRenderer;				// CEGUI 渲染
	Window			* mGUIRoot;					// GUI主窗口
	bool			  mGameShutDown;			// 是否退出游戏
};

#endif // #ifndef __GameGUI_h_
