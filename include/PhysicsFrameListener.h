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

// LIB Bullet
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace Ogre;
using namespace OgreBulletDynamics;
using namespace OgreBulletCollisions;

// 非玩家控制对象
struct DynamicObject
{
	OgreBulletDynamics::RigidBody	* rigidBody;	// 物理体
	Ogre::SceneNode					* graphicBody;	// 图形体
	int								  posNum;		// 运动目标点个数
	int								  currPosID;	// 当前运动到的节点ID
	std::vector< Ogre::Vector3 >	  posList;		// 运动目标点队列 0为初始点
	Ogre::Vector3					  moveStep;		// 运动步长
};

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

 	void createBox( Ogre::SceneManager * pSceneMgr, Ogre::Camera * mCamera );					// 投掷盒子
	virtual void createPhysicsTerrain();	// 构建地形
	virtual void createPhysicsScene();		// 在地形基础上构建场景

	// 更新非玩家控制对象
	void updateNPCObject();
	void updateDynamicObject();

protected:
	void createTerrain01();
	void createTerrain02();
	// 创建场景对象 | true: 静态  false: 动态
	void createSceneObject( Ogre::Entity * entity, Ogre::Vector3 origPos,
			Ogre::Vector3 pPosList[], int pPosNum, // 运动目标点队列
			bool bStatic = false, bool autoMove = false
			);

private:
	std::vector< DynamicObject >	mDynamicObjects;
};

#endif
