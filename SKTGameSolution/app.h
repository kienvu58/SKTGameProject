#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

// The simple framework expects the application code to define these functions.
void appInit();
void appResize(int w, int h);
void appDestroy();
void appUpdate();

void appOnTouch( int flag, int x, int y, int id);
void appClearTouchEvents();
void appOnKeyDown( int keyCode );

void appOnKeyUp( int keyCode );

void appPause();
void appResume();

#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED


