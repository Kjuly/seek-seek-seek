/*
 *	   FILENAME: CharacterState.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	�洢��Ϸ��ɫ��״̬�������Ƿ�����Ծ״̬���Ƿ��Ѿ�
 *				��أ��Լ���ɫ��Ҫ�н��ķ���
 *					ͬʱ�����ཫͼ��ѧ��ɫ����˶�ѧ��ɫ��֮����в���
 *				������ת��������Ϸ��ͳһ���ߡ�
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
	// ״̬
	bool getJumpState(){ return mJump; }
	bool getLandedState(){ return mLanded; }

	void setJumpState( bool pJump ){ mJump = pJump; }
	void setLandedState( bool pLanded ){ mLanded = pLanded; }

private:
	Ogre::SceneNode * mCameraNode;		// ���ٽ�ɫ Camera �ڵ�
	Ogre::Vector3	  mKeyDirection;	// ���̰�������
	Ogre::Vector3	  mGoalDirection;	// ��ɫ�ƶ�ʵ�ʷ���
	bool			  mJump;			// ��ɫ�Ƿ�����Ծ״̬
	bool			  mLanded;			// ��ɫ�Ƿ�����
};

#endif
