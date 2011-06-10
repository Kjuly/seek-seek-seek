#include "KinematicCharacter.h"

// ------------------------------------------------------------------------
KinematicCharacter::KinematicCharacter(
		SceneNode * pNode,
		btPairCachingGhostObject * ghostObject, btConvexShape * convexShape, btScalar stepHeight, int upAxis /*= 1*/
		) :
	btKinematicCharacterController( ghostObject, convexShape, stepHeight, upAxis ),
	mNode( pNode )
{
	mGoalDirection = Ogre::Vector3::ZERO; // Ĭ��״̬�£���ɫĿ�귽��Ϊ0�����ƶ�
}
// ------------------------------------------------------------------------
KinematicCharacter::~KinematicCharacter()
{
}
// ------------------------------------------------------------------------
// ���ý�ɫǰ������
void KinematicCharacter::setCharacterWalkDirection( const Ogre::Vector3 & pGoalDirection )
{
	btKinematicCharacterController::setWalkDirection( OgreBulletCollisions::OgreBtConverter::to(pGoalDirection) );
}
// ------------------------------------------------------------------------
// ���ý�ɫǰ������, ����ÿ֡�ٶ�
void KinematicCharacter::setCharacterVelocityForTimeInterval( const btVector3 & pVelocity, btScalar pTimeInterval )
{
	btKinematicCharacterController::setVelocityForTimeInterval( pVelocity, pTimeInterval );
}
// ------------------------------------------------------------------------
// ��ɫ��Ծ��Ϊ
void KinematicCharacter::doCharacterJump()
{
	btKinematicCharacterController::jump();
}
// ------------------------------------------------------------------------
// ��ɫ�Ƿ����䣬�ڵ���
bool KinematicCharacter::isLanded()
{
	return btKinematicCharacterController::onGround();
}
// ------------------------------------------------------------------------
btTransform KinematicCharacter::getWorldTransform() const
{
	btTransform tmp;
	tmp.setIdentity();
	tmp.setOrigin( m_currentPosition );
	return tmp;
}
// ------------------------------------------------------------------------
void KinematicCharacter::getWorldTransform( btTransform & pWorldTrans ) const
{
	//pWorldTrans = mPosition;
	btTransform tmp;
	tmp.setIdentity();
	tmp.setOrigin( m_currentPosition );
	pWorldTrans = tmp;
}
// ------------------------------------------------------------------------
void KinematicCharacter::setWorldTransform( const btTransform & pWorldTrans )
{
	if( mNode == NULL ) return;

	// Ŀǰ������û��������ת������ͼ������Ҫ�ٶ�������ת����ܽ��ת������
	//btQuaternion rot = pWorldTrans.getRotation();
	//mNode->setOrientation( rot.w(), rot.x(), rot.y(), rot.z() );

	btVector3 pos = pWorldTrans.getOrigin();
	mNode->setPosition( pos.x(), pos.y(), pos.z() );
}
// ------------------------------------------------------------------------
