/*
 *	   FILENAME: Character.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	��Ϸ��ɫ����ͼ��ѧ��ɫ(�μ�GraphicCharacter.h)����
 *				��ѧ��ɫ(�μ�KinematicCharacter.h)�����ֹ��ɡ�
 *					����ͼ��ѧ��ɫ�����ɫ�����������ȣ��˶�ѧ��ɫ����
 *				�������������ײ��⡣
 * ------------------------------------------------------------------------
 */

#ifndef __Character_h_
#define __Character_h_

#include "PhysicsFrameListener.h"	// ����ģ��
#include "GraphicCharacter.h"		// ͼ��ѧ��ɫ
#include "KinematicCharacter.h"		// �˶�ѧ��ɫ
#include "CharacterState.h"			// ��ɫ״̬

class Character
{
public:
	Character( SceneManager * pSceneMgr, OgreBulletDynamics::DynamicsWorld * pWorld, CharacterState * pCharacterState );
	~Character();

	GraphicCharacter	* getGraphicCharacter()		{ return mGraphicCharacter;	  }	// ��ȡͼ��ѧ��ɫ
	KinematicCharacter	* getKinematicCharacter()	{ return mKinematicCharacter; } // ��ȡ�˶�ѧ��ɫ

	void createGraphicCharacter();			// ����ͼ��ѧ��ɫ
	void createKinematicCharacter();		// �����˶�ѧ��ɫ
	void update( Ogre::Real deltaTime );	// �������У������ƶ�����Ծ������״̬���µ�

private:
    Ogre::SceneManager				  * mSceneMgr;			 // Ogre����������

	OgreBulletDynamics::DynamicsWorld * mWorld;				 // ����ѧ����
	GraphicCharacter				  * mGraphicCharacter;   // ͼ��ѧ��ɫ
	KinematicCharacter				  * mKinematicCharacter; // �˶�ѧ��ɫ

	CharacterState					  * mCharacterState;	 // ��¼����״̬
};

#endif
