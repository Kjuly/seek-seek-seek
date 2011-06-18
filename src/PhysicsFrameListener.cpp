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

	// 删除场景中的自动对象
	while( ! mDynamicObjects.empty() )
	{
		mDynamicObjects.pop_back();
	}
	mDynamicObjects.clear();
}
// --------------------------------------------------------------------------------
// 构建地面物理体
void PhysicsFrameListener::createPhysicsTerrain()
{
	createTerrain02();
}
// ------------------------------------------------------------------------
void PhysicsFrameListener::createTerrain01()
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
void PhysicsFrameListener::createTerrain02()
{
	Ogre::SceneNode										* sceneNode;	// 存储场景节点
	Ogre::String										nodeName;		// 记录节点名
	OgreBulletCollisions::StaticMeshToShapeConverter	* Converter;	// 将 mesh 转换为 shape
	OgreBulletCollisions::CollisionShape				* mSceneShape;	// Collision Shape
	OgreBulletDynamics::RigidBody						* mSceneBody;	// Rigid Body
	int i;

	for( i = 1; i <= 66; ++i )
	{
		nodeName = "static_" + StringConverter::toString(i);
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

	// 自动对象 移动平台
	// 自动对象运动目标点队列
/*	for( i = 1; i <= 2; ++i )
	{
		nodeName = "moveplat_" + StringConverter::toString(i);
		sceneNode = mSceneMgr->getSceneNode( nodeName );

		Vector3 size = sceneNode->_getDerivedScale() * mSceneMgr->getEntity( nodeName )->getBoundingBox().getHalfSize();
		//node->setPosition( position );
		mSceneShape = new OgreBulletCollisions::BoxCollisionShape( size );
	//	Converter = new OgreBulletCollisions::StaticMeshToShapeConverter( mSceneMgr->getEntity( nodeName ) );
	//	mSceneShape = ( OgreBulletCollisions::CollisionShape * )Converter->createTrimesh(); // 三角形网格

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
	// 自动对象运动目标点队列
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

	// 自动对象 障碍物
	// 自动对象运动目标点队列
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
			createSceneObject( entity, pos, false );
	}
*/

	// 创建目标
 	SceneNode * goalNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	Entity * goalEntity = mSceneMgr->createEntity( "Scales", "Scales.mesh" );
 	goalNode->attachObject( goalEntity );
	goalNode->setPosition( Ogre::Vector3(108.0f,125.0f,-82.346f) );
 	goalNode->scale(1.0f, 1.0f, 1.0f);	// the cube is too big for us
	goalNode->yaw( Ogre::Degree(-180) );
	//createSceneObject( entity, Ogre::Vector3(10.0,5.0,0.0), false );

	// 创建盒子
/* 	SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	Entity * entity = mSceneMgr->createEntity( "Box" + StringConverter::toString( mNumEntitiesInstanced ), "cube.mesh" );
 	entity->setMaterialName( "Examples/BumpyMetal" );
 	node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 	node->attachObject( entity );
 	node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us

	// 自动对象运动目标点队列
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
// 场景对象分静态和动态物体: 静态:不可移动 动态:可移动
// 同时又分自动和非自动: 自动:自己在移动的障碍物等对象
void PhysicsFrameListener::createSceneObject( Ogre::Entity * entity, Ogre::Vector3 origPos,
		Ogre::Vector3 pPosList[], int pPosNum, // 运动目标点队列
		bool bStatic /*= false*/, bool autoMove /*= false*/
		)
{
	// 最原始的静态BOX
	Ogre::SceneNode * node = entity->getParentSceneNode();
	Ogre::Vector3 size = node->_getDerivedScale() * entity->getBoundingBox().getHalfSize();
    float mass =  bStatic ? 0.0f : 1.0f;
	srand( (unsigned)time( NULL ) );

	//node->setPosition( origPos );
	node->setOrientation( Quaternion( Degree( Ogre::Math::RangeRandom(0.0,60.0) ), Ogre::Vector3::UNIT_Y ) );

	OgreBulletCollisions::BoxCollisionShape * sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape( size );

	// 若非场景中自动对象
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
	// 将自动对象推入自动对象队列
	else
	{
		DynamicObject dynamicObject; // 创建自动对象

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
// 更新非玩家控制对象
void PhysicsFrameListener::updateNPCObject()
{
	updateDynamicObject();	// 自由移动对象
}
// --------------------------------------------------------------------------------
// 更新自动对象运动
void PhysicsFrameListener::updateDynamicObject()
{
	btTransform pos;
	Ogre::Vector3 targetPos;

	for( int i = 0; i < mDynamicObjects.size(); ++i )
	{
		pos = mDynamicObjects.at( i ).rigidBody->getBulletRigidBody()->getWorldTransform();

		// 获取第i个对象当前点的三维坐标
		//Ogre::Vector3 currPoint = mDynamicObjects.at( i ).posList.at( mDynamicObjects.at( i ).currPosID );
		// 获取第i个对象移动时下一个点的三维坐标
		Ogre::Vector3 nextPoint = mDynamicObjects.at( i ).posList.at(
				(mDynamicObjects.at( i ).currPosID + 1) % mDynamicObjects.at( i ).posNum
				);

		float stepX, stepY, stepZ;	// 移动步长
		stepX = mDynamicObjects.at( i ).moveStep[0];
		stepY = mDynamicObjects.at( i ).moveStep[1];
		stepZ = mDynamicObjects.at( i ).moveStep[2];
		//stepX = abs( currPoint[0] - nextPoint[0] ) / 200.0f;
		//stepY = abs( currPoint[1] - nextPoint[1] ) / 200.0f;
		//stepZ = abs( currPoint[2] - nextPoint[2] ) / 200.0f;

		float dx, dy, dz;	// btScalar为Bullet下的浮点型
		dx = pos.getOrigin()[0] - nextPoint[0];
		dy = pos.getOrigin()[1] - nextPoint[1];
		dz = pos.getOrigin()[2] - nextPoint[2];

		Ogre::Vector3 currPos = OgreBulletCollisions::BtOgreConverter::to( pos.getOrigin() );
		// 移动第i个对象
		if( ! ( abs( dx ) < 0.05f && abs( dy ) < 0.05f && abs( dz ) < 0.05f ) )
		{
			if( abs( dx ) > 0.05f )
				dx > 0 ? targetPos = currPos - Ogre::Vector3(stepX,0,0) : targetPos = currPos + Ogre::Vector3(stepX,0,0);
			else if( abs( dy ) > 0.05f )
				dy > 0 ? targetPos = currPos - Ogre::Vector3(0,stepY,0) : targetPos = currPos + Ogre::Vector3(0,stepY,0);
			else if( abs( dz ) > 0.05f )
				dz > 0 ? targetPos = currPos - Ogre::Vector3(0,0,stepZ) : targetPos = currPos + Ogre::Vector3(0,0,stepZ);

			pos.setOrigin( OgreBulletCollisions::OgreBtConverter::to( targetPos ) );
			mDynamicObjects.at( i ).rigidBody->getBulletRigidBody()->setWorldTransform( pos );		  // 更新物理体
			mDynamicObjects.at( i ).graphicBody->setPosition( targetPos[0], targetPos[1], targetPos[2] ); // 更新图形体
		}
		// 已到达下一个点，更新当前点以使对象向下一个点移动
		// % 运算解决循环问题
		else
		{
			mDynamicObjects.at( i ).currPosID = ++mDynamicObjects.at( i ).currPosID % mDynamicObjects.at( i ).posNum;
			//targetPos = pos.getOrigin();
		}

	}
}
// --------------------------------------------------------------------------------
