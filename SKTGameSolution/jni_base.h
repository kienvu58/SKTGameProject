#pragma once

#ifndef __jni_Game__
#define __jni_Game__

#include <jni.h>
#include <android/log.h>
#define LOG_TAG					"BATMAN"
#define JNI_FUNCTION(function)	Java_com_kienvu_over9000_ ## function

#ifdef  __cplusplus
extern "C" {
#endif

//int s_windowWidth;
//int s_windowHeight;

JNIEnv* get_env();

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))

static jobject mObjectGame;
static jobject mObjectSound;

static jmethodID mMethodHideAd;
static jmethodID mMethodShowAd;

static jmethodID mMethodAddSound;
static jmethodID mMethodPlayMusic;
static jmethodID mMethodStopMusic;
static jmethodID mMethodPlaySound;
static jmethodID mMethodStopSound;
static jmethodID mMethodPauseSound;
static jmethodID mMethodResumeSound;
static jmethodID mMethodPauseAll;
static jmethodID mMethodResumeAll;

void nativeHideAd();
void nativeShowAd();

int  nativeAddSound(const char* path);
void nativePlayMusic(const char* path);
void nativeStopMusic();
void nativePlaySound(int index, int loop);
void nativeStopSound(int index);
void nativePauseSound(int index);
void nativeResumeSound(int index);
void nativePauseAll();
void nativeResumeAll();
static jmethodID mMethodLogin;
static jmethodID mMethodShare;

void nativeLogin();
void nativeShare();

static jmethodID mMethodExit;
void nativeExit();

// static jmethodID mMethodSavePref;
// static jmethodID mMethodLoadPref;
// void nativeSave(int index);
// int nativeLoad();

#ifdef  __cplusplus
}
#endif


#endif //__jni_Game__

