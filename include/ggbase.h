#ifndef __GG_BASE_BASE_H__
#define __GG_BASE_BASE_H__

#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <pthread.h>
#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#ifdef WIN32
#ifdef GG_BASE_EXPORTS
#define GG_BASE_API __declspec(dllexport)
#else
#define GG_BASE_API __declspec(dllimport)
#endif
#else
#define GG_BASE_API
#endif

#include "ggcond.h"
#include "ggmutex.h"
#include "gglog.h"
#include "ggsocket.h"
#include "ggthread.h"
#include "ggutils.h"
#include "ggmd5.h"


#ifdef WIN32
typedef int ssize_t;
typedef short int int16_t;
typedef unsigned short int uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef char int8_t;
typedef unsigned char uint8_t;
#endif

#ifndef htonll
#define htonll(val)         (((uint64_t) htonl((val))) << 32) + htonl((val) >> 32);
#endif

#ifndef ntohll
#define ntohll(val)         (((uint64_t) ntohl((val))) << 32) + ntohl((val) >> 32);
#endif

#ifndef LQ_SAFE_DELETE
#define LQ_SAFE_DELETE(p)       do { if(p) { delete (p); (p) = NULL; } } while(0)
#endif

#ifndef LQ_SAFE_FREE
#define LQ_SAFE_FREE(p)       do { if(p) { free ((void*)p); (p) = NULL; } } while(0)
#endif

#ifndef LQ_LOCK_SAFE_DELETE
#define LQ_LOCK_SAFE_DELETE(m, p)    \
    gg_mutex_lock(m);                \
    LQ_SAFE_DELETE(p);               \
    gg_mutex_unlock(m);              \
    gg_mutex_destroy(m);
#endif

#endif /* __GG_BASE_BASE_H__ */
