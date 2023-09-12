//
// Created by zjf on 2023/9/9.
//

#ifndef MYMUSICPLAYER_MY_FFMPEG_H
#define MYMUSICPLAYER_MY_FFMPEG_H
#include "call_java.h"
#include "pthread.h"
#include "my_audio.h"

extern "C"
{
#include "include/ffmpeg/libavformat/avformat.h"
};

constexpr const char* TAG_MyFFmpeg = "MyFFmpeg";

class MyFFmpeg {
public:
    CallJava *m_CallJava = NULL;
    const char *m_Source;
    pthread_t m_DecodeThread;

    AVFormatContext *pFormatContext;
    MyAudio *pMyAudio = NULL;

    MyFFmpeg(CallJava *callJava, const char *source);
    void Prepared();
    void DecodeFFmpegThread();
    void Start();
    ~MyFFmpeg();

private:

};


#endif //MYMUSICPLAYER_MY_FFMPEG_H
