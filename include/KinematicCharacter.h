/*
 *	   FILENAME: KinematicCharacter.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	运动学角色，为游戏角色定义骨架、动画、材质。并通过
 *	DESCRIPTION:	运动学角色，能够模拟物理世界中的行为：可以贴着地面
 *				行走，可以爬楼梯，等。
 *					移动等与图形学角色公共的行为由CharacterInputListener
 *				类监听。
 *					继承于btKinematicCharacterController类(Bullet库)。
 * ------------------------------------------------------------------------
 */

#ifndef __KinematicCharacter_h_
#define __KinematicCharacter_h_

// LIB Ogre
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>
using namespace Ogre;

// LIB Bullet
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

// LIB OgreBullet
#include "OgreBulletDynamics.h"
#include "OgreBulletCollisions.h"
#include "Utils/OgreBulletConverter.h"
using namespace OgreBulletDynamics;
using namespace OgreBulletCollisions;

// HEADER
#include "btKinematicCharacterController.h"

class KinematicCharacter : public btKinematicCharacterController
{
public:
	KinematicCharacter(
			SceneNode * pNode,
			btPairCachingGhostObject * ghostObject, btConvexShape * convexShape, btScalar stepHeight, int upAxis = 1
			);
	~KinematicCharacter();

	SceneNode * getCharacterNode(){ return mNode; } // 获取角色节点

	///-----------------------------------------------------------
	// 设置角色前进方向 | 调用该方法后覆盖setCharacterVelocityForTimeInterval() | 取其一
	void setCharacterWalkDirection( const Ogre::Vector3 & pGoalDirection );
	// 设置角色前进方向和速度 | 调用该方法后覆盖setCharacterWalkDirection()		| 取其一
	void setCharacterVelocityForTimeInterval( const btVector3 & pVelocity, btScalar pTimeInterval );

	///-----------------------------------------------------------
	// 行为状态
	void doCharacterJump();		// 跳跃
	bool isLanded();			// 角色是否在地上

	///-----------------------------------------------------------
	// 方位
	void getWorldTransform( btTransform & pWorldTrans ) const;
	btTransform getWorldTransform() const;
	void setWorldTransform( const btTransform & pWorldTrans );

protected:
	SceneNode		* mNode;		  // 角色节点
	Ogre::Vector3	  mGoalDirection; // 角色前进方向
};

#endif
