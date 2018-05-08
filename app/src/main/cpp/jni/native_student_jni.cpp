//
// Created by ilong on 2018/3/19.
//

#include "native_student_jni.h"
#include "native/native_define.h"
#include "native/native_student.h"
#include "java_string.h"
#include <async_task_pool.h>

USING_NS_IL;

#define CALLBACK_METHOD_NAME           "onResponse"
#define CALLBACK_METHOD_PARAM          "(Ljava/lang/String;)V"

NativeStudent * GetNativeStudentFromObj(JNIEnv *env, jobject obj){
    jclass objClazz = (jclass)env->GetObjectClass(obj);//obj为对应的JAVA对象
    if (objClazz == NULL){
        LOGE("env->GetObjectClass return null.");
        return nullptr;
    }
    jfieldID fid = env->GetFieldID(objClazz, "mNativeStudent", "J");
    if(fid == NULL){
        LOGE("env->GetFieldID error.");
        return nullptr;
    }
    jlong p = (jlong)env->GetLongField(obj, fid);
    return (NativeStudent *)p;
}

jlong CreateStudent(JNIEnv *env, jobject obj){
    NativeStudent *student = new(std::nothrow) NativeStudent();
    jobject gThiz = (jobject)env->NewGlobalRef(obj);//thiz为JAVA对象
    if(student){
        student->mJavaObj = (long)gThiz; //c++对象存储java引用
        return (jlong)student;
    }else{
        LOGE("new NativeStudent object is null.");
    }
    return -1;
}

void DestoryStudent(JNIEnv *env, jobject obj, jlong nativeStudent){
    NativeStudent *student = (NativeStudent*)nativeStudent;
    env->DeleteGlobalRef((jobject)student->mJavaObj); //销毁创建的引用
    IL_SAFE_DELETE(student);
}

void SetName(JNIEnv *env, jobject obj, jstring name){
    NativeStudent *student = GetNativeStudentFromObj(env,obj);
    if(student){
        std::string nameC = std::string(JavaString(env,name));
        student->SetName(nameC);
    } else{
        LOGE("GetNativeStudentFromObj(env,obj) return null.");
    }
}

jstring GetName(JNIEnv *env, jobject obj){
    NativeStudent *student = GetNativeStudentFromObj(env,obj);
    if(student){
        std::string name = student->GetName();
        jstring jName = env->NewStringUTF(name.c_str());
        return jName;
    }else{
        LOGE("GetNativeStudentFromObj(env,obj) return null.");
    }
    return env->NewStringUTF("");
}

void AsynGetName(JNIEnv *env, jobject obj, jobject callback){
    NativeStudent *student = GetNativeStudentFromObj(env,obj);
    if(student){
        jclass clazz = env->GetObjectClass(callback);
        if (clazz == NULL) {
            LOGE("env->GetObjectClass return NULL!");
            return ;
        }
        jmethodID callbackMethod = env->GetMethodID(clazz, CALLBACK_METHOD_NAME, CALLBACK_METHOD_PARAM);
        if (callbackMethod == NULL) {
            LOGE("env->GetMethodID return NULL!");
            return ;
        }
        JavaVM *jvm = NULL;
        env->GetJavaVM(&jvm);
        if (jvm == NULL) {
            LOGE("jvm is NULL!");
            return ;
        }
        jobject objcb = env->NewGlobalRef(callback);
        AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO,[jvm,callbackMethod,objcb,student]()->void{
            //TODO Child Thread
            JNIEnv *env_ = NULL ;
            if (jvm->AttachCurrentThread(&env_, NULL) != JNI_OK) {
                LOGE("AttachCurrentThread return NULL!");
                return ;
            }
            jstring str = env_->NewStringUTF(student->GetName().c_str());
            env_->CallVoidMethod(objcb, callbackMethod, str);
            env_->DeleteGlobalRef(objcb);
            if (jvm->DetachCurrentThread() != JNI_OK) {
                LOGE("DetachCurrentThread is not ok.");
                return ;
            }
        });
    }
}

void SetGrade(JNIEnv *env, jobject obj, jint grade){
    NativeStudent *student = GetNativeStudentFromObj(env,obj);
    if(student){
        student->SetGrade((int)grade);
    }else{
        LOGE("GetNativeStudentFromObj(env,obj) return null.");
    }
}

jint GetGrade(JNIEnv *env, jobject obj){
    NativeStudent *student = GetNativeStudentFromObj(env,obj);
    if(student){
        return (jint)(student->GetGrade());
    }else{
        LOGE("GetNativeStudentFromObj(env,obj) return null.");
    }
    return 0;
}

// object method
jstring Print(JNIEnv *env, jobject obj){
    NativeStudent *student = GetNativeStudentFromObj(env,obj);
    if(student){
        std::string str = student->Print();
        return env->NewStringUTF(str.c_str());
    }else{
        LOGE("GetNativeStudentFromObj(env,obj) return null.");
    }
    return env->NewStringUTF("");
}

// static class method
JNIEXPORT jstring JNICALL PrintClassName(JNIEnv *env, jclass clazz){
    return env->NewStringUTF("NativeStudent");
}