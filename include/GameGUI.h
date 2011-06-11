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
	bool quit( const CEGUI::EventArgs & evt );

private:
	OgreRenderer	* mRenderer;				// CEGUI ��Ⱦ
	Window			* mSheetMain;				// ������
	bool			  mGameShutDown;			// �Ƿ��˳���Ϸ
};

#endif // #ifndef __GameGUI_h_
