package com.zjf.myplayer;

public class FFmepgDemo {
    // Used to load the 'mymusicplayer' library on application startup.
    static {
        System.loadLibrary("myplayer");
    }

    public native String ffmpegVersion();
}
