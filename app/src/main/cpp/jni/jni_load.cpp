//
// Created by ilong on 2018/3/19.
//

#include <jni.h>
#include "native/native_define.h"
#include "native_student_jni.h"

/*
* Register several native methods for one class.
*/
static int registerNativeMethods(JNIEnv* env, const char* className,
                                 JNINativeMethod* methods, int numMethods)
{
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, methods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/*
* Register native methods for all classes we know about.
*/
static int registerNatives(JNIEnv* env)
{
    if (!registerNativeMethods(env,
                               JNIREG_CLASS_STUDENT,
                               StudentMethods,
                               sizeof(StudentMethods) / sizeof(StudentMethods[0]))) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/*
* Set some test stuff up.
*
* Returns the JNI version on success, -1 on failure.
*/
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    if (!registerNatives(env)) {
        LOGE("registerNatives error.");
        return -1;
    }
    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

    return result;
}