package com.zjf.myplayer.player;

import android.text.TextUtils;
import android.util.Log;

import com.zjf.myplayer.listener.MyPlayerPreparedListener;

public class MyMediaPlayer {
    private static final String TAG = "MyMediaPlayer";
    // Used to load the 'mylayer' library on application startup.
    static {
        System.loadLibrary("myplayer");
    }

    private String mSource;

    private MyPlayerPreparedListener mMyPlayerPreparedListener;

    public MyMediaPlayer() {

    }

    public MyMediaPlayer(String source) {
        this.mSource = source;
    }

    public void prepared() {
        if (TextUtils.isEmpty(mSource)) {
            Log.e(TAG,"Source is empty when prepared.");
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                native_prepared(mSource);
            }
        }).start();
    }

    public void start() {
        if (TextUtils.isEmpty(mSource)) {
            Log.e(TAG,"Source is empty when start playing.");
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                native_start();
            }
        }).start();
    }

    public void setSource(String source) {
        this.mSource = source;
    }

    public String getSource() {
        return mSource;
    }

    public void setMyPlayerPreparedListener(MyPlayerPreparedListener myPlayerPreparedListener) {
        this.mMyPlayerPreparedListener = myPlayerPreparedListener;
    }

    // Called by native.
    public void onCallPrepared() {
        if (mMyPlayerPreparedListener != null) {
            mMyPlayerPreparedListener.onPrepared();
        }
    }
    private native void native_prepared(String source);
    private native void native_start();
}
