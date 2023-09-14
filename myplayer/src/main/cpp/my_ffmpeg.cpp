//
// Created by zjf on 2023/9/9.
//

#include "my_ffmpeg.h"

MyFFmpeg::MyFFmpeg(CallJava *callJava, const char *source, MyPlayStatus *myPlayStatus)
        : m_CallJava(callJava), m_Source(source),pMyPlayStatus(myPlayStatus)
{

}

void *decodeFFmpeg(void *data)
{
    MyFFmpeg *myFFmpeg = static_cast<MyFFmpeg *>(data);
    myFFmpeg->DecodeFFmpegThread();
    pthread_exit(&myFFmpeg->m_DecodeThread);
}

void MyFFmpeg::Prepared()
{
    pthread_create(&m_DecodeThread, NULL, decodeFFmpeg, this);
}

void MyFFmpeg::DecodeFFmpegThread()
{
    avformat_network_init();
    pFormatContext = avformat_alloc_context();
    if (avformat_open_input(&pFormatContext,m_Source,NULL,NULL) != 0)
    {
        LOGE(TAG_MyFFmpeg,"Open source failed.");
        return;
    }
    if (avformat_find_stream_info(pFormatContext,NULL) < 0)
    {
        LOGE(TAG_MyFFmpeg,"Find stream info failed.");
        return;
    }
    for (int i = 0;i < pFormatContext->nb_streams;i++)
    {
        if (pFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            if (NULL == pMyAudio)
            {
                pMyAudio = new MyAudio(pMyPlayStatus);
                pMyAudio->mStreamIndex = i;
                pMyAudio->pCodecParameters = pFormatContext->streams[i]->codecpar;
            }
        }
    }
    const AVCodec *pAudioCodec = avcodec_find_decoder(
            pMyAudio->pCodecParameters->codec_id);

    if (!pAudioCodec)
    {
        LOGE(TAG_MyFFmpeg,"Find decoder failed.");
        return;
    }
    pMyAudio->pCodexContext = avcodec_alloc_context3(pAudioCodec);
    if (!pMyAudio->pCodexContext) {
        LOGE(TAG_MyFFmpeg,"Get codex context failed.");
        return;
    }

    if (avcodec_parameters_to_context(pMyAudio->pCodexContext,pMyAudio->pCodecParameters) < 0)
    {
        LOGE(TAG_MyFFmpeg,"Parameters to context failed.");
        return;
    }
    if (avcodec_open2(pMyAudio->pCodexContext,pAudioCodec,0) != 0)
    {
        LOGE(TAG_MyFFmpeg,"Open av codec failed.");
        return;
    }
    m_CallJava->OnCallPrepared(CHILD_THREAD);
}

void MyFFmpeg::Start() {
    if (pMyAudio == NULL)
    {
        LOGE(TAG_MyFFmpeg,"pMyAudio == NULL");
        return;
    }

    int count = 0;
    while (1)
    {
        AVPacket *pAVPacket = av_packet_alloc();
        if (av_read_frame(pFormatContext,pAVPacket) == 0)
        {
            if (pAVPacket->stream_index == pMyAudio->mStreamIndex) {
                count++;
                LOGI(TAG_MyFFmpeg,"解碼第 %d 帧",count);
//                av_packet_free(&pAVPacket);
//                av_free(pAVPacket);
//                pAVPacket = NULL;
                pMyAudio->pAVPacketQueue->PutAVPacket(pAVPacket);
            }
            else
            {
                av_packet_free(&pAVPacket);
                av_free(pAVPacket);
                pAVPacket = NULL;
            }
        }
        else
        {
            av_packet_free(&pAVPacket);
            av_free(pAVPacket);
            break;
        }
    }

    while(pMyAudio->pAVPacketQueue->GetSize() > 0)
    {
        AVPacket *avPacket = av_packet_alloc();
        pMyAudio->pAVPacketQueue->GetAVPacket(avPacket);
        av_packet_free(&avPacket);
        av_free(avPacket);
        avPacket = NULL;
    }

    LOGI(TAG_MyFFmpeg,"解码完成");
}
