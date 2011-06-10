/*
 *	   FILENAME: KinematicCharacter.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	�˶�ѧ��ɫ��Ϊ��Ϸ��ɫ����Ǽܡ����������ʡ���ͨ��
 *	DESCRIPTION:	�˶�ѧ��ɫ���ܹ�ģ�����������е���Ϊ���������ŵ���
 *				���ߣ�������¥�ݣ��ȡ�
 *					�ƶ�����ͼ��ѧ��ɫ��������Ϊ��CharacterInputListener
 *				�������
 *					�̳���btKinematicCharacterController��(Bullet��)��
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

	SceneNode * getCharacterNode(){ return mNode; } // ��ȡ��ɫ�ڵ�

	///-----------------------------------------------------------
	// ���ý�ɫǰ������ | ���ø÷����󸲸�setCharacterVelocityForTimeInterval() | ȡ��һ
	void setCharacterWalkDirection( const Ogre::Vector3 & pGoalDirection );
	// ���ý�ɫǰ��������ٶ� | ���ø÷����󸲸�setCharacterWalkDirection()		| ȡ��һ
	void setCharacterVelocityForTimeInterval( const btVector3 & pVelocity, btScalar pTimeInterval );

	///-----------------------------------------------------------
	// ��Ϊ״̬
	void doCharacterJump();		// ��Ծ
	bool isLanded();			// ��ɫ�Ƿ��ڵ���

	///-----------------------------------------------------------
	// ��λ
	void getWorldTransform( btTransform & pWorldTrans ) const;
	btTransform getWorldTransform() const;
	void setWorldTransform( const btTransform & pWorldTrans );

protected:
	SceneNode		* mNode;		  // ��ɫ�ڵ�
	Ogre::Vector3	  mGoalDirection; // ��ɫǰ������
};

#endif
