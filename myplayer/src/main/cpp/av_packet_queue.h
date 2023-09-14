
#ifndef MYMUSICPLAYER_AV_PACKET_QUEUE_H
#define MYMUSICPLAYER_AV_PACKET_QUEUE_H
#include <queue>
#include "pthread.h"

#include "logging.h"
#include "my_play_status.h"

extern "C"
{
#include "include/ffmpeg/libavcodec/packet.h"
#include "include/ffmpeg/libavutil/common.h"
};
constexpr const char* TAG_AVPacketQueue = "AVPacketQueue";

class AVPacketQueue {
public:
    AVPacketQueue(MyPlayStatus *myPlayStatus);

    int PutAVPacket(AVPacket *avPacket);

    int GetAVPacket(AVPacket *avPacket);
    int GetSize();

    ~AVPacketQueue();

    std::queue<AVPacket *> mAVPacketQueue;
    pthread_mutex_t mAVPacketMutex;
    pthread_cond_t mAVPacketCond;

    MyPlayStatus* mMyPlayStatus = NULL;
};


#endif //MYMUSICPLAYER_AV_PACKET_QUEUE_H
