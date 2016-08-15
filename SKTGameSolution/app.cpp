#include <time.h>
#include <chrono>

#include "app.h"
#include "jni_base.h"

static JavaVM *cached_jvm;

extern int GameInit();

extern void GameSetScaleFactor(int w, int h);

extern void GameDraw();

extern void GameUpdate(float);

extern void OnKeyEvent(unsigned char, bool);

extern void GameCleanUp();

extern void OnTouchEvent(int, int, int, int);

void appInit() {

    GameInit();
}

void appResize(int w, int h) {
    GameSetScaleFactor(w, h);
}

void appUpdate() {
    auto now = std::chrono::system_clock::now().time_since_epoch();

    static long long begin = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
    long long end = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

    float time = (float) (end - begin) / 1000.0f;

    GameUpdate(time);
    GameDraw();

    begin = end;
}

void appDestroy() {
    GameCleanUp();
}

void appOnTouch(int type, int x, int y, int id) {
    LOGI("Touch at [x:%d, y:%d] [id: %d] [type: %d]", x, y, id, type);
    OnTouchEvent(type, x, y, id);
}

void appOnKeyDown(int keyCode) {
}

void appOnKeyUp(int keyCode) {
}

void appPause() {
    //TODO: pause the game play
}

void appResume() {
    //TODO: resume the game play
}

///////////////////////////////////////////////////////////////////////
// TO DO: Clean this up
///////////////////////////////////////////////////////////////////////
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnLoad");

    cached_jvm = vm;
    JNIEnv *env;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("vm->GetEnv((void**) &env, JNI_VERSION_1_4) FAIL");
        return -1;
    }

    LOGI("return JNI_VERSION_1_4;");
    return JNI_VERSION_1_4;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

JNIEnv *get_env() {
    JNIEnv *env;

    int status = cached_jvm->AttachCurrentThread(&env, 0);
    if (status < 0) {
        LOGE("Error attaching thread\n");
        return NULL;
    }

    if (cached_jvm->GetEnv((void **) &env, JNI_VERSION_1_6)) {
        LOGI("JNI version's not supported\n");
        return NULL;
    }

    return env;
}


