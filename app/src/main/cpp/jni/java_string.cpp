//
// Created by ilong on 2018/3/19.
//

#include "java_string.h"

JavaString::JavaString(JNIEnv *env, jstring str):env_(env), str_(str) {
    utfstring_ = env_->GetStringUTFChars(str_, NULL);
}

JavaString::~JavaString() {
    env_->ReleaseStringUTFChars(str_, utfstring_);
}