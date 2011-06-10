/*
 *	   FILENAME: SeekSeekSeek.h
 * ------------------------------------------------------------------------
 *	DESCRIPTION:	游戏主类，继承于GameBase，将创建的游戏角色、游戏地
 *				图等对象添加到游戏中进行渲染，并对各对象和键盘、鼠标进
 *				行实时的监听和更新。
 * ------------------------------------------------------------------------
 */

#ifndef __SeekSeekSeek_h_
#define __SeekSeekSeek_h_

#include "GameBase.h"				// 基础设置
#include "GameMap.h"				// 游戏地图
#include "PhysicsFrameListener.h"	// 物理事件
#include "Character.h"				// 角色
#include "CharacterInputListener.h" // 角色动作输入监听
#include "CharacterState.h"			// 运动状态存储集:可移动、可跳跃
#include "OgreALListener.h"			// OgreAL | Ogre Audio Lib | 加载音乐类库 >>> 5-8-2109
#include "OgreALSoundManager.h"		// OgreAL

#include "CEGUI.h"									// CEGUI
#include "RendererModules/Ogre/CEGUIOgreRenderer.h"

using namespace Ogre;

class SeekSeekSeek : public GameBase
{
public:
    SeekSeekSeek(void);
    virtual ~SeekSeekSeek(void);

protected:
    virtual void createScene(void);		// Scene Main
    virtual void createEnvir(void);     // Environment: Light, Sky, etc.
    virtual void createCamera(void);    // Camera
    virtual void createViewports(void); // Viewport
    virtual void createFrameListener(void);
    virtual void destroyScene(void);
	void initSound(void);				// 初始化背景音乐, 音效

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener | OIS::MouseListener
    virtual bool keyPressed( const OIS::KeyEvent & evt );
    virtual bool keyReleased( const OIS::KeyEvent & evt );
    virtual bool mouseMoved( const OIS::MouseEvent & evt );
    virtual bool mousePressed( const OIS::MouseEvent & evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent & evt, OIS::MouseButtonID id );
	bool quit( const CEGUI::EventArgs & evt );

	void updateCamera( Real deltaTime );									 // 更新 Camera
	void updateCameraGoal( Real deltaYaw, Real deltaPitch, Real deltaZoom ); // 更新 Camera 目标方向 | 更新视角

	// 摄像机
	SceneNode * mCameraPivot;	// 离角色一定距离(肩膀附近)的地方 | 用户位置
	SceneNode * mCameraGoal;	// 相机目标
	SceneNode * mCameraNode;	// 实际 Camera 节点
	Real mPivotPitch;		// 上下限制累加度数
	bool mViewTurningLeft;	// 向左旋转视角
	bool mViewTurningRight;	// 向右
	bool mViewTurningUp;	// 向上旋转视角
	bool mViewTurningDown;	// 向下
	bool mViewZoomingIn;	// 缩近角色视角
	bool mViewZoomingOut;	// 远离角色视角

	GameMap					* mMap;						// 游戏地图
	Character				* mCharacter;				// 角色对象
	PhysicsFrameListener	* mPhysicsFrameListener;	// 物理事件监听
	CharacterInputListener	* mCharacterInputListener;	// 角色动作输入监听
	CharacterState			* mCharacterState;			// 运动状态集

	OgreAL::SoundManager	* mSoundMgr;				// 声音
	Ogre::Real				  mBgMusicID;				// 当前播放的背景音乐
	Ogre::Real				  mBgFog;					// 背景雾: 0 无，1 白天 白雾，2 夜晚 蓝雾

	bool mDebugMode;									// 调试模式切换

	CEGUI::OgreRenderer		* mRenderer;				// CEGUI 渲染
};

#endif // #ifndef __SeekSeekSeek_h_
