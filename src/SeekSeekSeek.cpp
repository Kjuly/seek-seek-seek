#include "SeekSeekSeek.h"

//-------------------------------------------------------------------------------------
SeekSeekSeek::SeekSeekSeek(void)
{
	mDebugMode = false;	// Ĭ�Ϲرյ���ģʽ
}
//-------------------------------------------------------------------------------------
SeekSeekSeek::~SeekSeekSeek(void)
{
}
//-------------------------------------------------------------------------------------
void SeekSeekSeek::destroyScene(void)
{
	// �Ƴ���ɫ
	if( mCharacter ) delete mCharacter; 

	// �Ƴ���ͼ
	if( mMap )
	{
		mMap->cleanMap();
		delete mMap;
	}

	if( mPhysicsFrameListener ) delete mPhysicsFrameListener;
}
//-------------------------------------------------------------------------------------
void SeekSeekSeek::createScene(void)
{
	// ��ɫ״̬��
	mCharacterState = new CharacterState( mCameraNode );

	// ��ͼ
	mMap = new GameMap( mSceneMgr, mLight );

	// ���������¼�����
	mPhysicsFrameListener = new PhysicsFrameListener(
			mSceneMgr,
			mMap,		// ��Ϸ��ͼ
			Ogre::Vector3(0, -9.81, 0), // gravity vector for Bullet
            Ogre::AxisAlignedBox( Ogre::Vector3 (-10000, -10000, -10000), //aligned box for Bullet
				Ogre::Vector3 (10000,  10000,  10000) ) 
			);

	// ������ɫ
	mCharacter = new Character(
			mSceneMgr,									// �������ƾ��
			mPhysicsFrameListener->getPhysicsWorld(),	// Dynamics | Collision Wrold
			mCharacterState								// ��ɫ״̬��
			);

	// Ϊ��ɫ�����������
	mCharacterInputListener = new CharacterInputListener(
			mCharacter->getKinematicCharacter(),
			mCharacterState
			);

	// ������������ | Light, Sky, etc
	createEnvir();

	// ��ʼ����������, ��Ч
	initSound();

	// ��Ϊ����ģʽ�������������
	if( mDebugMode ) mPhysicsFrameListener->getPhysicsWorld()->setShowDebugShapes(true);

	// GUI
	mGUIMgr = new GameGUI();
}
//-------------------------------------------------------------------------------------
void SeekSeekSeek::createEnvir(void)
{
	// Light
    Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();

    mLight = mSceneMgr->createLight("mainLight");
    mLight->setType( Ogre::Light::LT_DIRECTIONAL );
    mLight->setDirection( lightdir );
    mLight->setDiffuseColour( Ogre::ColourValue::White );
    mLight->setSpecularColour( Ogre::ColourValue(0.4, 0.4, 0.4) );

	// ������
    mSceneMgr->setAmbientLight( Ogre::ColourValue(0.2, 0.2, 0.2) );

	// Fog
	Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    mSceneMgr->setFog( Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 210 );
    mWindow->getViewport(0)->setBackgroundColour( fadeColour );
	mBgFog = 1; // ���죬����

	// Sky
    //Ogre::Plane plane;
    //plane.d = 100;
    //plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 500);
	// Planeģʽ��Fog�ļ����Ժ�
    //mSceneMgr->setSkyPlane(true, plane, "Examples/CloudySky", 500, 20, true, 0.5, 150, 150);
}
//-------------------------------------------------------------------------------------
// ��ʼ����������, ��Ч
void SeekSeekSeek::initSound(void)
{
	mSoundMgr = new OgreAL::SoundManager();
	mBgMusicID = 0;
	Ogre::String soundName;
	for( int i = 1; i <= 3; ++i )
	{
		soundName = "bgMusic_" + StringConverter::toString( i );
		// createSound(), ����3��4: loop, stream
		OgreAL::Sound * bgSound = mSoundMgr->createSound( soundName, soundName + ".ogg", true, true);
		bgSound->setGain(0.5);
		bgSound->setRelativeToListener(true);
		//bgSound->play();
	}
	OgreAL::SoundManager::getSingleton().getSound("bgMusic_1")->play();
	mBgMusicID = 1;
}
//-------------------------------------------------------------------------------------
void SeekSeekSeek::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

	// Camera Position �� GraphicCharacter ���и��ݽ�ɫλ�ö���
    // Position it at 500 in Z direction
    //mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    //mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);

    if( mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE) )
		mCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
	
	// create a default camera controller
    mCameraMan = new OgreBites::SdkCameraMan( mCamera ); 
	mCameraMan->setStyle( OgreBites::CS_MANUAL ); // �ֶ�����ģʽ

	// --------------
	// create a pivot at roughly the character's shoulder
	mCameraPivot = mCamera->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	// this is where the camera should be soon, and it spins around the pivot
	// mCameraGoal �� mCameraPivot �ӽڵ���
	mCameraGoal = mCameraPivot->createChildSceneNode( Ogre::Vector3(0, 0, 25) );
	// this is where the camera actually is
	mCameraNode = mCamera->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition( mCameraPivot->getPosition() + mCameraGoal->getPosition() );

	mCameraPivot->setFixedYawAxis(true);
	mCameraGoal->setFixedYawAxis(true);
	mCameraNode->setFixedYawAxis(true);

	// �����ݹ����� mCamera ������ mCameraNode �ڵ���
	mCameraNode->attachObject( mCamera );

	mPivotPitch			= 0;		// ���������ۼӶ���
	mViewTurningLeft	= false;	// ����LEFT�����ƣ��Ƿ���������ת״̬
	mViewTurningRight	= false;	// ����
	mViewTurningUp		= false;	// ����
	mViewTurningDown	= false;	// ����
	mViewZoomingIn		= false;	// ����
	mViewZoomingOut		= false;	// Զ��
}
//-------------------------------------------------------------------------------------
void SeekSeekSeek::createViewports(void)
{
	mViewport = mWindow->addViewport( mCamera );
	//mViewport->setBackgroundColour( ColourValue(1.0f,1.0f,1.0f) );
	mViewport->setBackgroundColour( ColourValue(0.0f,0.0f,0.0f) );

	// ���� Camera ����Ӧ Viewport ��Ұ��Χ
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio( Ogre::Real(mViewport->getActualWidth()) /
			Ogre::Real(mViewport->getActualHeight()) );
}
//-------------------------------------------------------------------------------------
void SeekSeekSeek::createFrameListener(void)
{
    GameBase::createFrameListener();
	
	//mMap->createFrameListener( mTrayMgr );
	
	// Ϊ�������紴������ | ��createScene�д���
	mRoot->addFrameListener( mPhysicsFrameListener );
	// END

}
//-------------------------------------------------------------------------------------
bool SeekSeekSeek::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = GameBase::frameRenderingQueued( evt );

	// ͨ��GUI�˳���Ϸ
	if( mGUIMgr->gameShutDown() ) return false;

	// ��������ģ��
	mPhysicsFrameListener->getPhysicsWorld()->stepSimulation( evt.timeSinceLastFrame );
	// ���½�ɫ����״̬
	mCharacter->update( evt.timeSinceLastFrame );

	// ���������
	updateCamera( evt.timeSinceLastFrame );

    return ret;
}
// ---------------------------------------------------------------------
bool SeekSeekSeek::keyPressed( const OIS::KeyEvent & evt )
{
	// GUI
	if( evt.key == OIS::KC_DELETE ) mShutDown = true;
	if( evt.key == OIS::KC_ESCAPE )
	{
		mGUIMgr->toggleGUIVisibility(); // �л�GUI��ʾ
		//mGUIWasVisible = ! mGUIWasVisible;
	}

	// ������Ϸ
	if( ! mGUIMgr->GUIisVisible() )
	{

	GameBase::keyPressed( evt ); // ������ļ��̲���
	// �Խ�ɫ��Ϊ���������
	mCharacterInputListener->keyDown( evt );
	// ����Ogre��ɫ
	mCharacter->getGraphicCharacter()->injectKeyDown( evt );
	//if ( ! mTrayMgr->isDialogVisible() ) mCharacter->getGraphicCharacter()->injectKeyDown( evt );

	// ���̴����������ӽ�
	if( evt.key == OIS::KC_LEFT )		mViewTurningLeft	= true;
	else if( evt.key == OIS::KC_RIGHT ) mViewTurningRight	= true;
	else if( evt.key == OIS::KC_UP )	mViewTurningUp		= true;
	else if( evt.key == OIS::KC_DOWN )	mViewTurningDown	= true;
	else if( evt.key == OIS::KC_PGUP )	mViewZoomingIn		= true;
	else if( evt.key == OIS::KC_PGDOWN) mViewZoomingOut		= true;

	switch( evt.key )
	{
	case OIS::KC_DELETE:
		mShutDown = true;
		break;
	case OIS::KC_B:
		mPhysicsFrameListener->createBox( mSceneMgr, mCamera ); // Ͷ�����������
		break;
	// ��������
	case OIS::KC_F1:
		if( mBgMusicID == 1 )
		{
			OgreAL::SoundManager::getSingleton().getSound("bgMusic_1")->stop();
			mBgMusicID = 0;
		}
		else
		{	
			if( mBgMusicID == 2 )
				OgreAL::SoundManager::getSingleton().getSound("bgMusic_2")->stop();
			else if( mBgMusicID == 3 )
				OgreAL::SoundManager::getSingleton().getSound("bgMusic_3")->stop();
			OgreAL::SoundManager::getSingleton().getSound("bgMusic_1")->play();
			mBgMusicID = 1;
		}
		break;
	case OIS::KC_F2:
		if( mBgMusicID == 2 )
		{
			OgreAL::SoundManager::getSingleton().getSound("bgMusic_2")->stop();
			mBgMusicID = 0;
		}
		else
		{	
			if( mBgMusicID == 1 )
				OgreAL::SoundManager::getSingleton().getSound("bgMusic_1")->stop();
			else if( mBgMusicID == 3 )
				OgreAL::SoundManager::getSingleton().getSound("bgMusic_3")->stop();
			OgreAL::SoundManager::getSingleton().getSound("bgMusic_2")->play();
			mBgMusicID = 2;
		}
		break;
	case OIS::KC_F3:
		if( mBgMusicID == 3 )
		{
			OgreAL::SoundManager::getSingleton().getSound("bgMusic_3")->stop();
			mBgMusicID = 0;
		}
		else
		{	
			if( mBgMusicID == 1 )
				OgreAL::SoundManager::getSingleton().getSound("bgMusic_1")->stop();
			else if( mBgMusicID == 2 )
				OgreAL::SoundManager::getSingleton().getSound("bgMusic_2")->stop();
			OgreAL::SoundManager::getSingleton().getSound("bgMusic_3")->play();
			mBgMusicID = 3;
		}
		break;
	// Fog
	case OIS::KC_TAB:
		if( mBgFog == 0 )
		{
			Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
			mSceneMgr->setFog( Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 210 );
			mWindow->getViewport(0)->setBackgroundColour( fadeColour );
			mBgFog = 1;
		}
		else if( mBgFog == 1 )
		{
			Ogre::ColourValue fadeColour(0.6, 0.6, 1.0);
			mSceneMgr->setFog( Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 210 );
			mWindow->getViewport(0)->setBackgroundColour( fadeColour );
			mBgFog = 2;
		}
		else if( mBgFog == 2 )
		{
			mSceneMgr->setFog( Ogre::FOG_NONE );
			mBgFog = 0;
		}
		break;
	// ����ģʽ�л�
	case OIS::KC_F12:
		if( mDebugMode )
		{
			mPhysicsFrameListener->getPhysicsWorld()->setShowDebugShapes(false);
			mDebugMode = false;
		}
		else
		{
			mPhysicsFrameListener->getPhysicsWorld()->setShowDebugShapes(true);
			mDebugMode = true;
		}
		break;
	default:
		break;
	}

	} // end if( ! mGUIWasVisible )
	// ����ʾ�û�����״̬�¶�GUIע�����������Ϊ
	else
	{
		mGUIMgr->injectKeyPressed( evt );
	}

	return true;
}
// ---------------------------------------------------------------------
bool SeekSeekSeek::keyReleased( const OIS::KeyEvent & evt )
{
	if( ! mGUIMgr->GUIisVisible() )
	{
		GameBase::keyReleased( evt ); // ������ļ��̲���
		// �Խ�ɫ��Ϊ���������
		mCharacterInputListener->keyUp( evt );
		// ����Ogre��ɫ
		mCharacter->getGraphicCharacter()->injectKeyUp( evt );
		//if ( ! mTrayMgr->isDialogVisible() ) mCharacter->getGraphicCharacter()->injectKeyUp( evt );

		// ���̴����������ӽ�
		if( evt.key == OIS::KC_LEFT )		mViewTurningLeft	= false;
		else if( evt.key == OIS::KC_RIGHT ) mViewTurningRight	= false;
		else if( evt.key == OIS::KC_UP )	mViewTurningUp		= false;
		else if( evt.key == OIS::KC_DOWN )	mViewTurningDown	= false;
		else if( evt.key == OIS::KC_PGUP )	mViewZoomingIn		= false;
		else if( evt.key == OIS::KC_PGDOWN) mViewZoomingOut		= false;
	} // end if( ! mGUIWasVisible )
	// GUI
	else
	{
		mGUIMgr->injectKeyReleased( evt );
	}

	return true;
}
// ---------------------------------------------------------------------
bool SeekSeekSeek::mouseMoved( const OIS::MouseEvent & evt )
{
	if( ! mGUIMgr->GUIisVisible() )
	{
		// ���� Camera �ӽ�
		updateCameraGoal( -0.05f * evt.state.X.rel, -0.05f * evt.state.Y.rel, -0.0005f * evt.state.Z.rel );
	} // end if( ! mGUIWasVisible )
	// GUI
	else
	{
		mGUIMgr->injectMouseMoved( evt );
	}
	
    return true;
}
// ---------------------------------------------------------------------
void SeekSeekSeek::updateCamera( Real deltaTime )
{
	if( mViewTurningLeft )		updateCameraGoal( -1, 0, 0 );
	else if( mViewTurningRight )updateCameraGoal(  1, 0, 0 );
	if( mViewTurningUp )		updateCameraGoal( 0, -0.5, 0 );
	else if( mViewTurningDown )	updateCameraGoal( 0,  0.5, 0 );
	if( mViewZoomingIn )		updateCameraGoal(  0,  0, -0.01 ); // ����̫�󣬷����޷�if�������
	else if( mViewZoomingOut )	mCameraGoal->translate( 0, 0, 1, Node::TS_LOCAL ); // ��ʱδ�趨������

	// place the camera pivot roughly at the character's shoulder
	mCameraPivot->setPosition( mCharacter->getGraphicCharacter()->getBodyNode()->getPosition() + Ogre::Vector3::UNIT_Y * CAM_HEIGHT );
	// move the camera smoothly to the goal
	Ogre::Vector3 goalOffset = mCameraGoal->_getDerivedPosition() - mCameraNode->getPosition();
	mCameraNode->translate( goalOffset * deltaTime * 9.0f );
	// always look at the pivot
	mCameraNode->lookAt( mCameraPivot->_getDerivedPosition(), Node::TS_WORLD );
}
// ---------------------------------------------------------------------
void SeekSeekSeek::updateCameraGoal( Real deltaYaw, Real deltaPitch, Real deltaZoom )
{
	// ������ת�ӽ�
	mCameraPivot->yaw( Degree( deltaYaw ), Node::TS_WORLD );

	// bound the pitch
	// ������ת�ӽ�
	if( ! (mPivotPitch + deltaPitch > 25 && deltaPitch > 0) &&
		! (mPivotPitch + deltaPitch < -60 && deltaPitch < 0) )
	{
		mCameraPivot->pitch(Degree(deltaPitch), Node::TS_LOCAL);
		mPivotPitch += deltaPitch;
	}
		
	// bound the zoom
	// �����ӽ�
	Real dist = mCameraGoal->_getDerivedPosition().distance( mCameraPivot->_getDerivedPosition() );
	Real distChange = deltaZoom * dist;
	// ��8~25֮���ƶ� Camera�������Ž�ɫ
	if( ! (dist + distChange < 8 && distChange < 0) &&
		! (dist + distChange > 25 && distChange > 0) )
	{
		mCameraGoal->translate( 0, 0, distChange, Node::TS_LOCAL );
	}
}
// ---------------------------------------------------------------------
bool SeekSeekSeek::mousePressed( const OIS::MouseEvent & evt, OIS::MouseButtonID id )
{
	//mCharacter->getGraphicCharacter()->injectMouseDown( evt, id );
	//if ( ! mTrayMgr->isDialogVisible() ) mCharacter->getGraphicCharacter()->injectMouseDown( evt, id );
	
	// GUI
	if( mGUIMgr->GUIisVisible() ) mGUIMgr->injectMousePressed( id );

    return true;
}
// ---------------------------------------------------------------------
bool SeekSeekSeek::mouseReleased( const OIS::MouseEvent & evt, OIS::MouseButtonID id )
{
    //if (mTrayMgr->injectMouseUp(evt, id)) return true;
    //mCameraMan->injectMouseUp(evt, id);
	
	// GUI
	if( mGUIMgr->GUIisVisible() ) mGUIMgr->injectMouseReleased( id );

    return true;
}
// ---------------------------------------------------------------------
