package com.kienvu.over9000;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;

import java.util.HashMap;

/**
 * Created by Kien Vu on 13/08/2016.
 */
public class SoundManager {

    private MediaPlayer mMediaPlayer;
    private int mCurrentPos;

    public SoundManager(Context context) {
        mMediaPlayer = new MediaPlayer();
        mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
        mMediaPlayer.setLooping(true);
        mCurrentPos = 0;

        mSoundPool = new SoundPool(4, AudioManager.STREAM_MUSIC, 0);
        mAudioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
        mStreamMap = new HashMap<Integer, Integer>();
        nativeInitSound();
    }

    public void playMusic(String path) {
        stopMusic();
        try {
            mMediaPlayer = new MediaPlayer();
            mMediaPlayer.setDataSource(path);
            mMediaPlayer.prepareAsync();
            mMediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                public void onPrepared(MediaPlayer mp) {
                    mp.start();
                }
            });
        } catch (Exception e) {
        }
    }

    public void stopMusic() {
        try {
            mMediaPlayer.stop();
            mMediaPlayer.release();
            mCurrentPos = 0;
        } catch (Exception e) {
        }
    }

    public void pauseMusic() {
        try {
            mCurrentPos = mMediaPlayer.getCurrentPosition();
            mMediaPlayer.stop();
            mMediaPlayer.release();
        } catch (Exception e) {
        }
    }

    public void resumeMusic() {
        try {
            final int pos = mCurrentPos;
            mMediaPlayer.prepareAsync();
            mMediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                public void onPrepared(MediaPlayer mp) {
                    mp.seekTo(pos);
                    mp.start();
                }
            });
        } catch (Exception e) {
        }
    }


    /*******************************************************
     * This feature is under researching.
     */

    private SoundPool mSoundPool;
    private AudioManager mAudioManager;
    private HashMap<Integer, Integer> mStreamMap;

    public int addSound(String path) {
        return mSoundPool.load(path, 1);
    }

    public void playSound(int index, int loop) {
        stopSound(index);
        int streamVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
        int streamID = mSoundPool.play(index, streamVolume, streamVolume, 1, loop, 1.0f);

        mStreamMap.put(index, streamID);
    }

    public void stopSound(int index) {
        if (mStreamMap.containsValue(index)) {
            mSoundPool.stop(mStreamMap.get(index));
            mStreamMap.remove(index);
        }
    }

    public void pauseSound(int index) {
        if (mStreamMap.containsValue(index)) {
            mSoundPool.pause(mStreamMap.get(index));
        }
    }

    public void resumeSound(int index) {
        if (mStreamMap.containsValue(index)) {
            mSoundPool.resume(mStreamMap.get(index));
        }
    }

    public void pauseAll() {
        mSoundPool.autoPause();
    }

    public void resumeAll() {
        mSoundPool.autoResume();
    }

    private native void nativeInitSound();
}
