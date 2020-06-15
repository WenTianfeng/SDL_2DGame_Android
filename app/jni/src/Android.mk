LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

APP_STL := gnustl_static
#APP_STL := c++_shared

APP_CPPFLAGS += -std=c++11



# LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

LOCAL_CPPFLAGS += -frtti


# Add your application source files here...
LOCAL_SRC_FILES := main.cpp \
                SourceFiles/Animation.cpp \
                SourceFiles/Game.cpp \
                SourceFiles/AssetManager.cpp \
                SourceFiles/Collision.cpp \
                SourceFiles/Entity.cpp \
                SourceFiles/EntityManager.cpp \
                SourceFiles/FontManager.cpp \
                SourceFiles/TerrainMap.cpp \
                SourceFiles/TextureManager.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
