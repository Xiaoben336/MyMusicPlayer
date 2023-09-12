//
// Created by zjf on 2023/9/9.
//

#include "call_java.h"


CallJava::CallJava(_JavaVM *javaVm, JNIEnv *jniEnv, jobject jobj)
{
    this->m_JavaVM = javaVm;
    this->m_JniEnv = jniEnv;
    this->m_Jobj = jniEnv->NewGlobalRef(jobj);

    jclass jclz = jniEnv->GetObjectClass(m_Jobj);
    if (!jclz)
    {
        LOGI(TAG,"jclz is null.");
        return;
    }
    this->m_JmethodIdPrepared = m_JniEnv->GetMethodID(jclz,"onCallPrepared","()V");
}

CallJava::~CallJava() {

}

void CallJava::OnCallPrepared(int type) {
    if (type == MAIN_THREAD)
    {
        m_JniEnv->CallVoidMethod(m_Jobj,m_JmethodIdPrepared);
    } else if (type == CHILD_THREAD) {
        JNIEnv  *jniEnv;
        if (m_JavaVM->AttachCurrentThread(&jniEnv,0) != JNI_OK)
        {
            LOGW(TAG,"Get child thread jni failed.");
            return;
        }
        jniEnv->CallVoidMethod(m_Jobj,m_JmethodIdPrepared);
        m_JavaVM->DetachCurrentThread();
    }
}
