/*
 *	   FILENAME: Character.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	游戏角色，由图形学角色(参见GraphicCharacter.h)和运
 *				动学角色(参见KinematicCharacter.h)两部分构成。
 *					其中图形学角色定义角色骨骼、动画等，运动学角色定义
 *				与物理世界的碰撞检测。
 * ------------------------------------------------------------------------
 */

#ifndef __Character_h_
#define __Character_h_

#include "PhysicsFrameListener.h"	// 物理模拟
#include "GraphicCharacter.h"		// 图形学角色
#include "KinematicCharacter.h"		// 运动学角色
#include "CharacterState.h"			// 角色状态

class Character
{
public:
	Character( SceneManager * pSceneMgr, OgreBulletDynamics::DynamicsWorld * pWorld, CharacterState * pCharacterState );
	~Character();

	GraphicCharacter	* getGraphicCharacter()		{ return mGraphicCharacter;	  }	// 获取图形学角色
	KinematicCharacter	* getKinematicCharacter()	{ return mKinematicCharacter; } // 获取运动学角色

	void createGraphicCharacter();			// 构建图形学角色
	void createKinematicCharacter();		// 构建运动学角色
	void update( Ogre::Real deltaTime );	// 更新所有，包括移动、跳跃、着落状态更新等

private:
    Ogre::SceneManager				  * mSceneMgr;			 // Ogre场景控制器

	OgreBulletDynamics::DynamicsWorld * mWorld;				 // 物理学世界
	GraphicCharacter				  * mGraphicCharacter;   // 图形学角色
	KinematicCharacter				  * mKinematicCharacter; // 运动学角色

	CharacterState					  * mCharacterState;	 // 记录输入状态
};

#endif
