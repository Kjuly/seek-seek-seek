#include "GraphicCharacter.h"

// ------------------------------------------------------------------------
GraphicCharacter::GraphicCharacter( SceneManager * pSceneMgr, CharacterState * pCharacterState )
{
	mCharacterState = pCharacterState;
	setupBody( pSceneMgr );
}
// ------------------------------------------------------------------------
void GraphicCharacter::addTime( Real deltaTime )
{
	updateBody( deltaTime );
}
// ------------------------------------------------------------------------
void GraphicCharacter::injectKeyDown( const OIS::KeyEvent & evt )
{
	// 跳跃
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
	// mCharacterState->getKeyDirection()非零即角色将移动，或者正在移动；
	// mBaseAnimID = ANIM_IDLE_BASE 表示角色目前正处于 IDLE 状态
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
void GraphicCharacter::setupBody( SceneManager * pSceneMgr )
{
	//--------------------------------
	// tmp
/*	Ogre::SceneNode * characterNode = pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity * characterEnt = pSceneMgr->createEntity("colorBall_blue", "colorBall_blue.mesh");
	//tmpEnt->setMaterialName("Sintel_tiny");
	characterNode->attachObject( characterEnt );
	characterNode->setPosition( Ogre::Vector3(-10.0f,3.0f,-3.0f) );
	characterNode->setScale( 3.0, 3.0, 3.0 );
	characterNode->pitch(Ogre::Degree(90));
	//characterNode->yaw(Ogre::Degree(180));
	
	Ogre::SceneNode * tmpNode = pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity * tmpEnt = pSceneMgr->createEntity("colorBall_tmp", "Mesh.004.mesh");
	//tmpEnt->setMaterialName("Sintel_tiny");
	tmpNode->attachObject( tmpEnt );
	tmpNode->setPosition( Ogre::Vector3(-10.0f,3.0f,-3.0f) );
	tmpNode->setScale( 3.0, 3.0, 3.0 );
	tmpNode->pitch(Ogre::Degree(90));
*/
	//--------------------------------
	// create main model
	mBodyNode = pSceneMgr->getRootSceneNode()->createChildSceneNode( Vector3::UNIT_Y * CHAR_HEIGHT );
	mBodyEnt = pSceneMgr->createEntity("colorBall_blue", "colorBall_blue.mesh");
	//mBodyEnt = pSceneMgr->createEntity("colorBall_blue", "yinYangBall.mesh");
	mBodyNode->attachObject( mBodyEnt );
	mBodyNode->setScale( 3.0, 3.0, 3.0 );
	mBodyNode->yaw(Ogre::Degree(90));
	//mBodyNode->roll(Ogre::Degree(90));
	//mBodyNode->roll
/*	//--------------------------------
	// create main model
	mBodyNode = pSceneMgr->getRootSceneNode()->createChildSceneNode( Vector3::UNIT_Y * CHAR_HEIGHT );
	mBodyEnt = pSceneMgr->createEntity("Sintel_tiny_Body", "Sintel_tiny.mesh");
	mBodyNode->attachObject( mBodyEnt );
	mBodyNode->yaw(Ogre::Degree(180));
*/

	mVerticalVelocity = 0;
	mRun = true;
}
// ------------------------------------------------------------------------
// 在 转身 和 跳跃 情形下需要更新 Body
void GraphicCharacter::updateBody( Real deltaTime )
{
	// 更新角色方向 | 移动已于 KinematicCharacter.cpp 中实现
	if( ! mCharacterState->zeroKeyDirection() )
	{
		Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo( mCharacterState->getGoalDirection() );

		// calculate how much the character has to turn to face goal direction
		Real yawToGoal = toGoal.getYaw().valueDegrees() + 90; // 90:yaw
		// this is how much the character CAN turn this frame
		Real yawAtSpeed = yawToGoal / Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;
		// reduce "turnability" if we're in midair(半空中)
		// 角色处于半空中时, 减小转身速度
//		if( mBaseAnimID == ANIM_JUMP_LOOP ) yawAtSpeed *= 0.2f;

		// turn as much as we can, but not more than we need to
		if( yawToGoal < 0 )
			yawToGoal = std::min<Real>( 0, std::max<Real>(yawToGoal, yawAtSpeed) );
		else if( yawToGoal > 0 )
			yawToGoal = std::max<Real>( 0, std::min<Real>(yawToGoal, yawAtSpeed) );
		
		// 旋转角色朝向目标方向	
		mBodyNode->yaw( Degree( yawToGoal ) );

		mBodyNode->translate(0, 0, deltaTime * RUN_SPEED * 10, Node::TS_LOCAL);
	}

	///------------------------------------------------
	///角色跳跃状态
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
