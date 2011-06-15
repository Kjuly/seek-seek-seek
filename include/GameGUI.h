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

	// ������Ϣ����
	bool debugModeSetOn() { return mCheckDebugMode; }
	int getRadioBgMusicID() { return mRadioBgMusicID; }
	int getRadioSceneModeID() { return mRadioSceneModeID; };

	// OIS����
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
	OgreRenderer	* mRenderer;				// CEGUI ��Ⱦ
	Window			* mCEGUIRoot;				// CEGUI���ڵ�
	Window			* mGUIRoot;					// GUI������
	Window			* mInforUIRoot;				// ��Ϸ����ʱ��ɫ��ʱ��Ϣ
	bool			  mGameShutDown;			// �Ƿ��˳���Ϸ
	bool			  mCheckDebugMode;			// �Ƿ�����Ϊ����ģʽ
	int				  mRadioBgMusicID;			// ��������ID
	int				  mRadioSceneModeID;		// ����Ч��ID
};

#endif // #ifndef __GameGUI_h_
