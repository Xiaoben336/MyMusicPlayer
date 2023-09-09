#include <jni.h>
#include <string>

extern "C"
{
#include "include/ffmpeg/libavutil/avutil.h"
JNIEXPORT jstring JNICALL
Java_com_zjf_mymusicplayer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_zjf_mymusicplayer_MainActivity_ffmpegVersion(JNIEnv *env, jobject thiz) {
    // TODO: implement ffmpegVersion()
    return env->NewStringUTF(av_version_info());
}
}
