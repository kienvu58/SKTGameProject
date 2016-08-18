#include "jni_base.h"

// Call to initialize the graphics state
JNIEXPORT void JNI_FUNCTION(SoundManager_nativeInitSound)( JNIEnv*  env, jobject thiz )
{
    mObjectSound = (jobject) (*env)->NewGlobalRef(env, thiz);
	
	jclass cls = (*env)->GetObjectClass(env, thiz);

    mMethodAddSound    = (*env)->GetMethodID (env, cls, "addSound", "(Ljava/lang/String;)I");
	mMethodPlaySound   = (*env)->GetMethodID (env, cls, "playSound", "(II)V");
	mMethodPlayMusic   = (*env)->GetMethodID (env, cls, "playMusic", "(Ljava/lang/String;)V");
	mMethodStopMusic   = (*env)->GetMethodID (env, cls, "stopMusic", "()V");
	mMethodStopSound   = (*env)->GetMethodID (env, cls, "stopSound", "(I)V");
	mMethodPauseSound  = (*env)->GetMethodID (env, cls, "pauseSound", "(I)V");
	mMethodResumeSound = (*env)->GetMethodID (env, cls, "resumeSound", "(I)V");
	mMethodPauseAll    = (*env)->GetMethodID (env, cls, "pauseAll", "()V");
	mMethodResumeAll   = (*env)->GetMethodID (env, cls, "resumeAll", "()V");
}

int nativeAddSound(const char* path)
{
	JNIEnv* env = get_env();
	jstring sPath = (*env)->NewStringUTF(env, path);
	return (*env)->CallIntMethod(env, mObjectSound, mMethodAddSound, sPath);
}

void nativePlaySound(int index, int loop)
{
	JNIEnv* env = get_env();
	if (mMethodPlaySound)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodPlaySound, index, loop);
	}	
}

void nativePlayMusic(const char* path)
{
	JNIEnv* env = get_env();
	jstring sPath = (*env)->NewStringUTF(env, path);
	if (mMethodPlayMusic)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodPlayMusic, sPath);
	}	
}

void nativeStopMusic()
{
	JNIEnv* env = get_env();
	if (mMethodStopMusic)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodStopMusic);
	}	
}

void nativeStopSound(int index)
{
	JNIEnv* env = get_env();
	if (mMethodStopSound)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodStopSound, index);
	}	
}

void nativePauseSound(int index)
{
	JNIEnv* env = get_env();
	if (mMethodPauseSound)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodPauseSound, index);
	}	
}

void nativeResumeSound(int index)
{
	JNIEnv* env = get_env();
	if (mMethodResumeSound)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodResumeSound, index);
	}	
}

void nativePauseAll()
{
	JNIEnv* env = get_env();
	if (mMethodPauseAll)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodPauseAll);
	}	
}

void nativeResumeAll()
{
	JNIEnv* env = get_env();
	if (mMethodResumeAll)
	{
		(*env)->CallVoidMethod(env, mObjectSound, mMethodResumeAll);
	}
}


