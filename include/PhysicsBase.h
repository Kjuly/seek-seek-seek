/*
 *	   FILENAME: PhysicsBase.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	��������ģ�����ײ����ã�Ϊ��Ϸ�ṩ�������������
 *				�����ӿڣ��Լ�����Ķ���
 *					������Ҫ����������Ϊ�麯������PhysicsFrameListener
 *				��̳С�
 * ------------------------------------------------------------------------
 */

#ifndef __PhysicsBase_h_
#define __PhysicsBase_h_
  
// LIB Ogre
#include <OgreRoot.h>
using namespace Ogre;

// LIB OgreBullet
#include "OgreBulletDynamics.h"
#include "OgreBulletCollisions.h"
#include "OgreBulletDynamicsRigidBody.h"					// for OgreBullet
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h" // Mesh to Shape��ת������
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"	// for static planes | ʵ����plane����ײ���
#include "Shapes/OgreBulletCollisionsBoxShape.h"			// for Boxes
#include "Shapes/OgreBulletCollisionsCapsuleShape.h"		// for Capsule
using namespace OgreBulletDynamics;
using namespace OgreBulletCollisions;

// HEADER
#include "GameMap.h"	// ��Ϸ��ͼ

class PhysicsBase : public Ogre::FrameListener
{
public:
    PhysicsBase( Ogre::SceneManager * sceneMgr, GameMap * pMap, Ogre::Vector3 gravityVector, Ogre::AxisAlignedBox bounds );
 	virtual ~PhysicsBase();
	virtual void destroyPhysicsWorld();

	OgreBulletDynamics::DynamicsWorld * getPhysicsWorld(){ return mWorld; }

	virtual void initPhysicsWorld();			// ��ʼ����������
	virtual void createPhysicsTerrain() = 0;	// ��������
	virtual void createPhysicsScene()   = 0;	// �ڵ��λ����Ϲ�������

 	//bool frameStarted( const FrameEvent & evt );
 	//bool frameEnded( const FrameEvent & evt );

protected:
	Ogre::SceneManager				  * mSceneMgr;				// �洢��Ogre���ݽ�����pSceneMgr
	OgreBulletDynamics::DynamicsWorld * mWorld;					// OgreBullet World	
 	OgreBulletCollisions::DebugDrawer * debugDrawer;			// ����DeBug�������
 	int									mNumEntitiesInstanced;	// how many shapes are created
	Ogre::Vector3						mGravityVector;			// ����
	Ogre::AxisAlignedBox				mBounds;				// ������

	// �����弯(����)
 	std::deque< OgreBulletDynamics::RigidBody * >         mBodies; // ���������
 	std::deque< OgreBulletCollisions::CollisionShape * >  mShapes; // ������״����

	// ����������
	GameMap								 * mTerrain;
	OgreBulletDynamics::RigidBody		 * mTerrainPhysicsBody;
 	OgreBulletCollisions::CollisionShape * mTerrainPhysicsShape;
};

#endif
