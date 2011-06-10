#include "PhysicsFrameListener.h"
 
PhysicsFrameListener::PhysicsFrameListener(
		Ogre::SceneManager * pSceneMgr,	// ��������
		GameMap * pTerrain,				// ��Ϸ��ͼ
		Ogre::Vector3 gravityVector,	// ����
		Ogre::AxisAlignedBox bounds		// �����Χ��С
		) :
	PhysicsBase( pSceneMgr, pTerrain, gravityVector, bounds )
{
	initPhysicsWorld(); // ��ʼ���������磬��PhysicsBase���ж���
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
// ��������������
void PhysicsFrameListener::createPhysicsTerrain()
{
	// .scene File Map >>> 5-7-2103
	Ogre::SceneNode										* sceneNode;	// �洢�����ڵ�
	Ogre::String										nodeName;		// ��¼�ڵ���
	OgreBulletCollisions::StaticMeshToShapeConverter	* Converter;	// �� mesh ת��Ϊ shape
	OgreBulletCollisions::CollisionShape				* mSceneShape;	// Collision Shape
	OgreBulletDynamics::RigidBody						* mSceneBody;	// Rigid Body

	for( int i = 1; i <= 14; ++i )
	{
		nodeName = "sLand_" + StringConverter::toString(i);
		sceneNode = mSceneMgr->getSceneNode( nodeName );

		// ??? �����������ƫ�ư���߶�
	//	Vector3 size = sceneNode->_getDerivedScale() * mSceneMgr->getEntity( nodeName )->getBoundingBox().getHalfSize();
		//node->setPosition( position );
	//	mSceneShape = new OgreBulletCollisions::BoxCollisionShape( size );
		Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity( nodeName ) );
		mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh(); // ����������

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
	// ����
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
	// ���ϳ��������
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
	// ��ľ��
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
	// ��ʼ��
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
// �ڵ��λ����Ϲ�������
void PhysicsFrameListener::createPhysicsScene()
{
/*
 * -----------------------------------------------------------------
	Ogre::String nodeName;	// ��¼�ڵ���
	Ogre::Vector3 base, pos;		// ��׼λ��, ��ǰλ��

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

/*	// ��������
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
	// ��ԭʼ�ľ�̬BOX
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
 	entity->setCastShadows(true); // ͶӰ
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
 
	// ����box
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
 			1.0f,					// dynamic body restitution(�ָ�ԭ״)
 			0.3f,					// dynamic body friction(Ħ��)
 			0.2f,					// dynamic bodymass
 			position,				// starting position of the box | Vector3 &
 			Quaternion(0,0,0,1)     // orientation of the box | Quaternion &
			);
 	mNumEntitiesInstanced++;		
 
 	defaultBody->setLinearVelocity( mCamera->getDerivedDirection().normalisedCopy() * Ogre::Math::RangeRandom(0.7f,20.0f) ); // shooting speed | Ͷ�����ӵ��ٶ�
 	// push the created objects to the dequese
 	mShapes.push_back( sceneBoxShape );
 	mBodies.push_back( defaultBody );				
}
// --------------------------------------------------------------------------------
