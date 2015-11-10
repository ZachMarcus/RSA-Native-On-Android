LOCAL_PATH := $(call my-dir)

#get gmp
include $(CLEAR_VARS)
LOCAL_MODULE := gmp
LOCAL_SRC_FILES := libgmp.so
include $(PREBUILT_SHARED_LIBRARY)

#get gmpxx
include $(CLEAR_VARS)
LOCAL_MODULE := gmpxx
LOCAL_SRC_FILES := libgmpxx.so
include $(PREBUILT_SHARED_LIBRARY)

#build native library
include $(CLEAR_VARS)
LOCAL_MODULE := crypto-rsa-gmp
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := crypto.cpp
LOCAL_CPPFLAGS	:= -DARM -DOS_LNX -DARCH_32 -fexceptions -fPIC 
LOCAL_CPPFLAGS	+= -I$(LOCAL_PATH)/include
LOCAL_CPPFLAGS 	+= -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)/libs
LOCAL_SHARED_LIBRARIES := gmp gmpxx
LOCAL_LDFLAGS := -Wl,-rpath,. -Wl,-rpath,/data/local/tmp

include $(BUILD_EXECUTABLE)




