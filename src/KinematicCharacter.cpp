#include "KinematicCharacter.h"

// ------------------------------------------------------------------------
KinematicCharacter::KinematicCharacter(
		SceneNode * pNode,
		btPairCachingGhostObject * ghostObject, btConvexShape * convexShape, btScalar stepHeight, int upAxis /*= 1*/
		) :
	btKinematicCharacterController( ghostObject, convexShape, stepHeight, upAxis ),
	mNode( pNode )
{
	mGoalDirection = Ogre::Vector3::ZERO; // 默认状态下，角色目标方向为0，不移动
}
// ------------------------------------------------------------------------
KinematicCharacter::~KinematicCharacter()
{
}
// ------------------------------------------------------------------------
// 设置角色前进方向
void KinematicCharacter::setCharacterWalkDirection( const Ogre::Vector3 & pGoalDirection )
{
	btKinematicCharacterController::setWalkDirection( OgreBulletCollisions::OgreBtConverter::to(pGoalDirection) );
}
// ------------------------------------------------------------------------
// 设置角色前进方向, 控制每帧速度
void KinematicCharacter::setCharacterVelocityForTimeInterval( const btVector3 & pVelocity, btScalar pTimeInterval )
{
	btKinematicCharacterController::setVelocityForTimeInterval( pVelocity, pTimeInterval );
}
// ------------------------------------------------------------------------
// 角色跳跃行为
void KinematicCharacter::doCharacterJump()
{
	btKinematicCharacterController::jump();
}
// ------------------------------------------------------------------------
// 角色是否着落，在地上
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

	// 目前物理体没有设置旋转，所以图形体需要再独自设置转向才能解决转身问题
	//btQuaternion rot = pWorldTrans.getRotation();
	//mNode->setOrientation( rot.w(), rot.x(), rot.y(), rot.z() );

	btVector3 pos = pWorldTrans.getOrigin();
	mNode->setPosition( pos.x(), pos.y(), pos.z() );
}
// ------------------------------------------------------------------------
