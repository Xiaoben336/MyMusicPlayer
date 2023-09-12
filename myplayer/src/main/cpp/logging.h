//
// Created by zjf on 2023/9/9.
//
#include "android/log.h"

#ifndef MYMUSICPLAYER_LOGGING_H
#define MYMUSICPLAYER_LOGGING_H



#define LOGI(TAG,FORMAT,...) __android_log_print(ANDROID_LOG_INFO,TAG,FORMAT,##__VA_ARGS__)
#define LOGW(TAG,FORMAT,...) __android_log_print(ANDROID_LOG_WARN,TAG,FORMAT,##__VA_ARGS__)
#define LOGE(TAG,FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,TAG,FORMAT,##__VA_ARGS__)

#endif //MYMUSICPLAYER_LOGGING_H
