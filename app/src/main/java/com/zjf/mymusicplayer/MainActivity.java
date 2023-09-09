package com.zjf.mymusicplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.zjf.mymusicplayer.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'mymusicplayer' library on application startup.
    static {
        System.loadLibrary("mymusicplayer");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        TextView ffmpegVersionText = binding.ffmpegVersionText;
        ffmpegVersionText.setText(ffmpegVersion());
    }

    /**
     * A native method that is implemented by the 'mymusicplayer' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String ffmpegVersion();
}