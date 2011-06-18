#include "Character.h"

// ------------------------------------------------------------------------
Character::Character( SceneManager * pSceneMgr, OgreBulletDynamics::DynamicsWorld * pWorld, CharacterState * pCharacterState ) :
	mSceneMgr( pSceneMgr ),
	mWorld( pWorld ),
	mCharacterState( pCharacterState )
{
	createGraphicCharacter();
	createKinematicCharacter();
}
// ------------------------------------------------------------------------
Character::~Character()
{
}
// ------------------------------------------------------------------------
void Character::createGraphicCharacter()
{
	mGraphicCharacter = new GraphicCharacter( mSceneMgr, mCharacterState );
}
// ------------------------------------------------------------------------
void Character::createKinematicCharacter()
{
	Ogre::SceneNode * playerNode = mGraphicCharacter->getBodyNode();
	Ogre::Entity * playerEntity = mGraphicCharacter->getBodyEnt();

	// ��ʼ��λ
	playerNode->setPosition( Ogre::Vector3(0.0,5.0,0.0) ); 
	// ����
	playerNode->setOrientation( Quaternion( Degree( Ogre::Math::RangeRandom(0.0,0.0) ), Vector3::UNIT_Y ) ); 

	//Vector3 size = playerNode->_getDerivedScale() * playerEntity->getBoundingBox().getHalfSize();
	//OgreBulletCollisions::CollisionShape * mPlayerPhysicsShape = new OgreBulletCollisions::CapsuleCollisionShape( Ogre::Real(2.5), Ogre::Real(1.9), Vector3::UNIT_Y );
	OgreBulletCollisions::CollisionShape * mPlayerPhysicsShape = new OgreBulletCollisions::SphereCollisionShape( Ogre::Real(3) );

	//--------------------------------------------
	// Character BoundingBox Test
/*	OgreBulletDynamics::RigidBody * mSceneBody = new OgreBulletDynamics::RigidBody( "Player", mWorld );
	mSceneBody->setStaticShape(
			playerNode,
			mPlayerPhysicsShape,
			0.6f,
			0.6f,
			playerNode->_getDerivedPosition(),
			playerNode->_getDerivedOrientation()
			//Ogre::Quaternion( Ogre::Degree(90), Ogre::Vector3::UNIT_Z )
			);
	// Character BoundingBox Test END
	//--------------------------------------------
*/
	// --------------------------------------
	// Kinematic Character
	// a special btCollisionObject, useful for fast localized collision queries
	// Kinematic ������ btGhostShape ��ʵ����¥�ݵ�һЩ��ײ����
	// btKinematicCharacterController ... uses a btGhostShape to perform collision queries
	//to create a character that can climb stairs, slide smoothly along walls etc.
	// btPairCachingGhostObject->btGhostObject->btCollisionObject
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin( OgreBulletCollisions::OgreBtConverter::to(playerNode->_getDerivedPosition()) ); // ԭʼ��

	///------------
	// a special btCollisionObject, useful for fast localized collision queries
	// Kinematic ������ btGhostShape ��ʵ����¥�ݵ�һЩ��ײ����
	// btKinematicCharacterController ... uses a btGhostShape to perform collision queries
	//to create a character that can climb stairs, slide smoothly along walls etc.
	// btPairCachingGhostObject->btGhostObject->btCollisionObject
	// BulletCollision/CollisionDispatch/btGhostObject/99
	btPairCachingGhostObject * m_ghostObject = new btPairCachingGhostObject();
	m_ghostObject->setWorldTransform( startTransform );
	mWorld->getBulletDynamicsWorld()->getPairCache()->setInternalGhostPairCallback( new btGhostPairCallback() );

	///------------
	// Set shape for GHostObject
	m_ghostObject->setCollisionShape( mPlayerPhysicsShape->getBulletShape() );
	m_ghostObject->setCollisionFlags( btCollisionObject::CF_CHARACTER_OBJECT );

	///------------
	btScalar stepHeight = btScalar(0.6);

	// ------------
	// Set Controller
	///BulletDynamics/Character/btKin...
	mKinematicCharacter = new KinematicCharacter(
			mGraphicCharacter->getBodyNode(),
			m_ghostObject,
			static_cast<btCapsuleShape*>(mPlayerPhysicsShape->getBulletShape()),
			stepHeight
			);
	
	// ------------
	// Add Object
	mWorld->getBulletDynamicsWorld()->addCollisionObject( m_ghostObject );
	mWorld->getBulletDynamicsWorld()->addAction( mKinematicCharacter );
	mWorld->getBulletDynamicsWorld()->addCharacter( mKinematicCharacter ); // >>> 4-26-1933
	// --------------------------------------
	
	// �� Kinematic ��ɫ����һЩ����
	mKinematicCharacter->setMaxJumpHeight( 30 );	// ��Ծ����߸߶�
	mKinematicCharacter->setJumpSpeed( 20 );		// �����ٶ�
	mKinematicCharacter->setFallSpeed( 10 );		// �����ٶ�
}
// ------------------------------------------------------------------------
void Character::update( Ogre::Real deltaTime )
{
	// ͨ�� KeyDirection �ϳ� GoalDirection, ������ setWalkDirection()
	mKinematicCharacter->setCharacterVelocityForTimeInterval(
			OgreBulletCollisions::OgreBtConverter::to( mCharacterState->getGoalDirection() ), // �ٶ�
			deltaTime * 40
			);

	// ������Ծ
	if( mCharacterState->getJumpState() ) mKinematicCharacter->doCharacterJump();
	
	// �������
	if( mKinematicCharacter->isLanded() ) mCharacterState->setLandedState(true);
	else mCharacterState->setLandedState(false);

	//mKinematicCharacter->updateAction( mWorld, deltaTime );

	// ��ȡ�˶�ѧ��ɫ��ǰλ�ò���, ��ͬ��ͼ��ѧ��ɫ�ƶ�
	mKinematicCharacter->setWorldTransform( mKinematicCharacter->getWorldTransform() );

	// ����ͼ��ѧ��ɫ�Ķ���״̬ | Ogre Animation
	mGraphicCharacter->addTime( deltaTime );
}
// ------------------------------------------------------------------------
