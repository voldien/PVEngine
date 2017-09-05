CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(physic)

# Build shared/dynamic library option
OPTION(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
IF(NOT BUILD_SHARED_LIBS)
	SET(CMAKE_EXE_LINKER_FLAGS "-static")
	SET(LINK_SEARCH_START_STATIC TRUE)
ENDIF(NOT BUILD_SHARED_LIBS)


# Set version of the project.
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)
SET(VERSION_REVISION 0)
SET(VERSION_STATE a)
SET(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_STATE}${VERSION_REVISION} )
SET(PROJECT_VERSION "${VERSION}")

# Set predefined macro for version.
ADD_DEFINITIONS(-DPV_VERSION="${VERSION}"})

# Added additional include headers.
INCLUDE_DIRECTORIES(./include)

# g++ compiler flags
IF((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
	IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8) # -fPIC is only required
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	ENDIF()

	ADD_DEFINITIONS( -Wall -w -fpermissive -Wfatal-errors)
	IF (CMAKE_BUILD_TYPE STREQUAL "Release")
		MESSAGE(STATUS "Compile for release.")
		ADD_DEFINITIONS( -DNDEBUG )
		ADD_DEFINITIONS( -O2 )
		SET(CMAKE_RELEASE TRUE)
	ELSE()
		MESSAGE(STATUS "Compile for debug.")
		ADD_DEFINITIONS( -D_DEBUG )
		ADD_DEFINITIONS( -g3 -O0 )
		SET(CMAKE_DEBUG TRUE)
	ENDIF()
ELSEIF(MSVC)

	# Enable multi-core complication with MSVC
	ADD_DEFINITIONS(/MP)
endif()


# Set c++ language version required for the project.
IF( CMAKE_COMPILER_IS_GNUCXX )
	SET(LIBSTDC++_LIBRARIES -std=c++0x)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x" )
ENDIF( CMAKE_COMPILER_IS_GNUCXX )


# Core source files.
FILE(GLOB clientsrc 	${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp)
FILE(GLOB enginesrc	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB serversrc 	${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp)

# All Headers
FILE(GLOB headers 	${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
			${CMAKE_CURRENT_SOURCE_DIR}/include/physic/*.h
			${CMAKE_CURRENT_SOURCE_DIR}/include/renderer/*.h)
FILE(GLOB physichaders ${CMAKE_CURRENT_SOURCE_DIR}/include/physic/*.h )
FILE(GLOB rendererheaders ${CMAKE_CURRENT_SOURCE_DIR}/include/renderer/*.h)

# Shader files.
FILE(GLOB shaders  ${CMAKE_CURRENT_SOURCE_DIR}/shader/*.glsl )

# Source files for the physic interfaces.
FILE(GLOB rpcphysicsrc		${CMAKE_CURRENT_SOURCE_DIR}/src/physic/rpc/*.cpp)
FILE(GLOB bulletphysicsrc	${CMAKE_CURRENT_SOURCE_DIR}/src/physic/bullet/*.cpp )
FILE(GLOB bulletphysicheader	${CMAKE_CURRENT_SOURCE_DIR}/include/physic/*.cpp )
FILE(GLOB bullet3physicsrc	${CMAKE_CURRENT_SOURCE_DIR}/src/physic/bullet3/*.cpp )
FILE(GLOB physxphysicsrc	${CMAKE_CURRENT_SOURCE_DIR}/src/physic/physx/*.cpp)

# OpenGL rendering interface source files.
FILE(GLOB rendereropengl 	${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/opengl/*.cpp )

# Vulkan rendering interface source files.
FILE(GLOB renderervulkan 	${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/vulkan/*.cpp)

# DirectX rendering interface source files.
FILE(GLOB rendererdirectx 	${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/directx/*.cpp)

# Include OpenGL and OpenSSL Cmake modules.
INCLUDE(FindOpenSSL)
INCLUDE(FindOpenGL)

# Find and include libxml2 for supporting configuration.
INCLUDE(FindLibXml2)
IF ( LIBXML2_FOUND )
	MESSAGE(STATUS "Using xml2 version ${LIBXML2_VERSION_STRING}.")
	INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
ENDIF()

# Add main library.
ADD_LIBRARY(PVEngine ${enginesrc} )
ADD_DEPENDENCIES(PVEngine shaders )

# Add executable library targets.
ADD_EXECUTABLE(PVClient ${clientsrc} )
ADD_EXECUTABLE(PVServer ${serversrc} )

# Set linking dependencies.
TARGET_LINK_LIBRARIES(PVEngine -lSDL2 -lGL -lassimp -lfreeimage -llz4 -lz -lzip -lssl -ldl -lcrypto -lhpm -lhpmcpp ${LIBXML2_LIBRARIES} )
TARGET_LINK_LIBRARIES(PVClient PVEngine )
TARGET_LINK_LIBRARIES(PVServer PVEngine )

# Rendering interface.
ADD_LIBRARY(pvopengl ${rendereropengl})
ADD_LIBRARY(pvvulkan ${renderervulkan})
#ADD_LIBRARY(pvdirectx ${rendererdirectx})

# Rendering interface library needed.
TARGET_LINK_LIBRARIES(pvopengl -lGL -lGLEW)
TARGET_LINK_LIBRARIES(pvvulkan -lvulkan)
IF(WIN32)
	TARGET_LINK_LIBRARIES(pvdirectx -ldirectx)
ENDIF()

# Physic interfaces.
ADD_LIBRARY(pvrpcphysic	${rpcphysicsrc})
ADD_LIBRARY(pvbulletphysic ${bulletphysicsrc})
ADD_LIBRARY(pvbullet3physic ${bullet3physicsrc})
#ADD_LIBRARY(pvphysxphysic ${physxphysicsrc})

# 
INCLUDE(FindBullet)
SET(BULLET_LIB "-lBulletDynamics -lBulletCollision -lLinearMath -lBulletSoftBody")
TARGET_LINK_LIBRARIES(pvrpcphysic PVEngine)
TARGET_LINK_LIBRARIES(pvbulletphysic ${BULLET_LIB} PVEngine )
TARGET_LINK_LIBRARIES(pvbullet3physic ${BULLET_LIB} PVEngine )
#TARGET_LINK_LIBRARIES(pvphysxphysic )

# Set compilation option flags.
IF ((CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang") )
	TARGET_INCLUDE_DIRECTORIES( pvbulletphysic PUBLIC "${BULLET_INCLUDE_DIRS}" )
	TARGET_INCLUDE_DIRECTORIES( pvbullet3physic PUBLIC "${BULLET_INCLUDE_DIRS}" )
ENDIF()

# Install physic interface plugin in library directory.
INSTALL(TARGETS pvrpcphysic DESTINATION lib)
INSTALL(TARGETS pvbulletphysic DESTINATION lib)
INSTALL(TARGETS pvbullet3physic DESTINATION lib)
#INSTALL(TARGETS pvphysxphysic DESTINATION lib)

# Install rendering interfaces in the library directory.
INSTALL(TARGETS pvopengl DESTINATION lib)
INSTALL(TARGETS pvvulkan DESTINATION lib)
IF(WIN32)
INSTALL(TARGETS pvdirectx DESTINATION lib)

ENDIF()

# Install physic engine core in the library directory.
INSTALL(TARGETS PVEngine DESTINATION lib)

# Install Server and client application in the executable binary location.
INSTALL(TARGETS PVClient DESTINATION bin)
INSTALL(TARGETS PVServer DESTINATION bin)

# Install the headers for implementing physic or rendering interfaces.
INSTALL(FILES ${headers} DESTINATION include/PVPhysic)
INSTALL(FILES ${rendererheaders} DESTINATION include/PVPhysic/renderer)
INSTALL(FILES ${physichaders} DESTINATION include/PVPhysic/physic)
INSTALL(FILES keymap.xml DESTINATION /usr/share/pvengine)
INSTALL(FILES pvengine.xml DESTINATION ~/.pvengine)

# Only UNIX systems.
IF( UNIX )

	# Create default shader zip file.
	SET( SHADERZIP "defaultshader" )
	SET( SHADERZIPFILE "${SHADERZIP}.zip" )
	ADD_CUSTOM_TARGET(	shaders
				COMMAND mkdir -p glsl
				COMMAND cp -r shader/glsl/* glsl/
				COMMAND zip -r ${SHADERZIPFILE} glsl/
				COMMAND rm -r glsl)
	INSTALL( FILES ${SHADERZIPFILE} DESTINATION /usr/share/pvengine )

	# Create distribution tarball.
	SET( TARGETDIR "${PROJECT_NAME}-${VERSION}")
	ADD_CUSTOM_TARGET(	distribution
				COMMAND mkdir -p ${TARGETDIR}
				COMMAND cp -r src include samples shader CMakeLists.txt LICENSE ${TARGETDIR}
				COMMAND tar cf - ${TARGETDIR} | gzip -c > ${TARGETDIR}.tar.gz 
				COMMAND rm -r ${TARGETDIR} )
ELSEIF(WIN32)

ELSE()

ENDIF()

