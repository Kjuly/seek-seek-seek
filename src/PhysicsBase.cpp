#include "PhysicsBase.h"
 
// --------------------------------------------------------------------------------
PhysicsBase::PhysicsBase(
		Ogre::SceneManager * pSceneMgr, // ��������
		GameMap * pTerrain,				// ��Ϸ��ͼ
		Ogre::Vector3 gravityVector,	// ����
		Ogre::AxisAlignedBox bounds		// �����Χ��С
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
// ��ʼ����������
void PhysicsBase::initPhysicsWorld()
{
    // Dynamics World
    mWorld = new OgreBulletDynamics::DynamicsWorld( mSceneMgr, mBounds, mGravityVector );
	
	// --------------------------------------
	// DeBug Show // we want to see the Bullet containers
 	debugDrawer = new OgreBulletCollisions::DebugDrawer();
 	debugDrawer->setDrawWireframe(true);

 	mWorld->setDebugDrawer( debugDrawer );
	// true�������ߣ�����debug
	// DebugDrawer��Ҫͨ��Ogre�����ƣ�������Ҫ��Ogre�д����ڵ�node
	// enable it if you want to see the Bullet containers
 	// mWorld->setShowDebugShapes(true);
	// ͨ�������ı�TRUE or FALSE
	// --------------------------------------

	// --------------------------------------
	createPhysicsTerrain(); // �������
	// --------------------------------------
	createPhysicsScene();	// ���ڵ��δ�������
	// --------------------------------------
}
// --------------------------------------------------------------------------------
// �ͷ�ռ�õ��ڴ�
void PhysicsBase::destroyPhysicsWorld()
{
/*	// ����
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
	// stepSimulation()������ʹbox��׹����������ͣ�ڿ���
 	//mWorld->stepSimulation( evt.timeSinceLastFrame );	// update Bullet Physics animation
	 
 	return true;
}
// --------------------------------------------------------------------------------
bool PhysicsBase::frameEnded( const FrameEvent & evt )
{
	//mWorld->stepSimulation( evt.timeSinceLastFrame );	// update Bullet Physics animation

 	return true;
}*/
