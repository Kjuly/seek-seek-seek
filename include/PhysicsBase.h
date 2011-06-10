/*
 *	   FILENAME: PhysicsBase.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	物理世界模拟的最底层设置，为游戏提供创建物理世界的
 *				函数接口，以及必须的对象。
 *					该类主要函数均定义为虚函数，由PhysicsFrameListener
 *				类继承。
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
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h" // Mesh to Shape的转换方法
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"	// for static planes | 实现与plane的碰撞检测
#include "Shapes/OgreBulletCollisionsBoxShape.h"			// for Boxes
#include "Shapes/OgreBulletCollisionsCapsuleShape.h"		// for Capsule
using namespace OgreBulletDynamics;
using namespace OgreBulletCollisions;

// HEADER
#include "GameMap.h"	// 游戏地图

class PhysicsBase : public Ogre::FrameListener
{
public:
    PhysicsBase( Ogre::SceneManager * sceneMgr, GameMap * pMap, Ogre::Vector3 gravityVector, Ogre::AxisAlignedBox bounds );
 	virtual ~PhysicsBase();
	virtual void destroyPhysicsWorld();

	OgreBulletDynamics::DynamicsWorld * getPhysicsWorld(){ return mWorld; }

	virtual void initPhysicsWorld();			// 初始化物理世界
	virtual void createPhysicsTerrain() = 0;	// 构建地形
	virtual void createPhysicsScene()   = 0;	// 在地形基础上构建场景

 	//bool frameStarted( const FrameEvent & evt );
 	//bool frameEnded( const FrameEvent & evt );

protected:
	Ogre::SceneManager				  * mSceneMgr;				// 存储从Ogre传递进来的pSceneMgr
	OgreBulletDynamics::DynamicsWorld * mWorld;					// OgreBullet World	
 	OgreBulletCollisions::DebugDrawer * debugDrawer;			// 用于DeBug描绘绿线
 	int									mNumEntitiesInstanced;	// how many shapes are created
	Ogre::Vector3						mGravityVector;			// 重力
	Ogre::AxisAlignedBox				mBounds;				// 世界框架

	// 物理体集(队列)
 	std::deque< OgreBulletDynamics::RigidBody * >         mBodies; // 物理体队列
 	std::deque< OgreBulletCollisions::CollisionShape * >  mShapes; // 物理形状队列

	// 地形物理体
	GameMap								 * mTerrain;
	OgreBulletDynamics::RigidBody		 * mTerrainPhysicsBody;
 	OgreBulletCollisions::CollisionShape * mTerrainPhysicsShape;
};

#endif
