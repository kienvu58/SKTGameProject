#include "jni_base.h"
#include "app.h"


// Call to initialize the graphics state
JNIEXPORT void JNI_FUNCTION(GameRenderer_nativeInit)( JNIEnv*  env, jobject thiz )
{
    LOGI("GameRenderer_nativeInit");
	appInit();
}

// Call to resize viewport
JNIEXPORT void JNI_FUNCTION(GameRenderer_nativeResize)( JNIEnv*  env, jobject thiz, jint w, jint h )
{
    LOGI("GameRenderer_nativeResize %d x %d", w, h);
    appResize((int)w, (int)h);
}

// Call to render the next GL frame
JNIEXPORT void JNI_FUNCTION(GameRenderer_nativeRender)( JNIEnv*  env )
{
	appUpdate();
}

// Call to finalize the graphics state
JNIEXPORT void JNI_FUNCTION(GameRenderer_nativeDestroy)( JNIEnv*  env )
{
    LOGI("GameRenderer_nativeDestroy");

	appDestroy();
}

// This is called to indicate to the render loop that it should
// stop as soon as possible.
JNIEXPORT void JNI_FUNCTION(GameGLSurfaceView_nativePause)( JNIEnv*  env )
{
    LOGI("GameGLSurfaceView_nativePause");

	appPause();
}

JNIEXPORT void JNI_FUNCTION(GameGLSurfaceView_nativeResume)( JNIEnv*  env )
{
    LOGI("GameGLSurfaceView_nativeResume");

	appResume();
}

JNIEXPORT void JNI_FUNCTION(GameGLSurfaceView_nativeOnTouch)( JNIEnv*  env, jobject thiz, jint a, jint x, jint y , jint id)
{
	appOnTouch( a, x, y, id);
}