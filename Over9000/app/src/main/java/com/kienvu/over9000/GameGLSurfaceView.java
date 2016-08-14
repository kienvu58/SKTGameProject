package com.kienvu.over9000;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

/**
 * Created by Kien Vu on 13/08/2016.
 */
class GameGLSurfaceView extends GLSurfaceView
{
    public GameGLSurfaceView(Context context){
        super(context);
        setEGLContextClientVersion(2);
        setPreserveEGLContextOnPause(true);

        setRenderer(new GameRenderer());
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        int type = -1;
        int x    = (int) e.getX(0);
        int y    = (int) e.getY(0);
        int id   = (int) e.getPointerId(0);

        switch (e.getAction()) {
            case MotionEvent.ACTION_DOWN:
                type = 1;
                break;
            case MotionEvent.ACTION_UP:
                type = 0;
                break;
            case MotionEvent.ACTION_MOVE:
                type = 2;
                break;
            default: break;
        }

        if (type != -1)
            nativeOnTouch( type, x, y, id);
        return true;
    }

    private native void nativeOnTouch( int type, int x, int y, int id);
}

