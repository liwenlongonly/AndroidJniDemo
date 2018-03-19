//
// Created by ilong on 2018/3/19.
//

#ifndef ANDROIDJNIDEMO_NATIVE_STUDENT_JNI_H
#define ANDROIDJNIDEMO_NATIVE_STUDENT_JNI_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JNIREG_CLASS_STUDENT "com/ilong/jnidemo/Student"

jlong CreateStudent(JNIEnv *, jobject);

void  DestoryStudent(JNIEnv *, jobject, jlong);

void  SetName(JNIEnv *, jobject, jstring);

jstring  GetName(JNIEnv *, jobject);

void  SetGrade(JNIEnv *, jobject, jint);

jint  GetGrade(JNIEnv *, jobject);

// object method
jstring Print(JNIEnv *, jobject);

// static class method
JNIEXPORT jstring JNICALL PrintClassName(JNIEnv *, jclass);

static JNINativeMethod StudentMethods[] = {
        { "CreateStudent",                "()J",                       (void*)CreateStudent, },
        { "DestoryStudent",               "(J)V",                      (void*)DestoryStudent, },
        { "SetName",                      "(Ljava/lang/String;)V",     (void*)SetName, },
        { "GetName",                      "()Ljava/lang/String;",      (void*)GetName, },
        { "SetGrade",                     "(I)V",                      (void*)SetGrade, },
        { "GetGrade",                     "()I",                       (void*)GetGrade, },
        { "Print",                        "()Ljava/lang/String;",      (void*)Print, },
        { "PrintClassName",               "()Ljava/lang/String;",      (void*)PrintClassName, }
};

#ifdef __cplusplus
}
#endif

#endif //ANDROIDJNIDEMO_NATIVE_STUDENT_JNI_H
