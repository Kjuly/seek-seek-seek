/*
 * 动力学角色和图形学角色共享 W A S D
 */

#include "CharacterInputListener.h"

// ------------------------------------------------------------------------
CharacterInputListener::CharacterInputListener( KinematicCharacter * pKinematicCharacter, CharacterState * pCharacterState ) :
	mKinematicCharacter( pKinematicCharacter ),
	mCharacterState( pCharacterState )
{
}
// ------------------------------------------------------------------------
CharacterInputListener::~CharacterInputListener()
{
}
// ------------------------------------------------------------------------
void CharacterInputListener::keyDown( const KeyEvent & evt )
{
	if	   ( evt.key == OIS::KC_W )		mCharacterState->setKeyDirectionZ(-1);
	else if( evt.key == OIS::KC_A )		mCharacterState->setKeyDirectionX(-1);
	else if( evt.key == OIS::KC_S )		mCharacterState->setKeyDirectionZ(1);
	else if( evt.key == OIS::KC_D )		mCharacterState->setKeyDirectionX(1);
	else if( evt.key == OIS::KC_SPACE ) mCharacterState->setJumpState(true);
}
// ------------------------------------------------------------------------
void CharacterInputListener::keyUp( const KeyEvent & evt )
{
	if( evt.key == OIS::KC_W && mCharacterState->getKeyDirectionZ() == -1 )
		mCharacterState->setKeyDirectionZ(0);
	else if( evt.key == OIS::KC_A && mCharacterState->getKeyDirectionX() == -1 )
		mCharacterState->setKeyDirectionX(0);
	else if( evt.key == OIS::KC_S && mCharacterState->getKeyDirectionZ() == 1 )
		mCharacterState->setKeyDirectionZ(0);
	else if( evt.key == OIS::KC_D && mCharacterState->getKeyDirectionX() == 1 )
		mCharacterState->setKeyDirectionX(0);
	else if( evt.key == OIS::KC_SPACE && mCharacterState->getJumpState() == true )
		mCharacterState->setJumpState(false);
}
// ------------------------------------------------------------------------
