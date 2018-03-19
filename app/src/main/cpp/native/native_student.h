//
// Created by ilong on 2018/3/19.
//

#ifndef ANDROIDJNIDEMO_NATIVE_STUDENT_H
#define ANDROIDJNIDEMO_NATIVE_STUDENT_H

#include <string>
#include "native_define.h"

NS_IL_BEGIN

class NativeStudent {
public:
    NativeStudent();
    ~NativeStudent();

    void SetName(std::string &name);

    std::string GetName();

    void SetGrade(const int grade);

    int GetGrade();

    std::string Print();

private:
    std::string mName;
    int mGrade;
};

NS_IL_END

#endif //ANDROIDJNIDEMO_NATIVE_STUDENT_H
