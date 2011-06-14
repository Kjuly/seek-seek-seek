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
	// �ӽ�ɫskeleton�ļ��л�ȡ������״̬��Ϣ
	mBodyEnt->getSkeleton()->setBlendMode( ANIMBLEND_CUMULATIVE );

	String animNames[] = { "Run", "Jump" };

	// populate(���) our animation list
	// ������״̬��Ϣ�����ڶ�ӦAnimationState������mAnims[]��
	for( int i = 0; i < NUM_ANIMS; ++i )
	{
		mAnims[i] = mBodyEnt->getAnimationState( animNames[i] );
		mAnims[i]->setLoop(true);
		mFadingIn[i] = false;
		mFadingOut[i] = false;
	}

	// start off in the idle state (top and bottom together)
	// ��ɫĬ�϶���״̬
	//setBaseAnimation( ANIM_NONE );
	setBaseAnimation( ANIM_RUN );

	// relax the hands since we're not holding anything
	// ��ɫ˫������
//	mAnims[ ANIM_HANDS_RELAXED ]->setEnabled(true);
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
		Real yawToGoal = toGoal.getYaw().valueDegrees();
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

		mBodyNode->translate(0, 0, deltaTime * RUN_SPEED * mAnims[mBaseAnimID]->getWeight(), Node::TS_LOCAL);
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
	// ���½�ɫ��״̬Ϊ��״̬
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
	// ����ɫ��״̬����Ϊ��״̬
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
