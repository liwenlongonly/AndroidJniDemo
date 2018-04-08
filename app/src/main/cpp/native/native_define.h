//
// Created by ilong on 2018/3/19.
//

#ifndef ANDROIDJNIDEMO_NATIVE_DEFINE_H
#define ANDROIDJNIDEMO_NATIVE_DEFINE_H
#include <string>


#ifdef __cplusplus
#define NS_IL_BEGIN                              namespace iLong {
#define NS_IL_END                                }
#define USING_NS_IL                              using namespace iLong
#define NS_IL                                    ::iLong
#else
#define NS_IL_BEGIN
#define NS_IL_END
#define USING_NS_IL
#define NS_IL
#endif

/** @def IL_DISALLOW_COPY_AND_ASSIGN(TypeName)
 * A macro to disallow the copy constructor and operator= functions.
 * This should be used in the private: declarations for a class
 */
#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
|| (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
#define VH_DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName &) = delete; \
TypeName &operator =(const TypeName &) = delete;
#else
#define VH_DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName &); \
TypeName &operator =(const TypeName &);
#endif

#define IL_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define IL_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define IL_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define IL_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define IL_SAFE_DELETE(p)           do { if(p) { delete (p); (p) = nullptr; } } while(0)
#define IL_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)

typedef enum
{
    LOGCRIT=0, LOGERROR, LOGWARNING, LOGINFO,
    LOGDEBUG, LOGALL
} LogLevel;

extern LogLevel log_level;// default VHALL_LOGDEBUG;

extern std::string GetFormatDate();

extern uint64_t GetTimestampMs();

#define LOGTAG    "iLongLog"

#ifdef ANDROID
#include <android/log.h>

#define LOGD(format, ...)                  if (log_level>=LOGDEBUG) __android_log_print(ANDROID_LOG_DEBUG, LOGTAG, format, ##__VA_ARGS__)

#define LOGI(format, ...)                  if (log_level>=LOGINFO) __android_log_print(ANDROID_LOG_INFO,  LOGTAG, format, ##__VA_ARGS__)

#define LOGW(format, ...)                  if (log_level>=LOGWARNING) __android_log_print(ANDROID_LOG_WARN,  LOGTAG, format, ##__VA_ARGS__)

#define LOGE(format, ...)                  if (log_level>=LOGERROR) __android_log_print(ANDROID_LOG_ERROR, LOGTAG, format, ##__VA_ARGS__)

#define LOG_OPEN(format, ...)              __android_log_print(ANDROID_LOG_DEBUG,  LOGTAG, format, ##__VA_ARGS__)

#else

#define LOGD(format, ...)            if (log_level>=LOGDEBUG) printf("%s %s %d %s DEBUG:  " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)

#define LOGI(format, ...)            if (log_level>=LOGINFO) printf("%s %s %d %s INFO:  " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)

#define LOGW(format, ...)            if (log_level>=LOGWARNING) printf("%s %s %d %s WARNING:  " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)

#define LOGE(format, ...)            if (log_level>=LOGERROR) printf("%s %s %d %s ERROR:  " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)

#define LOG_OPEN(format, ...)         printf("%s %s %d %s:  " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)

#endif



#endif //ANDROIDJNIDEMO_NATIVE_DEFINE_H
