//
// Created by ilong on 2018/3/19.
//

#ifndef ANDROIDJNIDEMO_JAVA_STRING_H
#define ANDROIDJNIDEMO_JAVA_STRING_H

#include <jni.h>

class JavaString {
public:
    JavaString(JNIEnv *env, jstring str);

    ~JavaString();

    operator const char*() {
        return utfstring_;
    }

private:
    JNIEnv* env_;
    jstring str_;
    const char* utfstring_;
};


#endif //ANDROIDJNIDEMO_JAVA_STRING_H
