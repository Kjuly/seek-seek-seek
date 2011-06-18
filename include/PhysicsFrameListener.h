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
using namespace Ogre;
using namespace OgreBulletDynamics;
using namespace OgreBulletCollisions;

// ����ҿ��ƶ���
struct DynamicObject
{
	OgreBulletDynamics::RigidBody	* rigidBody;	// ������
	Ogre::SceneNode					* graphicBody;	// ͼ����
	int								  posNum;		// �˶�Ŀ������
	int								  currPosID;	// ��ǰ�˶����Ľڵ�ID
	std::vector< Ogre::Vector3 >	  posList;		// �˶�Ŀ������ 0Ϊ��ʼ��
	Ogre::Vector3					  moveStep;		// �˶�����
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

	// ���·���ҿ��ƶ���
	void updateNPCObject();
	void updateDynamicObject();

protected:
	void createTerrain01();
	void createTerrain02();
	// ������������ | true: ��̬  false: ��̬
	void createSceneObject( Ogre::Entity * entity, Ogre::Vector3 origPos,
			Ogre::Vector3 pPosList[], int pPosNum, // �˶�Ŀ������
			bool bStatic = false, bool autoMove = false
			);

private:
	std::vector< DynamicObject >	mDynamicObjects;
};

#endif
