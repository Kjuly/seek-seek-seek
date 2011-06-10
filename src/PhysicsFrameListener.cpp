#include "PhysicsFrameListener.h"
 
PhysicsFrameListener::PhysicsFrameListener(
		Ogre::SceneManager * pSceneMgr,	// 场景控制
		GameMap * pTerrain,				// 游戏地图
		Ogre::Vector3 gravityVector,	// 重力
		Ogre::AxisAlignedBox bounds		// 世界包围大小
		) :
	PhysicsBase( pSceneMgr, pTerrain, gravityVector, bounds )
{
	initPhysicsWorld(); // 初始化物理世界，在PhysicsBase类中定义
}
// --------------------------------------------------------------------------------
PhysicsFrameListener::~PhysicsFrameListener()
{
	destroyPhysicsWorld();
}
// --------------------------------------------------------------------------------
void PhysicsFrameListener::destroyPhysicsWorld()
{
	PhysicsBase::destroyPhysicsWorld();
}
// --------------------------------------------------------------------------------
// 构建地面物理体
void PhysicsFrameListener::createPhysicsTerrain()
{
	// .scene File Map >>> 5-7-2103
	Ogre::SceneNode										* sceneNode;	// 存储场景节点
	Ogre::String										nodeName;		// 记录节点名
	OgreBulletCollisions::StaticMeshToShapeConverter	* Converter;	// 将 mesh 转换为 shape
	OgreBulletCollisions::CollisionShape				* mSceneShape;	// Collision Shape
	OgreBulletDynamics::RigidBody						* mSceneBody;	// Rigid Body

	for( int i = 1; i <= 14; ++i )
	{
		nodeName = "sLand_" + StringConverter::toString(i);
		sceneNode = mSceneMgr->getSceneNode( nodeName );

		// ??? 物理体会向下偏移半个高度
	//	Vector3 size = sceneNode->_getDerivedScale() * mSceneMgr->getEntity( nodeName )->getBoundingBox().getHalfSize();
		//node->setPosition( position );
	//	mSceneShape = new OgreBulletCollisions::BoxCollisionShape( size );
		Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity( nodeName ) );
		mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh(); // 三角形网格

		mSceneBody = new OgreBulletDynamics::RigidBody( nodeName, mWorld );
		mSceneBody->setStaticShape(
				sceneNode,
				mSceneShape,
				0.6f,								// dynamic body restitution
				0.6f,								// dynamic body friction
				sceneNode->_getDerivedPosition(),   // starting position of the box | Vector3 &
				sceneNode->_getDerivedOrientation() // orientation of the box | Quaternion &
				);
	}
	///------------------------------------
	// 阶梯
	for( int i = 1; i <= 9; ++i )
	{
		nodeName = "StraightStair0" + StringConverter::toString(i);
		std::cout << nodeName << std::endl;

		sceneNode = mSceneMgr->getSceneNode( nodeName );
		Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity( nodeName ) );
		mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh();

		mSceneBody = new OgreBulletDynamics::RigidBody( nodeName, mWorld );
		mSceneBody->setStaticShape(
				sceneNode,
				mSceneShape,
				0.6f,
				0.6f,
				sceneNode->_getDerivedPosition(),
				sceneNode->_getDerivedOrientation()
				);
	}
	///------------------------------------
	// 复合长方体地形
	for( int i = 1; i <= 2; ++i )
	{
		nodeName = "C-Ext0" + StringConverter::toString(i);
		std::cout << nodeName << std::endl;

		sceneNode = mSceneMgr->getSceneNode( nodeName );
		Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity( nodeName ) );
		mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh();

		mSceneBody = new OgreBulletDynamics::RigidBody( nodeName, mWorld );
		mSceneBody->setStaticShape(
				sceneNode,
				mSceneShape,
				0.6f,
				0.6f,
				sceneNode->_getDerivedPosition(),
				sceneNode->_getDerivedOrientation()
				);
	}
	///------------------------------------
	sceneNode = mSceneMgr->getSceneNode("sLand10");
	Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity("sLand10") );
	mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh();

	mSceneBody = new OgreBulletDynamics::RigidBody( "sLand10", mWorld );
	mSceneBody->setStaticShape(
			sceneNode,
			mSceneShape,
			0.6f,
		    0.6f,
		    sceneNode->_getDerivedPosition(),
		    sceneNode->_getDerivedOrientation()
		    );
	///------------------------------------
	// 独木桥
	sceneNode = mSceneMgr->getSceneNode("Cylinder01");
	Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity("Cylinder01") );
	mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh();

	mSceneBody = new OgreBulletDynamics::RigidBody( "Cylinder01", mWorld );
	mSceneBody->setStaticShape(
			sceneNode,
			mSceneShape,
			0.6f,
		    0.6f,
		    sceneNode->_getDerivedPosition(),
		    sceneNode->_getDerivedOrientation()
		    );
	///------------------------------------
	// 起始点
	sceneNode = mSceneMgr->getSceneNode("GeoSphere01");
	Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity("GeoSphere01") );
	mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh();

	mSceneBody = new OgreBulletDynamics::RigidBody( "GeoSphere01", mWorld );
	mSceneBody->setStaticShape(
			sceneNode,
			mSceneShape,
			0.6f,
		    0.6f,
		    sceneNode->_getDerivedPosition(),
		    sceneNode->_getDerivedOrientation()
		    );

	delete Converter;
}
// ------------------------------------------------------------------------
// 在地形基础上构建场景
void PhysicsFrameListener::createPhysicsScene()
{
/*
 * -----------------------------------------------------------------
	Ogre::String nodeName;	// 记录节点名
	Ogre::Vector3 base, pos;		// 基准位置, 当前位置

	base = Ogre::Vector3(0.0,5.0,0.0);
	for( int z = 0; z < 6; ++z )
	for( int x = 0; x < 6; ++x )
	for( int y = 0; y < 6; ++y )
	{
			nodeName = "Box_"	+ StringConverter::toString( x )
								+ StringConverter::toString( y )
								+ StringConverter::toString( z );
			SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode( nodeName );
			Entity * entity = mSceneMgr->createEntity( nodeName, "cube.mesh" );
			entity->setMaterialName( "Examples/BumpyMetal" );
			node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
			node->attachObject( entity );
			node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us

			pos = base + Ogre::Vector3( 5 * x, 5 * y, 5 * z );
			createBoxShape( entity, pos, false );
	}
*/

/*	// 创建盒子
 	SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	Entity * entity = mSceneMgr->createEntity( "Box" + StringConverter::toString( mNumEntitiesInstanced ), "cube.mesh" );
 	entity->setMaterialName( "Examples/BumpyMetal" );
 	node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	node->attachObject( entity );
 	node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us

	createBoxShape( entity, Ogre::Vector3(10.0,5.0,0.0), false );
*/
}
// --------------------------------------------------------------------------------
void PhysicsFrameListener::createBoxShape( Ogre::Entity * entity, Ogre::Vector3 position, bool bStatic /*= false*/ )
{
	// 最原始的静态BOX
	Ogre::SceneNode * node = entity->getParentSceneNode();
	Vector3 size = node->_getDerivedScale() * entity->getBoundingBox().getHalfSize();
    float mass =  bStatic ? 0.0f : 1.0f;
	srand( (unsigned)time( NULL ) );

	//node->setPosition( position );
	node->setOrientation( Quaternion( Degree( Ogre::Math::RangeRandom(0.0,60.0) ), Vector3::UNIT_Y ) );

	OgreBulletCollisions::BoxCollisionShape * sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape( size );

	// and the Bullet rigid body
	OgreBulletDynamics::RigidBody * defaultBody = new OgreBulletDynamics::RigidBody( entity->getName(), mWorld );
	defaultBody->setShape( 
			node,							  // Ogre::SceneNode *
			sceneBoxShape,					  // OgreBulletCollisions::CollisionShape *
			0.6f,                             // dynamic body restitution
		    0.6f,                             // dynamic body friction
		    mass,                             // dynamic bodymass
		    //node->_getDerivedPosition(),      // starting position of the box | Vector3 &
		    position,      // starting position of the box | Vector3 &
		    node->_getDerivedOrientation()  // orientation of the box | Quaternion &
			); 
	mShapes.push_back( sceneBoxShape );
	mBodies.push_back( defaultBody );
	mNumEntitiesInstanced++;				
}
// --------------------------------------------------------------------------------
void PhysicsFrameListener::createBox( Ogre::SceneManager * pSceneMgr, Ogre::Camera * mCamera )
{
 	// create and throw a box if 'B' is pressed
 	Vector3 size = Vector3::ZERO;	// size of the box
 	// starting position of the box
 	Vector3 position = ( mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10 );
 
 	// create an ordinary, Ogre mesh with texture
 	Entity * entity = pSceneMgr->createEntity(
 				"Box" + StringConverter::toString( mNumEntitiesInstanced ),
 				"cube.mesh" );			    
 	entity->setCastShadows(true); // 投影
 	// we need the bounding box of the box to be able to set the size of the Bullet-box
 	AxisAlignedBox boundingB = entity->getBoundingBox();
 	size = boundingB.getSize();
	size /= 2.0f; // only the half needed
 	size *= 1.00f;	// Bullet margin is a bit bigger so we need a smaller size
 					// (Bullet 2.76 Physics SDK Manual page 18)
 	entity->setMaterialName( "Examples/BumpyMetal" );
 	SceneNode * node = pSceneMgr->getRootSceneNode()->createChildSceneNode();
 	node->attachObject( entity );
 	node->scale( 0.02f, 0.02f, 0.02f );	// the cube is too big for us
 	size *= 0.02f;						// don't forget to scale down the Bullet-box too
 
	// 创建box
 	// after that create the Bullet shape with the calculated size
 	OgreBulletCollisions::BoxCollisionShape * sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape( size );
 	// and the Bullet rigid body
 	OgreBulletDynamics::RigidBody * defaultBody = new OgreBulletDynamics::RigidBody(
			"defaultBoxRigid" + StringConverter::toString( mNumEntitiesInstanced ),
			mWorld
			);
 	defaultBody->setShape(
			node,					// Ogre::SceneNode *
			sceneBoxShape,          // OgreBulletCollisions::CollisionShape *
 			1.0f,					// dynamic body restitution(恢复原状)
 			0.3f,					// dynamic body friction(摩擦)
 			0.2f,					// dynamic bodymass
 			position,				// starting position of the box | Vector3 &
 			Quaternion(0,0,0,1)     // orientation of the box | Quaternion &
			);
 	mNumEntitiesInstanced++;		
 
 	defaultBody->setLinearVelocity( mCamera->getDerivedDirection().normalisedCopy() * Ogre::Math::RangeRandom(0.7f,20.0f) ); // shooting speed | 投掷盒子的速度
 	// push the created objects to the dequese
 	mShapes.push_back( sceneBoxShape );
 	mBodies.push_back( defaultBody );				
}
// --------------------------------------------------------------------------------
