/*
 *	   FILENAME: CharacterInputListener.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	�Լ��̰�����������м�������ͳһ��ͼ��ѧ��ɫ���˶�
 *				ѧ��ɫ����Ϊ���иı䣬�������ƶ������ϣ��˶�ѧ��ɫ����
 *				������ͼ��ѧһ�£�������ȷ������Χ����������ײ������
 *				����Ϊ��ģ�⡣
 * ------------------------------------------------------------------------
 */

#ifndef __CharacterInputListener_H__
#define __CharacterInputListener_H__

#include "CharacterState.h"		// ��ɫ״̬
#include "KinematicCharacter.h"	// �˶�ѧ��ɫ

// OIS
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
using namespace OIS;

class CharacterInputListener
{
public:
	CharacterInputListener( KinematicCharacter * pKinematicCharacter, CharacterState * pCharacterState );
	~CharacterInputListener();

	void keyDown( const KeyEvent & evt );
	void keyUp( const KeyEvent & evt );
private:
	KinematicCharacter * mKinematicCharacter;
	CharacterState	   * mCharacterState;
};

#endif
