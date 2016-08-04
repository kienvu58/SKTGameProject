LOCAL_PATH 		:= $(call my-dir)/../..

# 
# Utilities
# 
include $(CLEAR_VARS)

LOCAL_MODULE	:= Utilities
LOCAL_SRC_FILES	:= \
	Utilities/Math.cpp \
	Utilities/TGA.cpp \
	Utilities/esShader.cpp \

LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/include
LOCAL_C_INCLUDES 	+= $(LOCAL_PATH)

LOCAL_CFLAGS	:= \
	-DANDROID \
	-D_DEBUG \
	-D_LIB \

include $(BUILD_STATIC_LIBRARY)

# 
# GraphicsEngine
# 
include $(CLEAR_VARS)

LOCAL_MODULE 	:= GraphicsEngine
LOCAL_SRC_FILES := \
	GraphicsEngine/Animation.cpp \
	GraphicsEngine/AnimationManager.cpp \
	GraphicsEngine/Frame.cpp \
	GraphicsEngine/FrameManager.cpp \
	GraphicsEngine/GraphicalObject.cpp \
	GraphicsEngine/Model.cpp \
	GraphicsEngine/InputManager.cpp \
	GraphicsEngine/ResourceManager.cpp \
	GraphicsEngine/Shaders.cpp \
	GraphicsEngine/Sprite.cpp \
	GraphicsEngine/SpriteSheet.cpp \
	GraphicsEngine/TextManager.cpp \
	GraphicsEngine/Texture.cpp \

LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/include
LOCAL_C_INCLUDES 	+= $(LOCAL_PATH)

LOCAL_CFLAGS := \
	-DANDROID \
	-D_DEBUG \
	-D_LIB \

include $(BUILD_STATIC_LIBRARY)

# 
# SKTGameProject
# 
include $(CLEAR_VARS)

LOCAL_MODULE 	:= SKTGameProject
LOCAL_SRC_FILES := \
	SKTGameProject/BeamWave.cpp \
	SKTGameProject/CellJuniorOwnedStates.cpp \
	SKTGameProject/ContactListener.cpp \
	SKTGameProject/Entity.cpp \
	SKTGameProject/EntityCellJunior.cpp \
	SKTGameProject/EntityEffect.cpp \
	SKTGameProject/EntityLiving.cpp \
	SKTGameProject/EntityMinion.cpp \
	SKTGameProject/EntityPlayer.cpp \
	SKTGameProject/EntityStatic.cpp \
	SKTGameProject/FactoryEntity.cpp \
	SKTGameProject/Game.cpp \
	SKTGameProject/GameOptionState.cpp \
	SKTGameProject/GamePlayState.cpp \
	SKTGameProject/GameWelcomeState.cpp \
	SKTGameProject/KiBlast.cpp \
	SKTGameProject/MainMenuState.cpp \
	SKTGameProject/MessageDispatcher.cpp \
	SKTGameProject/MinionOwnedStates.cpp \
	SKTGameProject/PhysicsManager.cpp \
	SKTGameProject/PoolManager.cpp \
	SKTGameProject/PlayerOwnedStates.cpp \
	SKTGameProject/Spawner.cpp \
	SKTGameProject/SteeringBehavior.cpp \
	SKTGameProject/Telegram.cpp \
	SKTGameProject/Application_android.cpp \

LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/include
LOCAL_C_INCLUDES 	+= $(LOCAL_PATH)/Android/jni
LOCAL_C_INCLUDES 	+= $(LOCAL_PATH)

LOCAL_CFLAGS := \
	-DANDROID \
	-D_DEBUG \
	-D_LIB \
	-DCEGUI_STATIC \
	-DCEGUI_BUILD_STATIC_FACTORY_MODULE \

include $(BUILD_STATIC_LIBRARY)

# 
# Android
# 
include $(CLEAR_VARS)

LOCAL_MODULE 	:= Android
LOCAL_SRC_FILES := \

LOCAL_STATIC_LIBRARIES	:= \
	Utilities \
	SKTGameProject \
	GraphicsEngine \

LOCAL_LDLIBS	:= -llog -lGLESv2
include $(BUILD_SHARED_LIBRARY)