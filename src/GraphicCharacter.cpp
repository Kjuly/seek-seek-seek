#include "GraphicCharacter.h"

// ------------------------------------------------------------------------
GraphicCharacter::GraphicCharacter( SceneManager * pSceneMgr, CharacterState * pCharacterState )
{
	mCharacterState = pCharacterState;
	setupBody( pSceneMgr );
	setupAnimations();
}
// ------------------------------------------------------------------------
void GraphicCharacter::addTime( Real deltaTime )
{
	updateBody( deltaTime );
	updateAnimations( deltaTime );
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
	
	if( ! mCharacterState->zeroKeyDirection() && mBaseAnimID == ANIM_NONE )
	{
		// start running if not already moving and the player wants to move
	//	setBaseAnimation( ANIM_RUN_BASE, true );
		setBaseAnimation(ANIM_RUN, true);	// Run
		//if( mTopAnimID == ANIM_IDLE_TOP ) setTopAnimation( ANIM_RUN_TOP, true );
	}
}
// ------------------------------------------------------------------------
void GraphicCharacter::injectKeyUp( const OIS::KeyEvent & evt )
{
	if( evt.key == OIS::KC_LSHIFT ) mRun = true;
	
	if( mCharacterState->zeroKeyDirection() && mBaseAnimID == ANIM_RUN )
	{
		// stop running if already moving and the player doesn't want to move
		setBaseAnimation( ANIM_NONE );
	}
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
	Ogre::Entity * characterEnt = pSceneMgr->createEntity("Character_1", "Sintel_tiny.mesh");
	//tmpEnt->setMaterialName("Sintel_tiny");
	characterNode->attachObject( characterEnt );
	characterNode->setPosition( Ogre::Vector3(-30.0f,3.0f,-3.0f) );
	characterNode->yaw(Ogre::Degree(180));
*/
	//--------------------------------
	// create main model
	mBodyNode = pSceneMgr->getRootSceneNode()->createChildSceneNode( Vector3::UNIT_Y * CHAR_HEIGHT );
	mBodyEnt = pSceneMgr->createEntity("Sintel_tiny_Body", "Sintel_tiny.mesh");
	//mBodyEnt = pSceneMgr->createEntity("Sintel_tiny_Body", "maxpayen.mesh");
	mBodyNode->attachObject( mBodyEnt );
	mBodyNode->yaw(Ogre::Degree(180));

	mVerticalVelocity = 0;
	mRun = true;
}

// ------------------------------------------------------------------------
void GraphicCharacter::setupAnimations()
{
	// this is very important due to the nature of the exported animations
	// 从角色skeleton文件中获取各动画状态信息
	mBodyEnt->getSkeleton()->setBlendMode( ANIMBLEND_CUMULATIVE );

	String animNames[] = { "Run", "Jump" };

	// populate(填充) our animation list
	// 将动画状态信息储存于对应AnimationState类数组mAnims[]中
	for( int i = 0; i < NUM_ANIMS; ++i )
	{
		mAnims[i] = mBodyEnt->getAnimationState( animNames[i] );
		mAnims[i]->setLoop(true);
		mFadingIn[i] = false;
		mFadingOut[i] = false;
	}

	// start off in the idle state (top and bottom together)
	// 角色默认动画状态
	//setBaseAnimation( ANIM_NONE );
	setBaseAnimation( ANIM_RUN );

	// relax the hands since we're not holding anything
	// 角色双手闲置
//	mAnims[ ANIM_HANDS_RELAXED ]->setEnabled(true);
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
		Real yawToGoal = toGoal.getYaw().valueDegrees();
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

		mBodyNode->translate(0, 0, deltaTime * RUN_SPEED * mAnims[mBaseAnimID]->getWeight(), Node::TS_LOCAL);
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
void GraphicCharacter::updateAnimations( Real deltaTime )
{
	Real baseAnimSpeed = 1;
//	Real topAnimSpeed = 1;

	mTimer += deltaTime;

	// increment the current base and top animation times
	if( mBaseAnimID != ANIM_NONE ) mAnims[mBaseAnimID]->addTime( deltaTime * baseAnimSpeed );

	// apply smooth transitioning between our animations
	fadeAnimations( deltaTime );
}
// ------------------------------------------------------------------------
void GraphicCharacter::fadeAnimations( Real deltaTime )
{
	for( int i = 0; i < NUM_ANIMS; i++ )
	{
		if( mFadingIn[i] )
		{
			// slowly fade this animation in until it has full weight
			Real newWeight = mAnims[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
			mAnims[i]->setWeight( Math::Clamp<Real>(newWeight, 0, 1) );
			if( newWeight >= 1 ) mFadingIn[i] = false;
		}
		else if( mFadingOut[i] )
		{
			// slowly fade this animation out until it has no weight, and then disable it
			Real newWeight = mAnims[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
			mAnims[i]->setWeight( Math::Clamp<Real>(newWeight, 0, 1) );
			if( newWeight <= 0 )
			{
				mAnims[i]->setEnabled(false);
				mFadingOut[i] = false;
			}
		}
	}
}
// ------------------------------------------------------------------------
void GraphicCharacter::setBaseAnimation( AnimID id, bool reset /*= false*/ )
{
	// 更新角色旧状态为新状态
	if( mBaseAnimID >= 0 && mBaseAnimID < NUM_ANIMS )
	{
		// if we have an old animation, fade it out
		mFadingIn[mBaseAnimID] = false;
		mFadingOut[mBaseAnimID] = true;
	}

	mBaseAnimID = id;

	if( id != ANIM_NONE )
	{
		// if we have a new animation, enable it and fade it in
		mAnims[id]->setEnabled(true);
		mAnims[id]->setWeight(0);
		mFadingOut[id] = false;
		mFadingIn[id] = true;
		if( reset ) mAnims[id]->setTimePosition(0);
	}
}
// ------------------------------------------------------------------------
void GraphicCharacter::setTopAnimation( AnimID id, bool reset /*= false*/ )
{
	// 将角色旧状态更新为新状态
/*	if( mTopAnimID >= 0 && mTopAnimID < NUM_ANIMS )
	{
		// if we have an old animation, fade it out
		mFadingIn[mTopAnimID] = false;
		mFadingOut[mTopAnimID] = true;
	}

	mTopAnimID = id;

	if( id != ANIM_NONE )
	{
		// if we have a new animation, enable it and fade it in
		mAnims[id]->setEnabled(true);
		mAnims[id]->setWeight(0);
		mFadingOut[id] = false;
		mFadingIn[id] = true;
		if( reset ) mAnims[id]->setTimePosition(0);
	}
*/
}
// ------------------------------------------------------------------------
