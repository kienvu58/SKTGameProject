package com.kienvu.over9000;


import android.app.Activity;
import android.media.AudioManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;

/**
 * Created by Kien Vu on 13/08/2016.
 */
public class Game extends Activity {
    private GLSurfaceView mGLView = null;
//    private SoundManager mSoundManager = null;

    private native void nativeInit();
    //private native void nativeOnKeyDown( int keyCode);
    //private native void nativeOnKeyUp( int keyCode);
    //private native void nativeOnTouch(int t, int x, int y, int id);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("native");

        nativeInit();

        mGLView = new GameGLSurfaceView(this);
        setContentView(mGLView);

        setVolumeControlStream(AudioManager.STREAM_MUSIC);
//        mSoundManager = new SoundManager(this);
    }

    @Override
    protected void onPause() {
        Log.i("GAME", "onPause");
        super.onPause();

        mGLView.onPause();
//        mSoundManager.pauseMusic();
    }

    @Override
    protected void onResume() {
        Log.i("GAME", "onResume");
        super.onResume();

        mGLView.onResume();
//        mSoundManager.resumeMusic();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
//        mSoundManager.stopMusic();
    }

    public void Exit() {
        mGLView = null;
        int pid = android.os.Process.myPid();
        android.os.Process.killProcess(pid);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent msg) {
        if (keyCode == 24 || keyCode == 25 || keyCode == KeyEvent.KEYCODE_CAMERA)//volume side keys
            return false;

        if (keyCode == KeyEvent.KEYCODE_MENU || keyCode == KeyEvent.KEYCODE_SEARCH) {
            msg.startTracking();
        }

        //nativeOnKeyDown(keyCode);
        return true;
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent msg) {
        if (keyCode == 24 || keyCode == 25 || keyCode == KeyEvent.KEYCODE_CAMERA)//volume side keys
            return false;

        //nativeOnKeyUp(keyCode);
        return true;
    }


}

