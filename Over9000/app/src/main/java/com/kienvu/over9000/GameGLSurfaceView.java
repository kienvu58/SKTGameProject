package com.kienvu.over9000;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

/**
 * Created by Kien Vu on 13/08/2016.
 */
class GameGLSurfaceView extends GLSurfaceView
{
    private int lastPointerCount = 0;
    public GameGLSurfaceView(Context context){
        super(context);
        setEGLContextClientVersion(2);
        setPreserveEGLContextOnPause(true);

        setRenderer(new GameRenderer());
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        int currentPointerCount = e.getPointerCount();
        for (int pointerIndex = 0; pointerIndex < currentPointerCount; pointerIndex++) {

            int type = -1;
            int x = (int) e.getX(pointerIndex);
            int y = (int) e.getY(pointerIndex);
            int id = e.getPointerId(pointerIndex);

            switch (e.getAction()) {
                case MotionEvent.ACTION_DOWN:
                case MotionEvent.ACTION_POINTER_DOWN:
                    type = 1;
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_POINTER_UP:
                    type = 0;
                    break;
                case MotionEvent.ACTION_MOVE:
                    type = 2;
                    break;
//                case MotionEvent.ACTION_OUTSIDE:
//                    type = 3;
//                    break;
//                case MotionEvent.ACTION_CANCEL:
//                    type = 4;
//                    break;
//                case MotionEvent.ACTION_POINTER_DOWN:
//                    type = 5;
//                    break;
//                case MotionEvent.ACTION_POINTER_UP:
//                    type = 6;
//                    break;
                default:
                    break;
            }

            if (type != -1)
                nativeOnTouch(type, x, y, id);
        }
        return true;
    }

    private native void nativeOnTouch( int type, int x, int y, int id);
}

