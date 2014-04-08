#ifndef __GG_BASE_MUTEX_H__
#define __GG_BASE_MUTEX_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef gg_mutex_t
 * @brief 互斥锁类型。
 */
#ifdef WIN32
typedef CRITICAL_SECTION* gg_mutex_t;
#else
typedef pthread_mutex_t* gg_mutex_t;
#endif

/**
 * @brief 初始化互斥锁。
 * @return 成功返回互斥锁，失败返回NULL。
 */
gg_mutex_t GG_BASE_API gg_mutex_create();

/**
 * @brief 释放互斥锁资源。
 * @param[in] lock 互斥锁。
 */
void GG_BASE_API gg_mutex_destroy(gg_mutex_t mutex);

/**
 * @brief 锁定互斥锁。
 * @param[in] mutex 互斥锁。
 * @return 成功返回0；失败返回错误代码。
 */
int GG_BASE_API gg_mutex_lock(gg_mutex_t mutex);

/**
 * @brief 解锁互斥锁。
 * @param[in] mutex 互斥锁。
 * @return 成功返回0；失败返回错误代码。
 */
int GG_BASE_API gg_mutex_unlock(gg_mutex_t mutex);

#ifdef __cplusplus
}
#endif

#endif /* __GG_BASE_MUTEX_H__ */
