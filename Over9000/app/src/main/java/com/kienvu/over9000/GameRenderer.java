package com.kienvu.over9000;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by Kien Vu on 13/08/2016.
 */
public class GameRenderer implements GLSurfaceView.Renderer
{
    public GameRenderer()
    {
    }

    public void onSurfaceCreated(GL10 unused, EGLConfig config)
    {
        nativeInit();
        GLES20.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    }

    public void onSurfaceChanged(GL10 gl, int w, int h)
    {
        GLES20.glViewport(0, 0, w, h);
        nativeResize(w, h);
    }

    public void onDrawFrame(GL10 unused)
    {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        nativeRender();

    }

    private native void nativeInit();
    private native void nativeResize(int w, int h);
    private native void nativeRender();
}
