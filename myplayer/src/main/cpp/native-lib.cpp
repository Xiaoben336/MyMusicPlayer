#include <jni.h>
#include <string>

#include "logging.h"
#include "call_java.h"
#include "my_ffmpeg.h"

extern "C"
{
#include "include/ffmpeg/libavutil/avutil.h"
_JavaVM *javaVM;
CallJava *callJava = NULL;
MyFFmpeg *myFFmpeg = NULL;
MyPlayStatus *myPlayStatus = NULL;

JNIEXPORT jint JNICALL
JNI_OnLoad(_JavaVM *vm,void *reserved)
{
    jint  result = -1;
    javaVM = vm;
    JNIEnv *jniEnv;
    if (vm->GetEnv((void **)(&jniEnv), JNI_VERSION_1_4) != JNI_OK)
    {
        return result;
    }
    return JNI_VERSION_1_4;
}

JNIEXPORT jstring JNICALL
Java_com_zjf_myplayer_FFmepgDemo_ffmpegVersion(JNIEnv *env, jobject thiz) {
    // TODO: implement ffmpegVersion()
    return env->NewStringUTF(av_version_info());
}

JNIEXPORT void JNICALL
Java_com_zjf_myplayer_player_MyMediaPlayer_native_1prepared(JNIEnv *env, jobject thiz,
                                                            jstring source) {
    // TODO: implement native_prepared()
    const char* ch_source = env->GetStringUTFChars(source,0);
    if (myFFmpeg == NULL)
    {
        if (callJava == NULL)
        {
            callJava = new CallJava(javaVM,env,thiz);
        }
        myPlayStatus = new MyPlayStatus();
        myFFmpeg = new MyFFmpeg(callJava,ch_source,myPlayStatus);
        myFFmpeg->Prepared();
    }
    env->ReleaseStringUTFChars(source, ch_source);
}

JNIEXPORT void JNICALL
Java_com_zjf_myplayer_player_MyMediaPlayer_native_1start(JNIEnv *env, jobject thiz) {
    // TODO: implement native_start()
    if (myFFmpeg != NULL)
    {
        myFFmpeg->Start();
    }
}

}