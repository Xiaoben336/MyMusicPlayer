package com.zjf.mymusicplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.zjf.mymusicplayer.databinding.ActivityMainBinding;
import com.zjf.myplayer.FFmepgDemo;
import com.zjf.myplayer.listener.MyPlayerPreparedListener;
import com.zjf.myplayer.player.MyMediaPlayer;

public class MainActivity extends AppCompatActivity {

    private MyMediaPlayer mMyMediaPlayer = new MyMediaPlayer();
    private ActivityMainBinding binding;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.startText;
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mMyMediaPlayer.setSource("http://mpge.5nd.com/2010/2010b/2013-11-18/61402/6.mp3");
                mMyMediaPlayer.prepared();

            }
        });
        mMyMediaPlayer.setMyPlayerPreparedListener(new MyPlayerPreparedListener() {
            @Override
            public void onPrepared() {
                Log.i("zjf","My media player prepared.");
                mMyMediaPlayer.start();
            }
        });
    }
}