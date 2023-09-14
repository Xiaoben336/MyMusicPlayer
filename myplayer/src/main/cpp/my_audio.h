//
// Created by zjf on 2023/9/9.
//

#ifndef MYMUSICPLAYER_MY_AUDIO_H
#define MYMUSICPLAYER_MY_AUDIO_H

#include "av_packet_queue.h"
#include "my_play_status.h"

extern "C"
{
#include "include/ffmpeg/libavcodec/avcodec.h"
#include "include/ffmpeg/libavcodec/codec_par.h"
};

class MyAudio {
public:
    int mStreamIndex = -1;
    AVCodecParameters *pCodecParameters = NULL;
    AVCodecContext *pCodexContext = NULL;

    AVPacketQueue *pAVPacketQueue = NULL;
    MyPlayStatus *pMyPlayStatus = NULL;

    MyAudio(MyPlayStatus *myPlayStatus);
    ~MyAudio();
};


#endif //MYMUSICPLAYER_MY_AUDIO_H
