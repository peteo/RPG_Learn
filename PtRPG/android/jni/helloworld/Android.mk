LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game

LOCAL_SRC_FILES := main.cpp \
../../../Classes/AppDelegate.cpp \
../../../Classes/HelloWorldScene.cpp \
../../../Classes/PtHelpers/PtCharacter.cpp \
../../../Classes/PtHelpers/PtCode.cpp \
../../../Classes/PtHelpers/PtMap.cpp \
../../../Classes/Scene/GameScene.cpp \
../../../Classes/Scene/MenuScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../libs/cocos2dx \
                    $(LOCAL_PATH)/../../../libs/cocos2dx/platform \
                    $(LOCAL_PATH)/../../../libs/cocos2dx/include \
                    $(LOCAL_PATH)/../../../libs/CocosDenshion/include \
                    $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/PtHelpers \
					$(LOCAL_PATH)/../../../Classes/Scene

# it is used for ndk-r5  
# if you build with ndk-r4, comment it  
# because the new Windows toolchain doesn't support Cygwin's drive
# mapping (i.e /cygdrive/c/ instead of C:/)  
LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/armeabi) \
                -lcocos2d -llog -lcocosdenshion \
                -L$(call host-path, $(LOCAL_PATH)/../../../libs/cocos2dx/platform/third_party/android/libraries) -lcurl
            
include $(BUILD_SHARED_LIBRARY)
