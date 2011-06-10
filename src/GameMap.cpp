#include "GameMap.h"

// ------------------------------------------------------------------------
GameMap::GameMap(void) :
	mTerrainGlobals(0),
    mTerrainGroup(0),
    mTerrainsImported(false),
    mInfoLabel(0)
{
}
// ------------------------------------------------------------------------
GameMap::GameMap( Ogre::SceneManager * pSceneMgr, Ogre::Light * pLight ) :
	mSceneMgr( pSceneMgr ),
	mTerrainGlobals(0),
    mTerrainGroup(0),
    mTerrainsImported(false),
    mInfoLabel(0)
{
	initMap( pSceneMgr, pLight ); // 初始化地图
}
// ------------------------------------------------------------------------
GameMap::~GameMap(void)
{
}
// ------------------------------------------------------------------------
void GameMap::cleanMap(void)
{
    OGRE_DELETE mTerrainGroup;
    OGRE_DELETE mTerrainGlobals;
}
// ------------------------------------------------------------------------
// 初始化地图，main
void GameMap::initMap( Ogre::SceneManager * pSceneMgr, Ogre::Light * pLight )
{
	// .Scene File Loader
	std::auto_ptr<Ogre::DotSceneLoader> sceneLoader( new Ogre::DotSceneLoader() );
	sceneLoader->parseDotScene( "seek_map.scene", "General", mSceneMgr );
/*
	// Play with startup Texture Filtering options
	// Note: Pressing T on runtime will discarde those settings
	//Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	//Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

	// create a new set of global Terrain options
    mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	// construct TerrainGroup object
    mTerrainGroup = OGRE_NEW Ogre::TerrainGroup( pSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f );
    mTerrainGroup->setFilenameConvention( Ogre::String("GameMapTerrain"), Ogre::String("dat") );
    //mTerrainGroup->setOrigin( Ogre::Vector3::ZERO );
    mTerrainGroup->setOrigin( Ogre::Vector3(0.0,-265.0,0.0) );

	// configure Terrain
    configureTerrainDefaults( pSceneMgr, pLight );

	// 指示 TerrainGroup 加载 Terrain
	// 当前由于只有一个地形，只需要加载一次 >>> 4-8-0831
    for( long x = 0; x <= 0; ++x )
        for( long y = 0; y <= 0; ++y )
            defineTerrain( x, y );

    // sync load since we want everything in place when we start
    mTerrainGroup->loadAllTerrains(true);

	// 如果已经加载Terrain，计算 Blendmaps
    if( mTerrainsImported )
    {
        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
        while( ti.hasMoreElements() )
        {
            Ogre::Terrain * t = ti.getNext()->instance;
            initBlendMaps( t );
        }
    }

	// clean up after the initial terrain creation
    mTerrainGroup->freeTemporaryResources();
*/

	//std::auto_ptr sceneLoader( new DotSceneLoader() );	
	//sceneLoader->parseDotScene( , LEVEL_GROUP_NAME, mSceneMgr );

/*	// 平面地图 | 方便测试用	
	// create a floor mesh resource
	Ogre::MeshManager::getSingleton().createPlane(
			"terrain", // 平面模型名称
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::Plane(Ogre::Vector3::UNIT_Y, 0),
			100, 100, // 平面宽度和高度
			10, 10, // x,y方向分割数目
			true,   // 是否创建垂直于平面的法线
			1,      // 纹理坐标集的数目 | 即多层纹理的层数
			10, 10, // u,v方向纹理铺嵌行数
			Ogre::Vector3::UNIT_Z
			);
	// create a floor entity, give it a material, and place it at the origin
	mTerrain = pSceneMgr->createEntity("Terrain", "terrain");
    mTerrain->setMaterialName("Examples/Rockwall");
	mTerrain->setCastShadows(false);
	Ogre::SceneNode * terrainNode = pSceneMgr->getRootSceneNode()->createChildSceneNode();
	terrainNode->setPosition( Ogre::Vector3(0.0,0.0,0.0) );
	terrainNode->attachObject( mTerrain );
	terrainNode->roll( Ogre::Degree(5) ); // 倾斜一定角度
    //pSceneMgr->getRootSceneNode()->attachObject( mTerrain );
*/
}
// ------------------------------------------------------------------------
// Configure Terrain
void GameMap::configureTerrainDefaults( Ogre::SceneManager * pSceneMgr, Ogre::Light * pLight )
{
    // Configure global
    mTerrainGlobals->setMaxPixelError(8);
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000);

    // Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection( pLight->getDerivedDirection() );
    mTerrainGlobals->setCompositeMapAmbient( pSceneMgr->getAmbientLight() );
    mTerrainGlobals->setCompositeMapDiffuse( pLight->getDiffuseColour() );

    // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData & defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
    // textures
    defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 100;
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}
// ------------------------------------------------------------------------
// 从资源库加载图片，并适当旋转图片
void getTerrainImage( bool flipX, bool flipY, Ogre::Image & img )
{
    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX)
        img.flipAroundY();
    if (flipY)
        img.flipAroundX();

}
// ------------------------------------------------------------------------
// 查看在资源列表中是否存在Terrain文件
// 如果存在，表明已经生成 Binary Terrain Data，无需再从图片导入
void GameMap::defineTerrain( long x, long y )
{
    Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage( x % 2 != 0, y % 2 != 0, img ); // 加载图片，>>> terrain.png
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }
}
// ------------------------------------------------------------------------
void GameMap::initBlendMaps( Ogre::Terrain * terrain )
{
    Ogre::TerrainLayerBlendMap * blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap * blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
    float * pBlend1 = blendMap1->getBlendPointer();
    for( Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y )
    {
        for( Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x )
        {
            Ogre::Real tx, ty;

            blendMap0->convertImageToTerrainSpace( x, y, &tx, &ty );
            Ogre::Real height = terrain->getHeightAtTerrainPosition( tx, ty );
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp( val, (Ogre::Real)0, (Ogre::Real)1 );

            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp( val, (Ogre::Real)0, (Ogre::Real)1 );
            * pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}
// ------------------------------------------------------------------------
//void GameMap::createFrameListener(void)
void GameMap::createFrameListener( OgreBites::SdkTrayManager * pTrayMgr )
{
    //BaseApplication::createFrameListener();
	mInfoLabel = pTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 350);
}
// ------------------------------------------------------------------------
void GameMap::frameRenderingQueued( OgreBites::SdkTrayManager * pTrayMgr )
{
    if( mTerrainGroup->isDerivedDataUpdateInProgress() )
    {
        pTrayMgr->moveWidgetToTray( mInfoLabel, OgreBites::TL_TOP, 0 );
        mInfoLabel->show();
        if( mTerrainsImported )
        {
            mInfoLabel->setCaption("Building terrain, please wait...");
        }
        else
        {
            mInfoLabel->setCaption("Updating textures, patience...");
        }
    }
    else
    {
        pTrayMgr->removeWidgetFromTray( mInfoLabel );
        mInfoLabel->hide();
        if( mTerrainsImported )
        {
            mTerrainGroup->saveAllTerrains(true);
            mTerrainsImported = false;
        }
    }
}
// ------------------------------------------------------------------------
