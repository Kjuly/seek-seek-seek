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

	void createBoxShape( Ogre::Entity * entity, Ogre::Vector3 position, bool bStatic = false ); // ��������
 	void createBox( Ogre::SceneManager * pSceneMgr, Ogre::Camera * mCamera );					// Ͷ������
	virtual void createPhysicsTerrain();	// ��������
	virtual void createPhysicsScene();		// �ڵ��λ����Ϲ�������
};

#endif
