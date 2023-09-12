//
// Created by zjf on 2023/9/9.
//
#ifndef MYMUSICPLAYER_CALL_JAVA_H
#define MYMUSICPLAYER_CALL_JAVA_H

#include <jni.h>

#include "logging.h"

#define MAIN_THREAD 0
#define CHILD_THREAD 1

constexpr const char* TAG = "CallJava";

class CallJava {
public:
    CallJava(_JavaVM *javaVm,JNIEnv *jniEnv,jobject jobj);
    void OnCallPrepared(int type);
    ~CallJava();

    _JavaVM *m_JavaVM = NULL;
    JNIEnv *m_JniEnv = NULL;
    jobject m_Jobj;

    jmethodID  m_JmethodIdPrepared;
};


#endif //MYMUSICPLAYER_CALL_JAVA_H
