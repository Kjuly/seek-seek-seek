/*
 *	   FILENAME: GraphicCharacter.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	图形学角色，为游戏角色定义骨架、动画、材质。并通过
 *				键盘输入对角色和视角进行即时的更新。
 *					移动等与运动学角色公共的行为由CharacterInputListener
 *				类监听，同时为自身动画的更新进行相应的输入监听。
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

#include "CharacterState.h" // 运动状态集

#define NUM_ANIMS 2           // number of animations the character has
#define CHAR_HEIGHT 3.8        // height of character's center of mass above ground | 角色中心距离地面高度
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
	enum AnimID
	{
		ANIM_RUN,
		ANIM_JUMP,
		ANIM_NONE
	};

public:
	GraphicCharacter( SceneManager * pSceneMgr, CharacterState * pCharacterState );

	Ogre::Entity	* getBodyEnt()	{ return mBodyEnt;	} // 获取角色实体
	Ogre::SceneNode * getBodyNode()	{ return mBodyNode; } // 获取角色节点

	void addTime( Real deltaTime );
	void injectKeyDown( const OIS::KeyEvent & evt );
	void injectKeyUp( const OIS::KeyEvent & evt );
	void injectMouseDown( const OIS::MouseEvent & evt, OIS::MouseButtonID id );

private:
	void setupBody( SceneManager * pSceneMgr );
	void setupAnimations();
	void updateBody( Real deltaTime );
	void updateAnimations( Real deltaTime );
	void fadeAnimations( Real deltaTime );
	void setBaseAnimation( AnimID id, bool reset = false );
	void setTopAnimation( AnimID id, bool reset = false );

	SceneNode		* mBodyNode;
	Entity			* mBodyEnt;
	AnimationState	* mAnims[ NUM_ANIMS ];		// master animation list
	AnimID			  mBaseAnimID;              // current base (full- or lower-body) animation
	AnimID			  mTopAnimID;               // current top (upper-body) animation
	bool			  mFadingIn[ NUM_ANIMS ];   // which animations are fading in
	bool			  mFadingOut[ NUM_ANIMS ];  // which animations are fading out
	Real			  mVerticalVelocity;		// for jumping
	Real			  mTimer;					// general timer to see how long animations have been playing

	bool mRun;									// 标记是否为跑步状态
	CharacterState	* mCharacterState;			// 运动状态集
};

#endif
