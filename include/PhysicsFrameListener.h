/*
 *	   FILENAME: PhysicsFrameListener.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	��������Ľ������̳���PhysicsBase������Ϸ�е�ͼ��ѧ
 *				����ת��Ϊ����������ײ��⡢�������˶�ѧ���塣
 * ------------------------------------------------------------------------
 */

#ifndef __PhysicsFrameListener_h_
#define __PhysicsFrameListener_h_

#include "PhysicsBase.h" // ���������������

// LIB Bullet
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace OgreBulletDynamics;
using namespace OgreBulletCollisions;

struct DynamicObject
{
	OgreBulletDynamics::RigidBody	* rigidBody;	// ������
	Ogre::SceneNode					* graphicBody;	// ͼ����
	int								  posNum;		// �˶�Ŀ������
	int								  currPosID;	// ��ǰ�˶����Ľڵ�ID
	std::vector< btVector3 >		  posList;		// �˶�Ŀ������ 0Ϊ��ʼ��
};

class PhysicsFrameListener : public PhysicsBase
{
public:
    PhysicsFrameListener(
			Ogre::SceneManager * sceneMgr,	// ��������
			GameMap * pTerrain,				// ��Ϸ��ͼ
			Ogre::Vector3 gravityVector,	// ����
			Ogre::AxisAlignedBox bounds		// �����Χ��С
			);
 	~PhysicsFrameListener();
	virtual void destroyPhysicsWorld();		// �ͷ��ڴ�

 	void createBox( Ogre::SceneManager * pSceneMgr, Ogre::Camera * mCamera );					// Ͷ������
	virtual void createPhysicsTerrain();	// ��������
	virtual void createPhysicsScene();		// �ڵ��λ����Ϲ�������

	void updateDynamicObject();

protected:
	// ������������ | true: ��̬  false: ��̬
	void createSceneObject( Ogre::Entity * entity, Ogre::Vector3 origPos,
			btVector3 pPosList[], int pPosNum, // �˶�Ŀ������
			bool bStatic = false, bool autoMove = false
			);

private:
	std::vector< DynamicObject >	mDynamicObjects;
};

#endif
