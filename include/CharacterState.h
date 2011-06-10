/*
 *	   FILENAME: CharacterState.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	存储游戏角色的状态，包括是否处于跳跃状态，是否已经
 *				落地，以及角色将要行进的方向。
 *					同时，该类将图形学角色类和运动学角色类之间进行参数
 *				的类型转化，以游戏中统一两者。
 * ------------------------------------------------------------------------
 */

#ifndef __CharacterState_h_
#define __CharacterState_h_

#include <OgreRoot.h>

class CharacterState
{
public:
	CharacterState( Ogre::SceneNode * pCameraNode ) :
		mCameraNode( pCameraNode ),
		mKeyDirection( Ogre::Vector3::ZERO ),
		mGoalDirection( Ogre::Vector3::ZERO ),
		mJump(false),
		mLanded(true)
	{
	}
	~CharacterState(){};

	Ogre::Vector3 getKeyDirection(){ return mKeyDirection; }
	Ogre::Vector3 getGoalDirection()
	{
		mGoalDirection = Ogre::Vector3::ZERO;
		if( mKeyDirection != Ogre::Vector3::ZERO ) {
			mGoalDirection += mKeyDirection.z * mCameraNode->getOrientation().zAxis();
			mGoalDirection += mKeyDirection.x * mCameraNode->getOrientation().xAxis();
			mGoalDirection.y = 0;
			mGoalDirection.normalise();
		}
		return mGoalDirection;
	}
	bool zeroKeyDirection()
	{
		if( mKeyDirection == Ogre::Vector3::ZERO ) return true;
		return false;
	}

	Ogre::Real getKeyDirectionX(){ return mKeyDirection.x; }
	Ogre::Real getKeyDirectionY(){ return mKeyDirection.y; }
	Ogre::Real getKeyDirectionZ(){ return mKeyDirection.z; }
	void setKeyDirectionX( Ogre::Real pX ){ mKeyDirection.x = pX; }
	void setKeyDirectionY( Ogre::Real pY ){ mKeyDirection.y = pY; }
	void setKeyDirectionZ( Ogre::Real pZ ){ mKeyDirection.z = pZ; }

	// -----------------------------------------------------------
	// 状态
	bool getJumpState(){ return mJump; }
	bool getLandedState(){ return mLanded; }

	void setJumpState( bool pJump ){ mJump = pJump; }
	void setLandedState( bool pLanded ){ mLanded = pLanded; }

private:
	Ogre::SceneNode * mCameraNode;		// 跟踪角色 Camera 节点
	Ogre::Vector3	  mKeyDirection;	// 键盘按键方向
	Ogre::Vector3	  mGoalDirection;	// 角色移动实际方向
	bool			  mJump;			// 角色是否处于跳跃状态
	bool			  mLanded;			// 角色是否着落
};

#endif
