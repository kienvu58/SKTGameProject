#include "jni_base.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * Method:		nativeInit
 * Signature:	(V)V
 * Comment:		Since in GLRender we already initialize the important stuff, here we're only registering the methods
 */
JNIEXPORT void JNICALL JNI_FUNCTION(Game_nativeInit) (JNIEnv*  env, jobject thiz)
{
    LOGI("TUNGPH: Game_nativeInit");

	mObjectGame = (jobject) (*env)->NewGlobalRef(env, thiz);   

	jclass cls = (*env)->GetObjectClass(env, thiz);

    //mMethodExit = (*env)->GetMethodID (env,cls, "Exit", "()V");

    LOGI("TUNGPH: Game_nativeInit DONE");

}

// JNIEXPORT void JNI_FUNCTION(Game_nativeOnKeyDown)( JNIEnv*  env, jobject thiz, jint a )
// {
// 	appOnKeyDown( a );
// }

// JNIEXPORT void JNI_FUNCTION(Game_nativeOnKeyUp)( JNIEnv*  env, jobject thiz, jint a )
// {
// 	appOnKeyUp( a );
// }

void nativeExit()
{
	// JNIEnv* mEnv = get_env();
	// if (mMethodExit)
	// {
	// 	(*mEnv)->CallVoidMethod(mEnv, mObjectGame, mMethodExit);
	// }
}

// void nativeSave(int index)
// {
// 	JNIEnv* env = get_env();
// 	if (mMethodSavePref)
// 	{
// 		(*env)->CallVoidMethod(env, mObjectGame, mMethodSavePref, index);
// 	}
// }

// int nativeLoad()
// {
// 	JNIEnv* env = get_env();
// 	if (mMethodLoadPref)
// 	{
// 		return (*env)->CallIntMethod(env, mObjectGame, mMethodLoadPref);
// 	}
// }


#ifdef  __cplusplus
}
#endif



