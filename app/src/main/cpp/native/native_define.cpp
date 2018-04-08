//
// Created by ilong on 2018/3/19.
//

#include "native_define.h"
#include <chrono>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif // WIN32
#include <sstream>

LogLevel log_level = LOGALL;

std::string GetFormatDate(){
    const int buff_len = 255;
    char tmpBuf[buff_len];
#ifdef WIN32
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    snprintf(tmpBuf, buff_len, "%d-%02d-%02d %02d:%02d:%02d.%03d",
            sys.wYear, sys.wMonth, sys.wDay,
            sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#else
    struct timeval  tv;
    struct tm       *p;
    gettimeofday(&tv, NULL);
    p = localtime(&tv.tv_sec);
    snprintf(tmpBuf, buff_len, "%d-%02d-%02d %02d:%02d:%02d.%03d",
             1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,
             p->tm_hour, p->tm_min, p->tm_sec, (int)(tv.tv_usec/1000));
#endif
    return std::string(tmpBuf);
}

uint64_t GetTimestampMs() {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
}
