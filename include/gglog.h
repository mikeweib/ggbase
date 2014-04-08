#ifndef Base_gglog_h
#define Base_gglog_h

#if ANDROID
#include <android/log.h>
#elif IOS || MACOSX
#import <Foundation/Foundation.h>
#endif

#if ANDROID
#undef GGLOG_TAG
#undef ggLogD
#undef ggLogW
#undef ggLogE
#define LQLOG_TAG "ggbase"
#define ggLogD(...) __android_log_print(ANDROID_LOG_DEBUG,LQLOG_TAG,__VA_ARGS__)
#define ggLogW(...) __android_log_print(ANDROID_LOG_WARN,LQLOG_TAG,__VA_ARGS__)
#define ggLogE(...) __android_log_print(ANDROID_LOG_ERROR,LQLOG_TAG,__VA_ARGS__)

#elif IOS || MACOSX
#define ggLogD(fmt, ...) NSLog(@fmt, ##__VA_ARGS__)
#define ggLogW(fmt, ...) NSLog(@fmt, ##__VA_ARGS__)
#define ggLogE(fmt, ...) NSLog(@fmt, ##__VA_ARGS__)

#elif WIN32

#ifdef __cplusplus
extern "C" {
#endif
	GG_BASE_API void __win_log_print(const char format[], ...);
#ifdef __cplusplus
}
#endif
#define ggLogD(fmt, ...) __win_log_print(fmt, __VA_ARGS__)
#define ggLogW(fmt, ...) __win_log_print(fmt, __VA_ARGS__)
#define ggLogE(fmt, ...) __win_log_print(fmt, __VA_ARGS__)
#endif

#endif // Base_gglog_h
