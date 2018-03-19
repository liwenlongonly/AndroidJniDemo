//
// Created by ilong on 2018/3/19.
//

#include "native_student.h"
#include "native_define.h"
#include <sstream>

NS_IL_BEGIN

NativeStudent::NativeStudent():mName(""),mGrade(0),mJavaObj(0) {

}

NativeStudent::~NativeStudent() {

}

void NativeStudent::SetName(std::string &name) {
    mName = name;
}

std::string NativeStudent::GetName() {
    return mName;
}

void NativeStudent::SetGrade(const int grade) {
    mGrade = grade;
}

int NativeStudent::GetGrade() {
    return mGrade;
}

std::string NativeStudent::Print() {
    LOGI("name:%s grade:%d",mName.c_str(),mGrade);
    std::stringstream ss;
    ss << "name:" <<mName <<" "<<"grade:"<<mGrade;
    return ss.str();
}

NS_IL_END