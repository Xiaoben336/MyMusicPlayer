//
// Created by zjf on 2023/9/13.
//

#include "av_packet_queue.h"


AVPacketQueue::AVPacketQueue(MyPlayStatus *myPlayStatus)
{
    pthread_mutex_init(&mAVPacketMutex,NULL);
    pthread_cond_init(&mAVPacketCond,NULL);
    this->mMyPlayStatus = myPlayStatus;
}

AVPacketQueue::~AVPacketQueue()
{
    pthread_mutex_destroy(&mAVPacketMutex);
    pthread_cond_destroy(&mAVPacketCond);
}

int AVPacketQueue::PutAVPacket(AVPacket *avPacket)
{
    pthread_mutex_lock(&mAVPacketMutex);
    mAVPacketQueue.push(avPacket);
    LOGI(TAG_AVPacketQueue,"放入一个AVPacket，当前大小为：%d",mAVPacketQueue.size());

    pthread_cond_signal(&mAVPacketCond);
    pthread_mutex_unlock(&mAVPacketMutex);
    return 0;
}

int AVPacketQueue::GetAVPacket(AVPacket *avPacket)
{
    pthread_mutex_lock(&mAVPacketMutex);

    while(mMyPlayStatus != NULL && !mMyPlayStatus->mExit)
    {
        if (mAVPacketQueue.size() > 0)
        {
            AVPacket *packet = mAVPacketQueue.front();
            if (av_packet_ref(avPacket,packet) == 0)
            {
                mAVPacketQueue.pop();
                av_packet_free(&packet);
                av_free(packet);
                packet = NULL;
                LOGI(TAG_AVPacketQueue,"从队列取出一个AVPacket，还剩下%d个",mAVPacketQueue.size());
            }
            break;
        }
        else
        {
            pthread_cond_wait(&mAVPacketCond,&mAVPacketMutex);
        }


    }
    pthread_mutex_unlock(&mAVPacketMutex);
    return 0;
}

int AVPacketQueue::GetSize() {
    int size = 0;
    pthread_mutex_lock(&mAVPacketMutex);
    size = mAVPacketQueue.size();
    pthread_mutex_unlock(&mAVPacketMutex);
    return size;
}
