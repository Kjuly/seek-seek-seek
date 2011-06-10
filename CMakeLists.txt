cmake_minimum_required(VERSION 2.6)
project(seek)
 
if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/Common/include
	)
	# OgreBullet >>> 5-6-1823
	set(OGREBULLET_INCLUDE_DIR
		E:/ogrebullet
	)
	set(OGREBULLET_INCLUDE_DIRS
		"${OGREBULLET_INCLUDE_DIR}/Collisions/include"
		"${OGREBULLET_INCLUDE_DIR}/Dynamics/include"
	)
	# Bullet
	set(BULLET_INCLUDE_DIR
		E:/Bullet/BULLET_PHYSICS/include/bullet
	)
	set(BULLET_INCLUDE_DIRS
		${BULLET_INCLUDE_DIR}
		"${BULLET_INCLUDE_DIR}/BulletCollision"
		"${BULLET_INCLUDE_DIR}/BulletDynamics"
		"${BULLET_INCLUDE_DIR}/BulletSoftBody"
		"${BULLET_INCLUDE_DIR}/BulletMultiThreaded"
		"${BULLET_INCLUDE_DIR}/ConvexDecomposition"
		"${BULLET_INCLUDE_DIR}/GIMPACTUtils"
		"${BULLET_INCLUDE_DIR}/LinearMath"
		"${BULLET_INCLUDE_DIR}/MiniCL"
		"E:/Bullet/BULLET_PHYSICS/include/OpenGL"
	)
	# OgreBullet >>> 4-11-0027 end.
	# OpenAL >>> 5-8-2056
	set(OPENAL_INCLUDE_DIR
		E:/openal/OpenALSDK/include
	)

	# OgreAL >>> 5-8-2056
	set(OGREAL_INCLUDE_DIR
		E:/openal/OgreAL-Eihort/include
	)
endif(WIN32)
 
if(UNIX)
	set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		/home/kjuly/ogre/Samples/Common/include/
	)
	# OgreBullet >>> 4-11-0027
	set(OGREBULLET_INCLUDE_DIR
		/usr/local/include/OgreBullet/
	)
	set(OGREBULLET_INCLUDE_DIRS
		#/usr/local/include/OgreBullet/
		"${OGREBULLET_INCLUDE_DIR}/Collisions"
		"${OGREBULLET_INCLUDE_DIR}/Dynamics"
	)
	# Bullet
	set(BULLET_INCLUDE_DIR
		/usr/local/include/bullet/
	)
	set(BULLET_INCLUDE_DIRS
		${BULLET_INCLUDE_DIR}
		"${BULLET_INCLUDE_DIR}/BulletCollision"
		"${BULLET_INCLUDE_DIR}/BulletDynamics"
		"${BULLET_INCLUDE_DIR}/BulletSoftBody"
		"${BULLET_INCLUDE_DIR}/BulletMultiThreaded"
		"${BULLET_INCLUDE_DIR}/ConvexDecomposition"
		"${BULLET_INCLUDE_DIR}/GIMPACTUtils"
		"${BULLET_INCLUDE_DIR}/LinearMath"
		"${BULLET_INCLUDE_DIR}/MiniCL"
		"/home/kjuly/bullet/src" # >>> 4-23-1228
	)
	# OgreBullet >>> 4-11-0027 end.

	# OpenGl
	set(OPENGL_INCLUDE_DIR
		/usr/local/include/OpenGL/
	)
	set(OPENGL_INCLUDE_DIRS
		${OPENGL_INCLUDE_DIR}
		"${OPENGL_INCLUDE_DIR}/ibmsdk"
		"/home/kjuly/bullet/Demos/OpenGL" # >>> 4-23-1228-opengl
	)

	# OpenAL >>> 5-8-2056
	set(OPENAL_INCLUDE_DIR
		/usr/local/include/AL/
	)

	# OgreAL >>> 5-8-2056
	set(OGREAL_INCLUDE_DIR
		/usr/local/include/OgreAL/
	)
endif(UNIX)
 
if (CMAKE_BUILD_TYPE STREQUAL "")
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	# differentiation between debug and release builds.
	set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")

if(WIN32)
 	set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR} )
endif(WIN32)
if(UNIX) 
	set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
endif(UNIX)
 
find_package(OGRE REQUIRED)
 
if(NOT "${OGRE_VERSION_NAME}" STREQUAL "Cthugha")
	message(SEND_ERROR "You need Ogre 1.7 Cthugha to build this.")
endif()
 
# Add OgreTerrain.{so,dll,etc.} to our linked libs
#	These variables are defined in FindeOGRE.cmake, mine is
#	found at /usr/local/lib/OGRE/cmake/
if(OGRE_Terrain_FOUND)
# pretty sure the following include is unneeded
#	include_directories(${OGRE_Terrain_INCLUDE_DIRS})
# append OgreTerrain to the end of the OGRE_LIBRARIES variable
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Terrain_LIBRARIES})
	message(STATUS "Found OGRE_Terrain: ${OGRE_Terrain_LIBRARIES}")
else(OGRE_Terrain_FOUND)
	message(SEND_ERROR "OgreTerrain Library not found.")
endif(OGRE_Terrain_FOUND)
# end Terrain

find_package(OIS REQUIRED)
 
if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()

# Find Bullet
#find_package(Bullet REQUIRED) # Bullet >>> 4-11-2139

# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)
 
	# Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# a b c d e f g  h i j k l m n  o p q r s t  u v w x y z
 
set(HDRS
	include/btKinematicCharacterController.h
	include/Character.h
	include/CharacterInputListener.h
	include/CharacterState.h
	include/GameBase.h
	include/GraphicCharacter.h
	include/GameMap.h
	include/KinematicCharacter.h
	include/LoadingBar.h
	include/PhysicsBase.h
	include/PhysicsFrameListener.h
	include/SeekSeekSeek.h
	include/DotSceneLoader.h	# .scene file loader >>> 5-7-2012
)
 
set(SRCS
	src/btKinematicCharacterController.cpp
	src/Character.cpp
	src/CharacterInputListener.cpp
	src/GameBase.cpp
	src/GraphicCharacter.cpp
	src/GameMap.cpp
	src/KinematicCharacter.cpp
	src/main.cpp
	src/PhysicsBase.cpp
	src/PhysicsFrameListener.cpp
	src/SeekSeekSeek.cpp
	src/DotSceneLoader.cpp	# .scene file loader >>> 5-7-2012
	src/tinyxml/tinyxml.cpp	# tinyXML >>> 5-7-2012
	src/tinyxml/tinystr.cpp
	src/tinyxml/tinyxmlerror.cpp
	src/tinyxml/tinyxmlparser.cpp
	src/tinyxml/tinyxml.h
	src/tinyxml/tinystr.h # tinyXML >>> 5-7-2012
)
 
include_directories(
	${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${BULLET_INCLUDE_DIRS}     # Bullet		>>> 4-14-1025
	${OGREBULLET_INCLUDE_DIRS} # OgreBullet >>> 4-11-0027
	${OGRE_SAMPLES_INCLUDEPATH}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${OPENGL_INCLUDE_DIRS} # OpenGL >>> 4-23-1245
	${OPENAL_INCLUDE_DIR} # OpenAL >>> 5-8-2059
	${OGREAL_INCLUDE_DIR} # OgreAL >>> 5-8-2059
)

add_executable(seek WIN32 ${HDRS} ${SRCS})
 
set_target_properties(seek PROPERTIES DEBUG_POSTFIX _d)

if(WIN32) # >>> 5-7-134
	target_link_libraries(
		seek
		${OGRE_LIBRARIES}
		${OIS_LIBRARIES}
		"E:/Bullet/BULLET_PHYSICS/lib/BulletCollision.lib"		
		"E:/Bullet/BULLET_PHYSICS/lib/BulletDynamics.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/BulletMultiThreaded.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/BulletSoftBody.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/BulletSoftBodySolvers_CPU.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/BulletSoftBodySolvers_OpenCL_Mini.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/ConvexDecomposition.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/GIMPACTUtils.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/LinearMath.lib"
		"E:/Bullet/BULLET_PHYSICS/lib/MiniCL.lib"
		"E:/ogrebullet/lib/Debug/OgreBulletCollisions_d.lib"
		"E:/ogrebullet/lib/Debug/OgreBulletDynamics_d.lib"
		"E:/openal/OpenALSDK/libs/Win32/OpenAL32.lib"	# OpenAL >>> 5-8-2100
		"E:/openal/OgreAL-Eihort/lib/Release/OgreAL.lib"# OgreAL >>> 5-8-2100
)
endif(WIN32)
if(UNIX)
	target_link_libraries(
		seek
		${OGRE_LIBRARIES}
		${OIS_LIBRARIES}
		BulletCollision			   # Bullet >>> 4-14-1041
		BulletDynamics
		BulletMultiThreaded
		BulletSoftBody
		BulletSoftBodySolvers_CPU
		BulletSoftBodySolvers_OpenCL_Mini
		ConvexDecomposition
		GIMPACTUtils
		LinearMath
		MiniCL
		OgreBulletCol			   # OgreBullet >>> 4-14-1041
		OgreBulletDyn
		openal					# OpenAL >>> 5-8-2100
		OgreAL					# OgreAL >>> 5-8-2100
)
endif(UNIX) 

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/media)
 
# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET seek PRE_BUILD
		COMMAND if not exist .\\bin mkdir .\\bin )
	add_custom_command( TARGET seek POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
endif(MINGW OR UNIX)
 
if(WIN32)
 
	install(TARGETS seek
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
    # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
    # so you'll have to change that to make it work with 1.7.1
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
	# as of sdk 1.7.2 we need to copy the boost dll's as well
	# because they're not linked statically (it worked with 1.7.1 though)
	install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
		${Boost_THREAD_LIBRARY_RELEASE}
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
		${Boost_THREAD_LIBRARY_DEBUG}
		DESTINATION bin
		CONFIGURATIONS Debug
	)
endif(WIN32)

if(UNIX)
 
	install(TARGETS seek
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
endif(UNIX)
