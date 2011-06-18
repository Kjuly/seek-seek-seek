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

	// ɾ�������е��Զ�����
	while( ! mDynamicObjects.empty() )
	{
		mDynamicObjects.pop_back();
	}
	mDynamicObjects.clear();
}
// --------------------------------------------------------------------------------
// ��������������
void PhysicsFrameListener::createPhysicsTerrain()
{
	createTerrain02();
}
// ------------------------------------------------------------------------
void PhysicsFrameListener::createTerrain01()
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
void PhysicsFrameListener::createTerrain02()
{
	Ogre::SceneNode										* sceneNode;	// �洢�����ڵ�
	Ogre::String										nodeName;		// ��¼�ڵ���
	OgreBulletCollisions::StaticMeshToShapeConverter	* Converter;	// �� mesh ת��Ϊ shape
	OgreBulletCollisions::CollisionShape				* mSceneShape;	// Collision Shape
	OgreBulletDynamics::RigidBody						* mSceneBody;	// Rigid Body
	int i;

	for( i = 1; i <= 66; ++i )
	{
		nodeName = "static_" + StringConverter::toString(i);
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

	// �Զ����� �ƶ�ƽ̨
	// �Զ������˶�Ŀ������
/*	for( i = 1; i <= 2; ++i )
	{
		nodeName = "moveplat_" + StringConverter::toString(i);
		sceneNode = mSceneMgr->getSceneNode( nodeName );

		Vector3 size = sceneNode->_getDerivedScale() * mSceneMgr->getEntity( nodeName )->getBoundingBox().getHalfSize();
		//node->setPosition( position );
		mSceneShape = new OgreBulletCollisions::BoxCollisionShape( size );
	//	Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity( nodeName ) );
	//	mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh(); // ����������

		mSceneBody = new OgreBulletDynamics::RigidBody( nodeName, mWorld );
		mSceneBody->setStaticShape(
				sceneNode,
				mSceneShape,
				0.6f,								// dynamic body restitution
				0.6f,								// dynamic body friction
				sceneNode->_getDerivedPosition(),   // starting position of the box | Vector3 &
				sceneNode->_getDerivedOrientation() // orientation of the box | Quaternion &
				);
	}*/
	// �Զ������˶�Ŀ������
	int listSize = 2;
	Ogre::Vector3 platPosList_1[ 2 ] = { Ogre::Vector3( 173.625, 26.499, 48.527 ), Ogre::Vector3( 173.625, 26.499, -48.816 ) };
	nodeName = "moveplat_" + StringConverter::toString( 1 );
	createSceneObject( mSceneMgr->getEntity( nodeName ), platPosList_1[0], platPosList_1, listSize, true, true );

	Ogre::Vector3 platPosList_2[ 2 ] = { Ogre::Vector3( 0.0, 62.405, -43.0 ), Ogre::Vector3( 0.0, -8.0, -43.0 ) };
	nodeName = "moveplat_" + StringConverter::toString( 2 );
	createSceneObject( mSceneMgr->getEntity( nodeName ), platPosList_2[0], platPosList_2, listSize, true, true );

//	Ogre::Vector3 posList_3[ 3 ] = { Ogre::Vector3( 10.0, 2.0, 0.0 ), Ogre::Vector3( 10.0, 10.0, 10.0 ) };
//	nodeName = "moveplat_" + StringConverter::toString( 3 );
//	createSceneObject( mSceneMgr->getEntity( nodeName ), posList_3[0], posList_3, listSize, true, true );

	// �Զ����� �ϰ���
	// �Զ������˶�Ŀ������
	Ogre::Vector3 blockPosList_2[ 2 ] = { Ogre::Vector3( 140.048, 31.543, -13.214 ), Ogre::Vector3( 207.679, 31.543, -13.214 ) };
	nodeName = "moveblock_" + StringConverter::toString( 2 );
	createSceneObject( mSceneMgr->getEntity( nodeName ), blockPosList_2[0], blockPosList_2, listSize, true, true );

	Ogre::Vector3 blockPosList_3[ 2 ] = { Ogre::Vector3( 207.679, 31.543, 20.228 ), Ogre::Vector3( 140.048, 31.543, 20.228 ) };
	nodeName = "moveblock_" + StringConverter::toString( 3 );
	createSceneObject( mSceneMgr->getEntity( nodeName ), blockPosList_3[0], blockPosList_3, listSize, true, true );
/*	for( i = 1; i <= 3; ++i )
	{
		nodeName = "moveblock_" + StringConverter::toString(i);
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
*/
/*	int listSize = 3;
	Ogre::Vector3 posList[ 2 ] = { Ogre::Vector3( 140.048, 31.542, 20.228 ), Ogre::Vector3( 207.679, 31.542, 20.228 ) };
	for( i = 1; i <= 3; ++i )
	{
		nodeName = "moveblock_" + StringConverter::toString(i);
		sceneNode = mSceneMgr->getSceneNode( nodeName );
		//std::cout << "***** " << sceneNode->_ << std::endl;
		createSceneObject( mSceneMgr->getEntity( nodeName ), posList[0], posList, listSize, true, true );
	}
*/
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
			createSceneObject( entity, pos, false );
	}
*/

	// ����Ŀ��
 	SceneNode * goalNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	Entity * goalEntity = mSceneMgr->createEntity( "Scales", "Scales.mesh" );
 	goalNode->attachObject( goalEntity );
	goalNode->setPosition( Ogre::Vector3(108.0f,125.0f,-82.346f) );
 	goalNode->scale(1.0f, 1.0f, 1.0f);	// the cube is too big for us
	goalNode->yaw( Ogre::Degree(-180) );
	//createSceneObject( entity, Ogre::Vector3(10.0,5.0,0.0), false );

	// ��������
/* 	SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	Entity * entity = mSceneMgr->createEntity( "Box" + StringConverter::toString( mNumEntitiesInstanced ), "cube.mesh" );
 	entity->setMaterialName( "Examples/BumpyMetal" );
 	node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	node->attachObject( entity );
 	node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us

	// �Զ������˶�Ŀ������
	int listSize = 3;
	Ogre::Vector3 posList[ 3 ] = {
		Ogre::Vector3( 10.0, 2.0, 0.0 ),
		Ogre::Vector3( 10.0, 10.0, 10.0 ),
		Ogre::Vector3( 0.0, 2.0, 5.0 )
	};
	createSceneObject( entity, Ogre::Vector3(10.0,5.0,0.0), posList, listSize, true, true );
*/
}
// --------------------------------------------------------------------------------
// ��������־�̬�Ͷ�̬����: ��̬:�����ƶ� ��̬:���ƶ�
// ͬʱ�ַ��Զ��ͷ��Զ�: �Զ�:�Լ����ƶ����ϰ���ȶ���
void PhysicsFrameListener::createSceneObject( Ogre::Entity * entity, Ogre::Vector3 origPos,
		Ogre::Vector3 pPosList[], int pPosNum, // �˶�Ŀ������
		bool bStatic /*= false*/, bool autoMove /*= false*/
		)
{
	// ��ԭʼ�ľ�̬BOX
	Ogre::SceneNode * node = entity->getParentSceneNode();
	Ogre::Vector3 size = node->_getDerivedScale() * entity->getBoundingBox().getHalfSize();
    float mass =  bStatic ? 0.0f : 1.0f;
	srand( (unsigned)time( NULL ) );

	//node->setPosition( origPos );
	node->setOrientation( Quaternion( Degree( Ogre::Math::RangeRandom(0.0,60.0) ), Ogre::Vector3::UNIT_Y ) );

	OgreBulletCollisions::BoxCollisionShape * sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape( size );

	// ���ǳ������Զ�����
	if( ! autoMove )
	{
		// and the Bullet rigid body
		OgreBulletDynamics::RigidBody * rigidBody = new OgreBulletDynamics::RigidBody( entity->getName(), mWorld );
		rigidBody = new OgreBulletDynamics::RigidBody( entity->getName(), mWorld );
		rigidBody->setShape( 
				node,							  // Ogre::SceneNode *
				sceneBoxShape,					  // OgreBulletCollisions::CollisionShape *
				0.6f,                             // dynamic body restitution
				0.6f,                             // dynamic body friction
				mass,                             // dynamic bodymass
				//node->_getDerivedPosition(),      // starting position of the box | Vector3 &
				origPos,      // starting position of the box | Vector3 &
				node->_getDerivedOrientation()  // orientation of the box | Quaternion &
				); 
		mShapes.push_back( sceneBoxShape );
		mBodies.push_back( rigidBody );
		mNumEntitiesInstanced++;
	}
	// ���Զ����������Զ��������
	else
	{
		DynamicObject dynamicObject; // �����Զ�����

		dynamicObject.rigidBody = new OgreBulletDynamics::RigidBody( entity->getName(), mWorld );
		dynamicObject.rigidBody->setShape( 
				node,							  // Ogre::SceneNode *
				sceneBoxShape,					  // OgreBulletCollisions::CollisionShape *
				1.0f,                             // dynamic body restitution
				1.0f,                             // dynamic body friction
				mass,                             // dynamic bodymass
				//node->_getDerivedPosition(),      // starting position of the box | Vector3 &
				origPos,      // starting position of the box | Vector3 &
				node->_getDerivedOrientation()  // orientation of the box | Quaternion &
				); 
		dynamicObject.graphicBody	= node;
		dynamicObject.currPosID		= 0;
		dynamicObject.posNum		= pPosNum;
		dynamicObject.moveStep		= Ogre::Vector3(0.05,0.05,0.05);

		for( int i = 0; i < pPosNum; ++i )
			dynamicObject.posList.push_back( pPosList[ i ] );

		mDynamicObjects.push_back( dynamicObject );
		mNumEntitiesInstanced++;
	}
}
// --------------------------------------------------------------------------------
void PhysicsFrameListener::createBox( Ogre::SceneManager * pSceneMgr, Ogre::Camera * mCamera )
{
 	// create and throw a box if 'B' is pressed
	Ogre::Vector3 size = Ogre::Vector3::ZERO;	// size of the box
 	// starting position of the box
	Ogre::Vector3 position = ( mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10 );
 
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
// ���·���ҿ��ƶ���
void PhysicsFrameListener::updateNPCObject()
{
	updateDynamicObject();	// �����ƶ�����
}
// --------------------------------------------------------------------------------
// �����Զ������˶�
void PhysicsFrameListener::updateDynamicObject()
{
	btTransform pos;
	Ogre::Vector3 targetPos;

	for( int i = 0; i < mDynamicObjects.size(); ++i )
	{
		pos = mDynamicObjects.at( i ).rigidBody->getBulletRigidBody()->getWorldTransform();

		// ��ȡ��i������ǰ�����ά����
		//Ogre::Vector3 currPoint = mDynamicObjects.at( i ).posList.at( mDynamicObjects.at( i ).currPosID );
		// ��ȡ��i�������ƶ�ʱ��һ�������ά����
		Ogre::Vector3 nextPoint = mDynamicObjects.at( i ).posList.at(
				(mDynamicObjects.at( i ).currPosID + 1) % mDynamicObjects.at( i ).posNum
				);

		float stepX, stepY, stepZ;	// �ƶ�����
		stepX = mDynamicObjects.at( i ).moveStep[0];
		stepY = mDynamicObjects.at( i ).moveStep[1];
		stepZ = mDynamicObjects.at( i ).moveStep[2];
		//stepX = abs( currPoint[0] - nextPoint[0] ) / 200.0f;
		//stepY = abs( currPoint[1] - nextPoint[1] ) / 200.0f;
		//stepZ = abs( currPoint[2] - nextPoint[2] ) / 200.0f;

		float dx, dy, dz;	// btScalarΪBullet�µĸ�����
		dx = pos.getOrigin()[0] - nextPoint[0];
		dy = pos.getOrigin()[1] - nextPoint[1];
		dz = pos.getOrigin()[2] - nextPoint[2];

		Ogre::Vector3 currPos = OgreBulletCollisions::BtOgreConverter::to( pos.getOrigin() );
		// �ƶ���i������
		if( ! ( abs( dx ) < 0.05f && abs( dy ) < 0.05f && abs( dz ) < 0.05f ) )
		{
			if( abs( dx ) > 0.05f )
				dx > 0 ? targetPos = currPos - Ogre::Vector3(stepX,0,0) : targetPos = currPos + Ogre::Vector3(stepX,0,0);
			else if( abs( dy ) > 0.05f )
				dy > 0 ? targetPos = currPos - Ogre::Vector3(0,stepY,0) : targetPos = currPos + Ogre::Vector3(0,stepY,0);
			else if( abs( dz ) > 0.05f )
				dz > 0 ? targetPos = currPos - Ogre::Vector3(0,0,stepZ) : targetPos = currPos + Ogre::Vector3(0,0,stepZ);

			pos.setOrigin( OgreBulletCollisions::OgreBtConverter::to( targetPos ) );
			mDynamicObjects.at( i ).rigidBody->getBulletRigidBody()->setWorldTransform( pos );		  // ����������
			mDynamicObjects.at( i ).graphicBody->setPosition( targetPos[0], targetPos[1], targetPos[2] ); // ����ͼ����
		}
		// �ѵ�����һ���㣬���µ�ǰ����ʹ��������һ�����ƶ�
		// % ������ѭ������
		else
		{
			mDynamicObjects.at( i ).currPosID = ++mDynamicObjects.at( i ).currPosID % mDynamicObjects.at( i ).posNum;
			//targetPos = pos.getOrigin();
		}

	}
}
// --------------------------------------------------------------------------------
