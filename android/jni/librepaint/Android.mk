LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog -lGLESv2 -ljnigraphics

LOCAL_CFLAGS := -D__ANDROID__=1 -DLOG_VERBOSE=1 -DDEBUG_OPENGL=1

LOCAL_MODULE := librepaint
LOCAL_SRC_FILES := Utils.cpp main.cpp

#LOCAL_STATIC_LIBRARIES := 

include $(BUILD_SHARED_LIBRARY)
