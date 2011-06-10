/*
 *	   FILENAME: CharacterInputListener.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	对键盘按键的输入进行监听，以统一对图形学角色和运动
 *				学角色的行为进行改变，尤其是移动问题上，运动学角色必须
 *				保持与图形学一致，才能正确地与周围环境进行碰撞检测等物
 *				理行为的模拟。
 * ------------------------------------------------------------------------
 */

#ifndef __CharacterInputListener_H__
#define __CharacterInputListener_H__

#include "CharacterState.h"		// 角色状态
#include "KinematicCharacter.h"	// 运动学角色

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
