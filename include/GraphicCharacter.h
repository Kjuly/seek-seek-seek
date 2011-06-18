/*
 *	   FILENAME: GraphicCharacter.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	ͼ��ѧ��ɫ��Ϊ��Ϸ��ɫ����Ǽܡ����������ʡ���ͨ��
 *				��������Խ�ɫ���ӽǽ��м�ʱ�ĸ��¡�
 *					�ƶ������˶�ѧ��ɫ��������Ϊ��CharacterInputListener
 *				�������ͬʱΪ�������ĸ��½�����Ӧ�����������
 * ------------------------------------------------------------------------
 */

#ifndef __GraphicCharacter_H__
#define __GraphicCharacter_H__

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkCameraMan.h>
using namespace Ogre;

#include "CharacterState.h" // �˶�״̬��

#define NUM_ANIMS 2           // number of animations the character has
#define CHAR_HEIGHT 3.8        // height of character's center of mass above ground | ��ɫ���ľ������߶�
#define CAM_HEIGHT 2           // height of camera above character's center of mass
#define RUN_SPEED 17           // character running speed in units per second
#define TURN_SPEED 500.0f      // character turning in degrees per second
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 30.0f       // character jump acceleration in upward units per squared second
#define GRAVITY 90.0f          // gravity in downward units per squared second

class GraphicCharacter
{
private:
	// all the animations our character has, and a null ID
	// some of these affect separate body parts and will be blended together

public:
	GraphicCharacter( SceneManager * pSceneMgr, CharacterState * pCharacterState );

	Ogre::Entity	* getBodyEnt()	{ return mBodyEnt;	} // ��ȡ��ɫʵ��
	Ogre::SceneNode * getBodyNode()	{ return mBodyNode; } // ��ȡ��ɫ�ڵ�

	void addTime( Real deltaTime );
	void injectKeyDown( const OIS::KeyEvent & evt );
	void injectKeyUp( const OIS::KeyEvent & evt );
	void injectMouseDown( const OIS::MouseEvent & evt, OIS::MouseButtonID id );

private:
	void setupBody( SceneManager * pSceneMgr );
	void updateBody( Real deltaTime );

	SceneNode		* mBodyNode;
	Entity			* mBodyEnt;
	Real			  mVerticalVelocity;		// for jumping
	Real			  mTimer;					// general timer to see how long animations have been playing

	bool mRun;									// ����Ƿ�Ϊ�ܲ�״̬
	CharacterState	* mCharacterState;			// �˶�״̬��
};

#endif
