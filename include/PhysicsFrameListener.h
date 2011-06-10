/*
 *	   FILENAME: PhysicsFrameListener.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	物理世界的建立，继承于PhysicsBase，将游戏中的图形学
 *				对象转化为含有物理碰撞检测、重力的运动学物体。
 * ------------------------------------------------------------------------
 */

#ifndef __PhysicsFrameListener_h_
#define __PhysicsFrameListener_h_

#include "PhysicsBase.h" // 物理世界基本设置

class PhysicsFrameListener : public PhysicsBase
{
public:
    PhysicsFrameListener(
			Ogre::SceneManager * sceneMgr,	// 场景控制
			GameMap * pTerrain,				// 游戏地图
			Ogre::Vector3 gravityVector,	// 重力
			Ogre::AxisAlignedBox bounds		// 世界包围大小
			);
 	~PhysicsFrameListener();
	virtual void destroyPhysicsWorld();		// 释放内存

	void createBoxShape( Ogre::Entity * entity, Ogre::Vector3 position, bool bStatic = false ); // 创建盒子
 	void createBox( Ogre::SceneManager * pSceneMgr, Ogre::Camera * mCamera );					// 投掷盒子
	virtual void createPhysicsTerrain();	// 构建地形
	virtual void createPhysicsScene();		// 在地形基础上构建场景
};

#endif
