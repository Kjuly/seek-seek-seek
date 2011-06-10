#include "PhysicsBase.h"
 
// --------------------------------------------------------------------------------
PhysicsBase::PhysicsBase(
		Ogre::SceneManager * pSceneMgr, // 场景控制
		GameMap * pTerrain,				// 游戏地图
		Ogre::Vector3 gravityVector,	// 重力
		Ogre::AxisAlignedBox bounds		// 世界包围大小
		) :
	mSceneMgr( pSceneMgr ),
	mTerrain( pTerrain ),
	mGravityVector( gravityVector ),
	mBounds( bounds )
{
	mNumEntitiesInstanced = 0; // how many shapes are created
}
// --------------------------------------------------------------------------------
PhysicsBase::~PhysicsBase()
{
	destroyPhysicsWorld();
}
// --------------------------------------------------------------------------------
// 初始化物理世界
void PhysicsBase::initPhysicsWorld()
{
    // Dynamics World
    mWorld = new OgreBulletDynamics::DynamicsWorld( mSceneMgr, mBounds, mGravityVector );
	
	// --------------------------------------
	// DeBug Show // we want to see the Bullet containers
 	debugDrawer = new OgreBulletCollisions::DebugDrawer();
 	debugDrawer->setDrawWireframe(true);

 	mWorld->setDebugDrawer( debugDrawer );
	// true绘制绿线，便于debug
	// DebugDrawer需要通过Ogre来绘制，所以需要在Ogre中创建节点node
	// enable it if you want to see the Bullet containers
 	// mWorld->setShowDebugShapes(true);
	// 通过按键改变TRUE or FALSE
	// --------------------------------------

	// --------------------------------------
	createPhysicsTerrain(); // 构造地形
	// --------------------------------------
	createPhysicsScene();	// 基于地形创建环境
	// --------------------------------------
}
// --------------------------------------------------------------------------------
// 释放占用的内存
void PhysicsBase::destroyPhysicsWorld()
{
/*	// 地形
	delete mTerrainPhysicsBody; // OGRE_DELETE
	delete mTerrainPhysicsShape;

	// OgreBullet physic delete - RigidBodies
 	std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
 	while( mBodies.end() != itBody )
	{   
 		delete * itBody;
 		++itBody;
 	}

 	// OgreBullet physic delete - Shapes
 	std::deque<OgreBulletCollisions::CollisionShape *>::iterator itShape = mShapes.begin();
 	while( mShapes.end() != itShape )
 	{   
 		delete * itShape; 
 		++itShape;
 	}
 	mBodies.clear();
 	mShapes.clear();

 	delete mWorld->getDebugDrawer();
 	mWorld->setDebugDrawer(0);
	delete mWorld;
*/
}
// --------------------------------------------------------------------------------
/*bool PhysicsBase::frameStarted( const FrameEvent & evt )
{
	// stepSimulation()方法，使box下坠，而不是悬停于空中
 	//mWorld->stepSimulation( evt.timeSinceLastFrame );	// update Bullet Physics animation
	 
 	return true;
}
// --------------------------------------------------------------------------------
bool PhysicsBase::frameEnded( const FrameEvent & evt )
{
	//mWorld->stepSimulation( evt.timeSinceLastFrame );	// update Bullet Physics animation

 	return true;
}*/
