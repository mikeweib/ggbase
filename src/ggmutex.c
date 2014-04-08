#include "ggbase.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化互斥锁。
 * @return 成功返回互斥锁，失败返回NULL。
 */
gg_mutex_t GG_BASE_API gg_mutex_create() {
#ifdef WIN32
	gg_mutex_t mutex = (gg_mutex_t)malloc(sizeof(CRITICAL_SECTION));
	if (mutex) {
		InitializeCriticalSection(mutex);
	}
	else {
		mutex = NULL;
	}
#else
	gg_mutex_t mutex = (gg_mutex_t)malloc(sizeof(pthread_mutex_t));
	if (mutex) {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(mutex, &attr);
        pthread_mutexattr_destroy(&attr);
	}
	else {
		mutex = NULL;
	}
#endif

	return mutex;
}

/**
 * @brief 释放互斥锁资源。
 * @param[in] lock 互斥锁。
 */
void GG_BASE_API gg_mutex_destroy(gg_mutex_t mutex) {
	if (mutex) {
#ifdef WIN32
		DeleteCriticalSection(mutex);
#else
		pthread_mutex_destroy(mutex);
#endif
		free(mutex);
	}
	mutex = NULL;
}

/**
 * @brief 锁定互斥锁。
 * @param[in] mutex 互斥锁。
 * @return 成功返回0；失败返回错误代码。
 */
int GG_BASE_API gg_mutex_lock(gg_mutex_t mutex) {
    if (!mutex) return 0;
    
#ifdef WIN32
	EnterCriticalSection(mutex);
	return 0;
#else
	return pthread_mutex_lock(mutex);
#endif
}

/**
 * @brief 解锁互斥锁。
 * @param[in] mutex 互斥锁。
 * @return 成功返回0；失败返回错误代码。
 */
int GG_BASE_API gg_mutex_unlock(gg_mutex_t mutex) {
    if (!mutex) return 0;
#ifdef WIN32
	LeaveCriticalSection(mutex);
	return 0;
#else
	return pthread_mutex_unlock(mutex);
#endif
}

#ifdef __cplusplus
}
#endif
