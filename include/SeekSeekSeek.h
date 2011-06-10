/*
 *	   FILENAME: SeekSeekSeek.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	��Ϸ���࣬�̳���GameBase������������Ϸ��ɫ����Ϸ��
 *				ͼ�ȶ�����ӵ���Ϸ�н�����Ⱦ�����Ը�����ͼ��̡�����
 *				��ʵʱ�ļ����͸��¡�
 * ------------------------------------------------------------------------
 */

#ifndef __SeekSeekSeek_h_
#define __SeekSeekSeek_h_

#include "GameBase.h"				// ��������
#include "GameMap.h"				// ��Ϸ��ͼ
#include "PhysicsFrameListener.h"	// �����¼�
#include "Character.h"				// ��ɫ
#include "CharacterInputListener.h" // ��ɫ�����������
#include "CharacterState.h"			// �˶�״̬�洢��:���ƶ�������Ծ
#include "OgreALListener.h"			// OgreAL | Ogre Audio Lib | ����������� >>> 5-8-2109
#include "OgreALSoundManager.h"		// OgreAL

#include "CEGUI.h"									// CEGUI
#include "RendererModules/Ogre/CEGUIOgreRenderer.h"

using namespace Ogre;

class SeekSeekSeek : public GameBase
{
public:
    SeekSeekSeek(void);
    virtual ~SeekSeekSeek(void);

protected:
    virtual void createScene(void);		// Scene Main
    virtual void createEnvir(void);     // Environment: Light, Sky, etc.
    virtual void createCamera(void);    // Camera
    virtual void createViewports(void); // Viewport
    virtual void createFrameListener(void);
    virtual void destroyScene(void);
	void initSound(void);				// ��ʼ����������, ��Ч

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener | OIS::MouseListener
    virtual bool keyPressed( const OIS::KeyEvent & evt );
    virtual bool keyReleased( const OIS::KeyEvent & evt );
    virtual bool mouseMoved( const OIS::MouseEvent & evt );
    virtual bool mousePressed( const OIS::MouseEvent & evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent & evt, OIS::MouseButtonID id );
	bool quit( const CEGUI::EventArgs & evt );

	void updateCamera( Real deltaTime );									 // ���� Camera
	void updateCameraGoal( Real deltaYaw, Real deltaPitch, Real deltaZoom ); // ���� Camera Ŀ�귽�� | �����ӽ�

	// �����
	SceneNode * mCameraPivot;	// ���ɫһ������(��򸽽�)�ĵط� | �û�λ��
	SceneNode * mCameraGoal;	// ���Ŀ��
	SceneNode * mCameraNode;	// ʵ�� Camera �ڵ�
	Real mPivotPitch;		// ���������ۼӶ���
	bool mViewTurningLeft;	// ������ת�ӽ�
	bool mViewTurningRight;	// ����
	bool mViewTurningUp;	// ������ת�ӽ�
	bool mViewTurningDown;	// ����
	bool mViewZoomingIn;	// ������ɫ�ӽ�
	bool mViewZoomingOut;	// Զ���ɫ�ӽ�

	GameMap					* mMap;						// ��Ϸ��ͼ
	Character				* mCharacter;				// ��ɫ����
	PhysicsFrameListener	* mPhysicsFrameListener;	// �����¼�����
	CharacterInputListener	* mCharacterInputListener;	// ��ɫ�����������
	CharacterState			* mCharacterState;			// �˶�״̬��

	OgreAL::SoundManager	* mSoundMgr;				// ����
	Ogre::Real				  mBgMusicID;				// ��ǰ���ŵı�������
	Ogre::Real				  mBgFog;					// ������: 0 �ޣ�1 ���� ����2 ҹ�� ����

	bool mDebugMode;									// ����ģʽ�л�

	CEGUI::OgreRenderer		* mRenderer;				// CEGUI ��Ⱦ
};

#endif // #ifndef __SeekSeekSeek_h_
