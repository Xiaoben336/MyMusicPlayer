//
// Created by zjf on 2023/9/9.
//

#ifndef MYMUSICPLAYER_MY_AUDIO_H
#define MYMUSICPLAYER_MY_AUDIO_H

extern "C"
{
#include "include/ffmpeg/libavcodec/avcodec.h"
#include "include/ffmpeg/libavcodec/codec_par.h"
};

class MyAudio {
public:
    int mStreamIndex = -1;
    AVCodecParameters *pCodecParameters;
    AVCodecContext *pCodexContext;

    MyAudio();
    ~MyAudio();
};


#endif //MYMUSICPLAYER_MY_AUDIO_H
