# NDK_TOOLCHAIN_VERSION := 4.8
APP_ABI := armeabi-v7a
APP_PLATFORM := android-9
# APP_STL := stlport_static
# APP_STL := gnustl_static 
APP_STL := c++_static
APP_CPPFLAGS += -std=c++11 -fno-unit-at-a-time -fexceptions
APP_GNUSTL_FORCE_CPP_FEATURES := exceptions rtti
