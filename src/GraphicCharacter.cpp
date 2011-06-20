#include "GraphicCharacter.h"

// ------------------------------------------------------------------------
GraphicCharacter::GraphicCharacter( SceneManager * pSceneMgr, CharacterState * pCharacterState ) :
	mSceneMgr( pSceneMgr )
{
	mCharacterState = pCharacterState;
	setupBody();
}
// ------------------------------------------------------------------------
void GraphicCharacter::addTime( Real deltaTime )
{
	updateBody( deltaTime );
	//mYellowLightAnimState->addTime( deltaTime );
}
// ------------------------------------------------------------------------
void GraphicCharacter::injectKeyDown( const OIS::KeyEvent & evt )
{
	// ��Ծ
	//else if( evt.key == OIS::KC_SPACE && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP) )
	//else if( mCharacterState->getJumpState() && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP) )
/*	if( mCharacterState->getJumpState() && (mTopAnimID == ANIM_IDLE_TOP || mTopAnimID == ANIM_RUN_TOP) )
	{
		// jump if on ground
		setBaseAnimation( ANIM_JUMP_START, true );
		setTopAnimation( ANIM_NONE );
		mTimer = 0;
	}
*/
	// mCharacterState->getKeyDirection()���㼴��ɫ���ƶ������������ƶ���
	// mBaseAnimID = ANIM_IDLE_BASE ��ʾ��ɫĿǰ������ IDLE ״̬
//	if( ! mCharacterState->zeroKeyDirection() && mBaseAnimID == ANIM_IDLE_BASE )
	if( evt.key == OIS::KC_LSHIFT ) mRun = false;
}
// ------------------------------------------------------------------------
void GraphicCharacter::injectKeyUp( const OIS::KeyEvent & evt )
{
	if( evt.key == OIS::KC_LSHIFT ) mRun = true;
}
// ------------------------------------------------------------------------
void GraphicCharacter::injectMouseDown( const OIS::MouseEvent & evt, OIS::MouseButtonID id )
{
}
// ------------------------------------------------------------------------
void GraphicCharacter::setupBody()
{
	//--------------------------------
	// tmp
/*	Ogre::SceneNode * characterNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity * characterEnt = mSceneMgr->createEntity("colorBall_blue", "colorBall_blue.mesh");
	//tmpEnt->setMaterialName("Sintel_tiny");
	characterNode->attachObject( characterEnt );
	characterNode->setPosition( Ogre::Vector3(-10.0f,3.0f,-3.0f) );
	characterNode->setScale( 3.0, 3.0, 3.0 );
	characterNode->pitch(Ogre::Degree(90));
	//characterNode->yaw(Ogre::Degree(180));
	
	Ogre::SceneNode * tmpNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity * tmpEnt = mSceneMgr->createEntity("colorBall_tmp", "Mesh.004.mesh");
	//tmpEnt->setMaterialName("Sintel_tiny");
	tmpNode->attachObject( tmpEnt );
	tmpNode->setPosition( Ogre::Vector3(-10.0f,3.0f,-3.0f) );
	tmpNode->setScale( 3.0, 3.0, 3.0 );
	tmpNode->pitch(Ogre::Degree(90));
*/
	//--------------------------------
	// create main model
	mBodyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( Vector3::UNIT_Y * CHAR_HEIGHT );
	mBodyEnt = mSceneMgr->createEntity("colorBall_blue", "colorBall_blue.mesh");
	//mBodyEnt = mSceneMgr->createEntity("colorBall_blue", "yinYangBall.mesh");
	mBodyNode->attachObject( mBodyEnt );
	mBodyNode->setScale( 3.0, 3.0, 3.0 );
	mBodyNode->yaw(Ogre::Degree(90));
	//mBodyNode->roll(Ogre::Degree(90));
	//mBodyNode->roll

	// attach a light with the same colour to the light node
	Ogre::Light * light = mSceneMgr->createLight();
	light->setDiffuseColour( Ogre::ColourValue(0,0.742,1) );
	light->setPowerScale(100);
	light->setShadowFarDistance(1000);
	mBodyNode->attachObject( light );

/*	//--------------------------------
	// create main model
	mBodyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( Vector3::UNIT_Y * CHAR_HEIGHT );
	mBodyEnt = mSceneMgr->createEntity("Sintel_tiny_Body", "Sintel_tiny.mesh");
	mBodyNode->attachObject( mBodyEnt );
	mBodyNode->yaw(Ogre::Degree(180));
*/

	mVerticalVelocity = 0;
	mRun = true;
}
// ------------------------------------------------------------------------
// �� ת�� �� ��Ծ ��������Ҫ���� Body
void GraphicCharacter::updateBody( Real deltaTime )
{
	// ���½�ɫ���� | �ƶ����� KinematicCharacter.cpp ��ʵ��
	if( ! mCharacterState->zeroKeyDirection() )
	{
		Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo( mCharacterState->getGoalDirection() );

		// calculate how much the character has to turn to face goal direction
		Real yawToGoal = toGoal.getYaw().valueDegrees() + 90; // 90:yaw
		// this is how much the character CAN turn this frame
		Real yawAtSpeed = yawToGoal / Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;
		// reduce "turnability" if we're in midair(�����)
		// ��ɫ���ڰ����ʱ, ��Сת���ٶ�
//		if( mBaseAnimID == ANIM_JUMP_LOOP ) yawAtSpeed *= 0.2f;

		// turn as much as we can, but not more than we need to
		if( yawToGoal < 0 )
			yawToGoal = std::min<Real>( 0, std::max<Real>(yawToGoal, yawAtSpeed) );
		else if( yawToGoal > 0 )
			yawToGoal = std::max<Real>( 0, std::min<Real>(yawToGoal, yawAtSpeed) );
		
		// ��ת��ɫ����Ŀ�귽��	
		mBodyNode->yaw( Degree( yawToGoal ) );

		mBodyNode->translate(0, 0, deltaTime * RUN_SPEED * 10, Node::TS_LOCAL);
	}

	///------------------------------------------------
	///��ɫ��Ծ״̬
/*	if( mBaseAnimID == ANIM_JUMP_LOOP )
	{
		if( mCharacterState->getLandedState() )
		{
			setBaseAnimation( ANIM_JUMP_END, true );
			mTimer = 0;
		}
	}
*/
}
// ------------------------------------------------------------------------
